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

#include "Core/CEntity.h"
using namespace rb;

CEntity::CEntity(void)
{
	ResetRotation();
	m_TempMatrix = new GLfloat[16];
}

void CEntity::ResetRotation(void)
{
	m_Position.m_Data[0] = 0.0f;
	m_Position.m_Data[1] = 0.0f;
	m_Position.m_Data[2] = 0.0f;
	m_Position.m_Data[3] = 1.0f;

	m_Up.m_Data[0] = 0.0f;
	m_Up.m_Data[1] = 1.0f;
	m_Up.m_Data[2] = 0.0f;
	m_Up.m_Data[3] = 1.0f;

	m_Forward.m_Data[0] = 0.0f;
	m_Forward.m_Data[1] = 0.0f;
	m_Forward.m_Data[2] = 1.0f;
	m_Forward.m_Data[3] = 1.0f;
}

void CEntity::SetPosition(CVector4 &Vector)
{
	for (int i = 0; i < 4; i++)
		m_Position.m_Data[i] = Vector.m_Data[i];
}

void CEntity::SetPosition(GLfloat X, GLfloat Y, GLfloat Z)
{
	m_Position.m_Data[0] = X;
	m_Position.m_Data[1] = Y;
	m_Position.m_Data[2] = Z;
}

void CEntity::GetPosition(CVector4 &Position)
{
	for (int i = 0; i < 4; i++)
		Position.m_Data[i] = m_Position.m_Data[i];
}

void CEntity::GetPosition(GLfloat *Position)
{
	for (int i = 0; i < 3; i++)
		Position[i] = m_Position.m_Data[i];
}

GLfloat CEntity::GetX(void)
{
	return m_Position.m_Data[0];
}

GLfloat CEntity::GetY(void)
{
	return m_Position.m_Data[1];
}

GLfloat CEntity::GetZ(void)
{
	return m_Position.m_Data[2];
}

void CEntity::TranslateWorld(GLfloat X, GLfloat Y, GLfloat Z)
{
	m_Position.m_Data[0] += X;
	m_Position.m_Data[1] += Y;
	m_Position.m_Data[2] += Z;
}

void CEntity::TranslateLocal(GLfloat X, GLfloat Y, GLfloat Z)
{
	MoveForward(Z);
	MoveUp(Y);
	MoveRight(X);
}

void CEntity::MoveForward(GLfloat Amount)
{
	for (int i = 0; i < 3; i++)
		m_Position.m_Data[i] += m_Forward.m_Data[i] * Amount;
}

void CEntity::MoveUp(GLfloat Amount)
{
	for (int i = 0; i < 3; i++)
		m_Position.m_Data[i] += m_Up.m_Data[i] * Amount;
}

void CEntity::MoveRight(GLfloat Amount)
{
	CVector4 Right;
	m_Up.Cross(m_Forward, Right);

	for (int i = 0; i < 3; i++)
		m_Position.m_Data[i] += Right.m_Data[i] * Amount;
}

void CEntity::GetMatrix(CMatrix44 &Matrix)
{
	CVector4 Right;
	m_Up.Cross(m_Forward, Right);

	Matrix.SetColumn(0, Right);
	Matrix.SetColumn(1, m_Up);
	Matrix.SetColumn(2, m_Forward);
	Matrix.SetColumn(3, m_Position);

	//set the 4th components, just to be sure
	Matrix.m_Data[3] = 0.0f;
	Matrix.m_Data[7] = 0.0f;
	Matrix.m_Data[11] = 0.0f;
	Matrix.m_Data[15] = 1.0f;
}

const GLfloat *CEntity::GetMatrix(void)
{
	GetMatrix(m_TempMatrix);
	return m_TempMatrix;
}

void CEntity::GetMatrix(GLfloat *Matrix)
{
	CMatrix44 Temporary;
	GetMatrix(Temporary);

	for (int i = 0; i < 16; i++)
		Matrix[i] = Temporary.m_Data[i];
}

void CEntity::RotateWorld(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z)
{
	CMatrix44 Rotation;
	Rotation.Rotation(Angle, X, Y, Z);

	CVector4 NewUp;
	Rotation.Multiply(m_Up, NewUp);

	CVector4 NewForward;
	Rotation.Multiply(m_Forward, NewForward);

	for (int i = 0; i < 4; i++)
		m_Up.m_Data[i] = NewUp.m_Data[i];

	for (int i = 0; i < 4; i++)
		m_Forward.m_Data[i] = NewForward.m_Data[i];
}

void CEntity::RotateLocal(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z)
{
	CVector4 Local;
	Local.m_Data[0] = X;
	Local.m_Data[1] = Y;
	Local.m_Data[2] = Z;

	CMatrix44 Rotation;
	GetMatrix(Rotation);

	//disable translation component in transform matrix
	CVector4 ZeroVector;
	Rotation.SetColumn(3, ZeroVector);

	CVector4 World;
	Rotation.Multiply(Local, World);

	RotateWorld(Angle, World.m_Data[0], World.m_Data[1], World.m_Data[2]);
}

CEntity::~CEntity(void)
{
	delete [] m_TempMatrix;
}
