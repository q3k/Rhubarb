#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GL.h>

#include "CTriangleMesh.h"

namespace rb
{
	class CObjReader
	{
		public:
			CObjReader(std::string Filename);
			~CObjReader(void);

			void Read(CTriangleMesh &Target);
		private:
			std::vector<GLushort> m_Indices;
			std::vector<GLfloat> m_Vertices;
			std::vector<GLfloat> m_Normals;

			std::string m_Filename;
	};
};

