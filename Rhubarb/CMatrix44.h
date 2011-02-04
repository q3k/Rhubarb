#pragma once

#include <math.h>

#include "CVector4.h"

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

			void Row(int i, CVector4 &Target);
			void Column(int i, CVector4 &Target);

			float m_Data[16];
	};
}
