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

#include <GL/glew.h>
#include <GL/GL.h>

#include "Math/CVector4.h"

#include <string>

namespace rb
{
	class CTriangleMesh
	{
		public:
			CTriangleMesh(void);
			~CTriangleMesh(void);

			//Automatic detection of duplicate vertices, immediate mode
			void Begin(GLint NumberVertices);

			inline void AddIndex(CVector4 &Vertex, CVector4 &Normal, GLfloat NewTextureVertex[2])
			{
				GLfloat *NewVertex = Vertex.m_Data;

				CVector4 NormalizedNormal;
				Normal.Normalize(NormalizedNormal);
				GLfloat *NewNormal = NormalizedNormal.m_Data;

				//each vertex from current vertex list.
				GLuint j = 0;
				for (j = 0; j < m_VertexCount / 3; j++)
				{
					GLfloat *OldVertex = m_Vertices + j * 3;
					GLfloat *OldNormal = m_Normals + j * 3;
					GLfloat *OldTextureVertex = m_TextureVertices + j * 2;

					if (CompareVectors(NewVertex, OldVertex) &&
						CompareVectors(NewNormal, OldNormal) &&
						CompareTextureVertices(NewTextureVertex, OldTextureVertex))
					{
						m_Indices[m_IndexCount] = j;
						m_IndexCount++;
						break;
					}
				}

				if (j == m_VertexCount / 3 && m_VertexCount / 3 < m_Maximum)
				{
					//std::cout << "Adding vertex..." << std::endl;
					memcpy_s(m_Vertices + m_VertexCount, sizeof(GLfloat) * 3, NewVertex, sizeof(GLfloat) * 3);
					memcpy_s(m_Normals + m_VertexCount, sizeof(GLfloat) * 3, NewNormal, sizeof(GLfloat) * 3);
					memcpy_s(m_TextureVertices + (m_VertexCount / 3) * 2, sizeof(GLfloat) * 2, NewTextureVertex, sizeof(GLfloat) * 2);

					m_Indices[m_IndexCount] = m_VertexCount / 3;
					m_IndexCount++;
					m_VertexCount += 3;
				}
			}
			inline void CTriangleMesh::AddTriangle(CVector4 Vertices[3], CVector4 Normals[3], GLfloat TextureVertices[6])
{
	for (GLuint i = 0; i < 3; i++)
		AddIndex(Vertices[i], Normals[i], &TextureVertices[i * 2]);
}
			void End(void);

			//Direct index and vertex list
			void ReadLists(GLushort *Indices, GLuint NumberIndices, GLfloat *Vertices, GLuint NumberVertices, GLfloat *Normals);

			void LoadFromObj(std::string File);

			void Draw(void);
		private:
			GLushort *m_Indices;
			GLfloat *m_Vertices;
			GLfloat *m_Normals;
			GLfloat *m_TextureVertices;

			GLuint m_Maximum;

			GLuint m_IndexCount;
			GLuint m_VertexCount;

			GLuint m_VertexObject;
			GLuint m_VertexArray;
			GLuint m_IndexArray;
			GLuint m_NormalArray;
			GLuint m_TextureVertexArray;

			inline bool CTriangleMesh::CompareVectors(GLfloat *VertexA, GLfloat *VertexB)
			{
				const GLfloat Error = 0.0001f;
				if (abs(VertexA[0]  - VertexB[0]) <= Error &&
					abs(VertexA[1]  - VertexB[1]) <= Error &&
					abs(VertexA[2]  - VertexB[2]) <= Error)
					return true;
				else
					return false;
			}
			inline bool CTriangleMesh::CompareTextureVertices(GLfloat *VertexA, GLfloat *VertexB)
			{
				const GLfloat Error = 0.0001f;
				if (abs(VertexA[0]  - VertexB[0]) <= Error &&
					abs(VertexA[1]  - VertexB[1]) <= Error)
					return true;
				else
					return false;
			}
	};
};
