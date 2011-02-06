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

namespace rb
{
	class CMesh
	{
		public:
			CMesh(void);
			~CMesh(void);

			//Raw access mode (a.k.a. FEED ME FLOATS)
			void Begin(GLenum Primitive, GLuint NumberVertices);
			void End();
			void CopyVertexData(float *Data);

			void Draw(void);
		private:
			GLenum m_Primitive;

			GLuint m_VertexArray;
			GLuint m_NumVertices;

			GLuint m_VertexArrayObject;

			bool m_BeingFed;
	};
};
