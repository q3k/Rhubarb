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

#include "CVector4.h"

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
			void AddIndex(CVector4 &Vertex, CVector4 &Normal, GLfloat TextureVertex[2]);
			void AddTriangle(CVector4 Vertices[3], CVector4 Normals[3], GLfloat TextureVertices[6]);
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

			bool CompareVectors(GLfloat *VertexA, GLfloat *VertexB);
			bool CompareTextureVertices(GLfloat *VertexA, GLfloat *VertexB);
	};
};
