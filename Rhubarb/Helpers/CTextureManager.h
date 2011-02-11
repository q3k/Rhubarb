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

#pragma once

#include <map>
#include <string>
#include <exception>

#include <GL/glew.h>
#include <GL/gl.h>

namespace rb
{
	namespace Exception
	{
		class TextureManagerException : public std::exception
		{
			public:
				TextureManagerException(const std::string Error) { m_Error = std::string(Error); }
				~TextureManagerException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};

	typedef GLuint TTexture;

#pragma pack(1)
	typedef struct
	{
		GLbyte identsize;
		GLbyte colormaptype;
		GLbyte imagetype;

		GLushort colormapstart;
		GLushort colormaplength;
		GLbyte colormapbits;

		GLushort xstart;
		GLushort ystart;
		GLushort width;
		GLushort height;

		GLbyte bpp;
		GLbyte descriptor;
	} TTGAHeader;
#pragma pack(8)

	class CTextureManager
	{
		public:
			CTextureManager(void);
			~CTextureManager(void);

			TTexture GetTexture(std::string Name);
		private:
			std::map<std::string, TTexture> m_Textures;

			GLbyte *ReadTGA(GLbyte *Data, GLuint DataSize, GLuint *Width, GLuint *Height, GLenum *Components, GLenum *Format);
	};
};
