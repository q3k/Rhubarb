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

#include "CCamera.h"
using namespace rb;

CCamera::CCamera(void)
{
	ResetRotation();
}

void CCamera::LookAt(CVector4 &Target)
{
	CVector4 Forward;
	Target.Subtract(m_Position, Forward);
	Forward.Normalize();
	Forward.m_Data[3] = 1.0f;

	CVector4 WorldUp;
	WorldUp.m_Data[1] = 1.0f;
	WorldUp.m_Data[3] = 1.0f;

	CVector4 Right;
	WorldUp.Cross(Forward, Right);
	Right.Normalize();
	Right.m_Data[3] = 1.0f;

	CVector4 Up;
	Forward.Cross(Right, Up);
	Up.Normalize();
	Up.m_Data[3] = 1.0f;

	for (int i = 0; i < 4; i++)
		m_Forward.m_Data[i] = Forward.m_Data[i];

	for (int i = 0; i < 4; i++)
		m_Up.m_Data[i] = Up.m_Data[i];
}

void CCamera::GetCameraMatrix(CMatrix44 &Matrix)
{
	CVector4 Forward;
	Forward.m_Data[0] = -m_Forward.m_Data[0];
	Forward.m_Data[1] = -m_Forward.m_Data[1];
	Forward.m_Data[2] = -m_Forward.m_Data[2];

	CVector4 Right;
	m_Up.Cross(Forward, Right);

	//Transposed matrix
	#define M(row, col)  Matrix.m_Data[col*4+row]
		M(0, 0) = Right.m_Data[0];
		M(0, 1) = Right.m_Data[1];
		M(0, 2) = Right.m_Data[2];
		M(0, 3) = 0.0;
		M(1, 0) = m_Up.m_Data[0];
		M(1, 1) = m_Up.m_Data[1];
		M(1, 2) = m_Up.m_Data[2];
		M(1, 3) = 0.0;
		M(2, 0) = Forward.m_Data[0];
		M(2, 1) = Forward.m_Data[1];
		M(2, 2) = Forward.m_Data[2];
		M(2, 3) = 0.0;
		M(3, 0) = 0.0;
		M(3, 1) = 0.0;
		M(3, 2) = 0.0;
		M(3, 3) = 1.0;
	#undef M

	CMatrix44 Translation;
	Translation.Translation(-m_Position.m_Data[0], -m_Position.m_Data[1], -m_Position.m_Data[2]);

	Matrix.Multiply(Translation);
}

void CCamera::GetCameraMatrix(GLfloat *Matrix)
{
	CMatrix44 Temp;
	GetCameraMatrix(Temp);

	for (int i = 0; i < 16; i++)
		Matrix[i] = Temp.m_Data[i];
}

CCamera::~CCamera(void)
{
}
