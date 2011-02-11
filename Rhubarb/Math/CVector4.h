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
#include <GL/gl.h>

namespace rb
{
	class CVector4
	{
		public:
			CVector4(void);
			CVector4(GLfloat X, GLfloat Y, GLfloat Z);
			~CVector4(void);

			float Dot(CVector4 &Vector);
			void Cross(CVector4 &Vector, CVector4 &Target);

			void Add(CVector4 &Vector, CVector4 &Target);
			void Subtract(CVector4 &Vector, CVector4 &Target);
			
			void Add(CVector4 &Vector);
			void Subtract(CVector4 &Vector);

			void Normalize(void);
			void Normalize(CVector4 &Target);

			GLfloat Length(void);
			GLfloat LengthSquared(void);

			float m_Data[4];
	};
}

