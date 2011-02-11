/***********************************************************************
**
** This file is part of Rhubarb.
** 
** Rhubarb is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** Rhubarb is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with Rhubarb.  If not, see <http://www.gnu.org/licenses/>.
**
************************************************************************/

#include "Helpers/CTextureManager.h"
using namespace rb;

#include "Core/Platform.h"
#include "Core/CEngine.h"

#include <fstream>
#include <iostream>
#include <sstream>

CTextureManager::CTextureManager(void)
{
}

TTexture CTextureManager::GetTexture(std::string Name)
{
	if (m_Textures.count(Name) > 0)
		return m_Textures[Name];

	std::ifstream File;
	File.open(Name.c_str(), std::ios::in | std::ios::binary);

	if (!File.is_open())
		throw Exception::TextureManagerException("Error opening texture file.");

	File.seekg(0, std::ios::end);
	unsigned int FileSize = (unsigned int)File.tellg();
	File.seekg(0, std::ios::beg);

	GLbyte *FileBuffer = new GLbyte[FileSize];

	File.read((char *)FileBuffer, FileSize);
	
	GLuint Width, Height;
	GLenum Format, Components;

	GLbyte *TextureBuffer = ReadTGA(FileBuffer, FileSize, &Width, &Height, &Components, &Format);

	if (TextureBuffer == 0)
		throw Exception::TextureManagerException("Error reading TGA file!");

	std::stringstream Message;
	Message << "Succesfully read texture " << Name << ", " << Width << " by " << Height << " pixels.\n";
	CEngine::Get()->Log(Message.str());

	TTexture Texture;
	glGenTextures(1, &Texture);

	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat Largest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Largest);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Largest);

	glTexImage2D(GL_TEXTURE_2D, 0, Components, Width, Height, 0, Format, GL_UNSIGNED_BYTE, TextureBuffer);
	
	CEngine::Get()->Log("Generating mipmaps...\n");
	glGenerateMipmap(GL_TEXTURE_2D);

	delete [] TextureBuffer;

	m_Textures[Name] = Texture;

	return Texture;
}

GLbyte *CTextureManager::ReadTGA(GLbyte *Data, GLuint DataSize, GLuint *Width, GLuint *Height, GLenum *Components, GLenum *Format)
{
	*Width = 0;
	*Height = 0;
	*Format = GL_RGB;
	*Components = GL_RGB;

	TTGAHeader *Header = (TTGAHeader*)Data;

	*Width = Header->width;
	*Height = Header->height;

	short Depth = Header->bpp / 8;

	if (Depth != 1 && Depth != 3 && Depth != 4)
		return 0;

	GLuint Size = *Width * *Height * Depth;

	GLbyte *Buffer = new GLbyte[Size];

	if (Size > DataSize - sizeof(TTGAHeader))
		return 0;

	memcpy_s(Buffer, Size, Data + sizeof(TTGAHeader), Size);

	switch (Depth)
	{
		case 3:
			*Format = GL_BGR;
			*Components = GL_RGB;
			break;
		case 4:
			*Format = GL_BGRA;
			*Components = GL_RGBA;
			break;
		case 1:
			*Format = GL_LUMINANCE;
			*Components = GL_LUMINANCE;
			break;
	}

	return Buffer;
}

CTextureManager::~CTextureManager(void)
{
}
