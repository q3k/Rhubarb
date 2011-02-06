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

#include <string>
#include <vector>
#include <exception>

#include <GL/glew.h>
#include <GL/GL.h>

#include "Core/CTriangleMesh.h"

namespace rb
{
	namespace Exception
	{
		class ObjReaderException : public std::exception
		{
			public:
				ObjReaderException(const std::string Error) { m_Error = std::string(Error); }
				~ObjReaderException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};
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
			std::vector<GLfloat> m_TextureVertices;

			std::string m_Filename;
	};
};

