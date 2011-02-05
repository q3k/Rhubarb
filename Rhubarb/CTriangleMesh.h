#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CVector4.h"

namespace rb
{
	class CTriangleMesh
	{
		public:
			CTriangleMesh(void);
			~CTriangleMesh(void);

			//Automatic detection of duplicate vertices, immediate mode
			void Begin(GLint NumberVertices);
			void AddTriangle(CVector4 Vertices[3], CVector4 Normals[3]);
			void End(void);

			//Direct index and vertex list
			void ReadLists(GLushort *Indices, GLuint NumberIndices, GLfloat *Vertices, GLuint NumberVertices, GLfloat *Normals);

			void Draw(void);
		private:
			GLushort *m_Indices;
			GLfloat *m_Vertices;
			GLfloat *m_Normals;

			GLuint m_Maximum;

			GLuint m_IndexCount;
			GLuint m_VertexCount;

			GLuint m_VertexObject;
			GLuint m_VertexArray;
			GLuint m_IndexArray;
			GLuint m_NormalArray;

			bool CompareVectors(GLfloat *VertexA, GLfloat *VertexB);
	};
};
