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

#include "CObjReader.h"
using namespace rb;

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>

#include "Core/CEngine.h"
#include "Math/CVector4.h"

CObjReader::CObjReader(std::string Filename)
{
	m_Filename = std::string(Filename);
}

void CObjReader::Read(CTriangleMesh &Target)
{
	std::cout << "[i] Reading .obj file " << m_Filename << "..." << std::endl;
	std::ifstream File;
	File.open(m_Filename.c_str(), std::ios::binary | std::ios::in);

	if (!File.is_open())
		throw Exception::ObjReaderException("Can not open file.");

	std::string Keyword;
	std::string Line;

	std::vector<GLuint> IndexInfoList;

	bool SlashMode = false;

	while (!File.eof())
	{
		File >> Keyword;

		if (Keyword == "v")
		{
			GLfloat X, Y, Z;
			File >> X >> Y >> Z;

			m_Vertices.push_back(X);
			m_Vertices.push_back(Y);
			m_Vertices.push_back(Z);
		}
		else if (Keyword == "f")
		{
			std::string Indices[3];
			File >> Indices[0] >> Indices[1] >> Indices[2];

			for (int i = 0; i < 3; i++)
			{
				std::string *Index = &Indices[i];

				if (Index->find('/') != -1)
				{
					SlashMode = true;
					//TODO: Fix this mess (I'm not good with STL).
					std::string::iterator Position = std::find(Index->begin(), Index->end(), '/');
					std::string Vertex(Index->begin(), Position);
					std::string TextureAndNormal(Position + 1, Index->end());

					Position = std::find(TextureAndNormal.begin(), TextureAndNormal.end(), '/');
					std::string TextureVertex(TextureAndNormal.begin(), Position);
					std::string Normal(Position + 1, TextureAndNormal.end());

					GLuint VertexInt = atoi(Vertex.c_str());
					GLuint TextureVertexInt = atoi(TextureVertex.c_str());
					GLuint NormalInt = atoi(Normal.c_str());

					//default to TV 0
					if (TextureVertexInt == 0)
						TextureVertexInt = 1;

					IndexInfoList.push_back(VertexInt - 1);
					IndexInfoList.push_back(TextureVertexInt - 1);
					IndexInfoList.push_back(NormalInt - 1);
				}
				else
				{
					if (SlashMode)
						throw Exception::ObjReaderException("Malformed obj file!");

					GLuint Vertex = atoi(Index->c_str());
					IndexInfoList.push_back(Vertex - 1);
				}
			}
			std::getline(File, Line);
		}
		else if (Keyword == "vn")
		{
			GLfloat X, Y, Z;
			File >> X >> Y >> Z;

			m_Normals.push_back(X);
			m_Normals.push_back(Y);
			m_Normals.push_back(Z);
			std::getline(File, Line);
		}
		else if (Keyword == "t" || Keyword == "vt")
		{
			GLfloat S, T;
			File >> S >> T;

			m_TextureVertices.push_back(S);
			m_TextureVertices.push_back(T);
			std::getline(File, Line);
		}
		else
			std::getline(File, Line);
	}

	std::vector<GLuint>::iterator it;
	GLfloat ZeroTexture[] = {0.0f, 0.0f};
	Target.Begin(IndexInfoList.size());
	if (SlashMode)
	{
		for (it = IndexInfoList.begin(); it < IndexInfoList.end() ; it += 3)
		{
			GLuint VertexIndex = *it;
			GLuint TextureVertexIndex = *(it + 1);
			GLuint NormalIndex = *(it + 2);

			CVector4 *Vertex = (CVector4 *)&m_Vertices[VertexIndex * 3];

			GLfloat *TextureVertex;
			if (m_TextureVertices.size() > TextureVertexIndex * 2)
				TextureVertex = &m_TextureVertices[TextureVertexIndex * 2];
			else
				TextureVertex = (GLfloat*)&ZeroTexture;

			CVector4 *Normal = (CVector4 *)&m_Normals[NormalIndex * 3];

			Target.AddIndex(*Vertex, *Normal, TextureVertex);
		}
	}
	else
	{
		for (it = IndexInfoList.begin(); it < IndexInfoList.end() ; it ++)
		{
			GLuint VertexIndex = *it;

			CVector4 *Vertex = (CVector4 *)&m_Vertices[VertexIndex * 3];

			GLfloat *TextureVertex;
			if (m_TextureVertices.size() > VertexIndex * 2)
				TextureVertex = &m_TextureVertices[VertexIndex * 2];
			else
				TextureVertex = (GLfloat*)&ZeroTexture;

			CVector4 *Normal = (CVector4 *)&m_Normals[VertexIndex * 3];

			Target.AddIndex(*Vertex, *Normal, TextureVertex);
		}
	}
	Target.End();

	std::stringstream Message;
	Message << "Succesfully read " << m_Vertices.size() / 3 << " vertices and " << IndexInfoList.size() / (SlashMode ? 9 : 3) << " faces.\n";

	CEngine::Get()->Log(Message.str());
}

CObjReader::~CObjReader(void)
{
}
