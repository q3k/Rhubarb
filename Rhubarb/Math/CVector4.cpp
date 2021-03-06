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

#include "Math/CVector4.h"
using namespace rb;

#include <math.h>

CVector4::CVector4(void)
{
	m_Data[0] = 0.0f;
	m_Data[1] = 0.0f;
	m_Data[2] = 0.0f;
	m_Data[3] = 1.0f;
}

CVector4::CVector4(GLfloat X, GLfloat Y, GLfloat Z)
{
	m_Data[0] = X;
	m_Data[1] = Y;
	m_Data[2] = Z;
	m_Data[3] = 1.0f;
}

CVector4::~CVector4(void)
{
}

float CVector4::Dot(CVector4 &Vector)
{
	float Result = 0.0f;
	for (int i = 0; i < 4; i++)
		Result += m_Data[i] * Vector.m_Data[i];

	return Result;
}

void CVector4::Cross(CVector4 &Vector, CVector4 &Target)
{
	Target.m_Data[0] = m_Data[1] * Vector.m_Data[2] - m_Data[2] * Vector.m_Data[1];
	Target.m_Data[1] = m_Data[2] * Vector.m_Data[0] - m_Data[0] * Vector.m_Data[2];
	Target.m_Data[2] = m_Data[0] * Vector.m_Data[1] - m_Data[1] * Vector.m_Data[0];
	Target.m_Data[3] = 1.0f;
}

void CVector4::Add(CVector4 &Vector, CVector4 &Target)
{
	for (int i = 0; i < 4; i++)
		Target.m_Data[i] = m_Data[i] + Vector.m_Data[i];
	Target.m_Data[3] = 1.0f;
}

void CVector4::Subtract(CVector4 &Vector, CVector4 &Target)
{
	for (int i = 0; i < 4; i++)
		Target.m_Data[i] = m_Data[i] - Vector.m_Data[i];
	Target.m_Data[3] = 1.0f;
}

void CVector4::Add(CVector4 &Vector)
{
	for (int i = 0; i < 4; i++)
		m_Data[i] += Vector.m_Data[i];
	m_Data[3] = 1.0f;
}

void CVector4::Subtract(CVector4 &Vector)
{
	for (int i = 0; i < 4; i++)
		m_Data[i] -= Vector.m_Data[i];
	m_Data[3] = 1.0f;
}

GLfloat CVector4::Length(void)
{
	return sqrtf(m_Data[0] * m_Data[0] + m_Data[1] * m_Data[1] + m_Data[2] * m_Data[2]);
}

GLfloat CVector4::LengthSquared(void)
{
	return m_Data[0] * m_Data[0] + m_Data[1] * m_Data[1] + m_Data[2] * m_Data[2];
}

void CVector4::Normalize(void)
{
	GLfloat _Length = Length();

	if (_Length == 0.0f)
		return;

	m_Data[0] /= _Length;
	m_Data[1] /= _Length;
	m_Data[2] /= _Length;
}

void CVector4::Normalize(CVector4 &Target)
{
	GLfloat _Length = Length();

	//Ugly fix.
	if (_Length == 0.0f)
		_Length = 1.0f;

	Target.m_Data[0] = m_Data[0] / _Length;
	Target.m_Data[1] = m_Data[1] / _Length;
	Target.m_Data[2] = m_Data[2] / _Length;
}