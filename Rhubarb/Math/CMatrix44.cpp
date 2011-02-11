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

#include "Core/Platform.h"
#include "Math/CMatrix44.h"
using namespace rb;

#include <string.h>

CMatrix44::CMatrix44(void)
{
	Identity();
}

CMatrix44::CMatrix44(GLfloat *Matrix)
{
	memcpy_s(m_Data, 16, Matrix, 16);
}

void CMatrix44::Rotation(float Angle, float X, float Y, float Z)
{
	float Length, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;


	s = float(sin(Angle));
	c = float(cos(Angle));

	Length = float(sqrt(X * X + Y * Y + Z * Z));

	if (Length == 0.0f)
		return;

	// Rotation matrix is normalized
	X /= Length;
	Y /= Length;
	Z /= Length;

    #define M(row, col)  m_Data[col*4+row]

	xx = X * X;
	yy = Y * Y;
	zz = X * X;
	xy = X * Y;
	yz = Y * Z;
	zx = Z * X;
	xs = X * s;
	ys = Y * s;
	zs = Z * s;
	one_c = 1.0f - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;
	M(0,3) = 0.0f;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;
	M(1,3) = 0.0f;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;
	M(2,3) = 0.0f;

	M(3,0) = 0.0f;
	M(3,1) = 0.0f;
	M(3,2) = 0.0f;
	M(3,3) = 1.0f;

    #undef M
}

void CMatrix44::Translation(float X, float Y, float Z)
{
	#define M(row, col)  m_Data[col*4+row]

	M(0, 3) = X;
	M(1, 3) = Y;
	M(2, 3) = Z;
	M(3, 3) = 1.0f;

	#undef M
}

void CMatrix44::Scale(float X, float Y, float Z)
{
	#define M(row, col)  m_Data[col*4+row]

	M(0, 0) = X;
	M(1, 1) = Y;
	M(2, 2) = Z;
	M(3, 3) = 1.0f;

	#undef M
}

void CMatrix44::Identity(void)
{
	for (int i = 0; i < 16; i++)
		m_Data[i] = 0.0f;

	#define M(row, col)  m_Data[col*4+row]

	M(0, 0) = 1.0f;
	M(1, 1) = 1.0f;
	M(2, 2) = 1.0f;
	M(3, 3) = 1.0f;

	#undef M
}

void CMatrix44::Multiply(CMatrix44 &Matrix)
{
	CMatrix44 NewMatrix;

	#define A(row,col) m_Data[(col<<2)+row]
	#define B(row,col) Matrix.m_Data[(col<<2)+row]
	#define P(row,col) NewMatrix.m_Data[(col<<2)+row]

	for (int i = 0; i < 4; i++) {
		float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	}


	for (int i = 0; i < 16; i++)
		m_Data[i] = NewMatrix.m_Data[i];

	#undef A
	#undef B
	#undef P
}

void CMatrix44::Multiply(CMatrix44 &Matrix, CMatrix44 &Target)
{
	for (int i = 0; i < 16; i++)
		Target.m_Data[i] = m_Data[i];

	Target.Multiply(Matrix);
}

void CMatrix44::Multiply(CVector4 &Vector, CVector4 &Target)
{
	Target.m_Data[0] = m_Data[0] * Vector.m_Data[0] + m_Data[4] * Vector.m_Data[1] + m_Data[8] *  Vector.m_Data[2] + m_Data[12] * Vector.m_Data[3];	 
    Target.m_Data[1] = m_Data[1] * Vector.m_Data[0] + m_Data[5] * Vector.m_Data[1] + m_Data[9] *  Vector.m_Data[2] + m_Data[13] * Vector.m_Data[3];	
    Target.m_Data[2] = m_Data[2] * Vector.m_Data[0] + m_Data[6] * Vector.m_Data[1] + m_Data[10] * Vector.m_Data[2] + m_Data[14] * Vector.m_Data[3];	
	Target.m_Data[3] = m_Data[3] * Vector.m_Data[0] + m_Data[7] * Vector.m_Data[1] + m_Data[11] * Vector.m_Data[2] + m_Data[15] * Vector.m_Data[3];
}

void CMatrix44::Column(int i, CVector4 &Target)
{
	memcpy_s(Target.m_Data, 4 * sizeof(float), m_Data + 4 * i, 4 * sizeof(float)); 
}

void CMatrix44::SetColumn(int i, CVector4 &Vector)
{
	memcpy_s(m_Data + 4 * i, 4 * sizeof(float), Vector.m_Data, 4 * sizeof(float)); 
}

CMatrix44::~CMatrix44(void)
{
}
