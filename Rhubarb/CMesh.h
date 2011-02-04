#pragma once

#include <GL/glew.h>

namespace rb
{
	class CMesh
	{
		public:
			CMesh(void);
			~CMesh(void);

			//Raw access mode (a.k.a. FEED ME FLOATS)
			void BeginRaw(GLenum Primitive, GLuint NumberVertices);
			void EndRaw();
			void CopyRawVertexData(float *Data);

			void Draw(void);
		private:
			GLenum m_Primitive;

			GLuint m_VertexArray;
			GLuint m_NumVertices;

			GLuint m_VertexArrayObject;

			bool m_BeingFed;
	};
};
