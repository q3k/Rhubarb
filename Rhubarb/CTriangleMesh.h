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

			void Begin(GLint NumberVertices);
			void AddTriangle(CVector4 Vertices[3]);
			void End(void);

			void Draw(void);
		private:
			GLushort *m_Indices;
			GLfloat *m_Vertices;

			GLuint m_Maximum;
			GLuint m_CurrentIndex;
			GLuint m_CurrentVertex;

			GLuint m_VertexObject;
			GLuint m_VertexArray;
			GLuint m_IndexArray;

			bool CompareVectors(GLfloat *VertexA, GLfloat *VertexB);
	};
};