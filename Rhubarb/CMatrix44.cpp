#include "CMatrix44.h"
using namespace rb;

CMatrix44::CMatrix44(void)
{
	Identity();
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

    #define M(col,row)  m_Data[col*4+row]

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
	#define M(col, row)  m_Data[col*4+row]

	M(3, 0) = X;
	M(3, 1) = Y;
	M(3, 2) = Z;
	M(3, 3) = 1.0f;

	#undef M
}

void CMatrix44::Scale(float X, float Y, float Z)
{
	#define M(col, row)  m_Data[col*4+row]

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

	#define M(col,row)  m_Data[col*4+row]

	M(0, 0) = 1.0f;
	M(1, 1) = 1.0f;
	M(2, 2) = 1.0f;
	M(3, 3) = 1.0f;

	#undef M
}

void CMatrix44::Multiply(CMatrix44 &Matrix)
{
	CMatrix44 NewMatrix;

	#define L(col,row) m_Data[col*4+row]
	#define R(col,row) Matrix.m_Data[col*4+row]
	#define D(col,row) NewMatrix.m_Data[col*4+row]

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			D(i, j) = L(0, j) * R(i, 0) + L(1, j) * R(i, 1) + L(2, j) * R(i, 2) + L(3, j) * R(i, 3);
		}
	}


	for (int i = 0; i < 16; i++)
		m_Data[i] = NewMatrix.m_Data[i];

	#undef L
	#undef R
	#undef D
}

void CMatrix44::Multiply(CMatrix44 &Matrix, CMatrix44 &Target)
{
	for (int i = 0; i < 16; i++)
		Target.m_Data[i] = m_Data[i];

	Target.Multiply(Matrix);
}

void CMatrix44::Multiply(CVector4 &Vector, CVector4 &Target)
{
	#define M(col,row) m_Data[col*4+row]
	for (int i = 0; i < 4; i++)
	{
		Target.m_Data[i] = M(i, 0) * Vector.m_Data[0] + M(i, 1) * Vector.m_Data[1] + M(i, 2) * Vector.m_Data[2] + M(i, 3) * Vector.m_Data[3];
	}
	#undef M
}

void CMatrix44::Row(int i, CVector4 &Target)
{
	Target.m_Data[0] = m_Data[0 + i];
	Target.m_Data[1] = m_Data[4 + i];
	Target.m_Data[2] = m_Data[8 + i];
	Target.m_Data[3] = m_Data[12 + i];
}

void CMatrix44::Column(int i, CVector4 &Target)
{
	for (int j = 0; j < 4; j++)
		Target.m_Data[j] = m_Data[j + i * 4];
}

void CMatrix44::SetColumn(int i, CVector4 &Vector)
{
	for (int j = 0; j < 4; j++)
		m_Data[i*4 + j] = Vector.m_Data[0];
}

CMatrix44::~CMatrix44(void)
{
}
