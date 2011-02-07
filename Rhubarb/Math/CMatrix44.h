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

#include <math.h>

#include "Math/CVector4.h"

namespace rb
{
	class CMatrix44
	{
		public:
			CMatrix44(void);
			~CMatrix44(void);

			//This overwrites the existing data
			void Rotation(float Angle, float X, float Y, float Z);
			void Translation(float X, float Y, float Z);
			void Scale(float X, float Y, float Z);
			void Identity(void);

			void Multiply(CMatrix44 &Matrix);
			void Multiply(CMatrix44 &Matrix, CMatrix44 &Target);
			void Multiply(CVector4 &Vector, CVector4 &Target);

			void Column(int i, CVector4 &Target);

			void SetColumn(int i, CVector4 &Vector);

			float m_Data[16];
	};
}
