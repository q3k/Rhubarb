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

#include <assert.h>
#include <string.h>

#include "CMatrixManager.h"
using namespace rb;

CMatrixManager::CMatrixManager(unsigned int StackSize)
{
	m_StackBottom = new float[StackSize * 4];
	m_StackPointer = m_StackBottom;
	m_MaxSize = StackSize;
	m_ProjectionMatrix = new CMatrix44();
	m_MVPMatrix = new CMatrix44();

	PushIdentity();
}

void CMatrixManager::PushIdentity(void)
{
	if (!CanAllocate())
		throw Exception::MatrixManagerException("Not enough space on the matrix stack! Go slap a programmer.");

	CMatrix44 *Matrix = (CMatrix44*)m_StackPointer;
	Matrix->Identity();
	m_StackPointer += 16;
}

void CMatrixManager::Push(CMatrix44 &Matrix)
{
	if (!CanAllocate())
		throw Exception::MatrixManagerException("Not enough space on the matrix stack! Go slap a programmer.");

	memcpy_s(m_StackPointer, 64, Matrix.m_Data, 64);
	m_StackPointer += 16;
}

void CMatrixManager::Push(const GLfloat *Matrix)
{
	if (!CanAllocate())
		throw Exception::MatrixManagerException("Not enough space on the matrix stack! Go slap a programmer.");

	memcpy_s(m_StackPointer, 64, Matrix, 64);
	m_StackPointer += 16;
}

void CMatrixManager::Push(CCamera &Camera)
{
	if (!CanAllocate())
		throw Exception::MatrixManagerException("Not enough space on the matrix stack! Go slap a programmer.");

	CMatrix44 CameraMatrix;
	Camera.GetCameraMatrix(CameraMatrix);

	memcpy_s(m_StackPointer, 64, CameraMatrix.m_Data, 64);
	m_StackPointer += 16;
}

void CMatrixManager::Push(void)
{
	if (!CanAllocate())
		throw Exception::MatrixManagerException("Not enough space on the matrix stack! Go slap a programmer.");

	CMatrix44 *OldMatrix = (CMatrix44*)(m_StackPointer - 16);
	CMatrix44 *NewMatrix = (CMatrix44*)(m_StackPointer);
	memcpy_s(NewMatrix, 64, OldMatrix, 64);
	m_StackPointer += 16;
}

void CMatrixManager::Pop(void)
{
	if (m_StackPointer - 16 < m_StackBottom)
		throw Exception::MatrixManagerException("You are trying to pop something that isn't there. Go slap a programmer.");

	m_StackPointer -= 16;
}

bool CMatrixManager::CanAllocate(void)
{
	return (((unsigned int)m_StackPointer - (unsigned int)m_StackBottom) <= m_MaxSize * 64 - 64);
}

void CMatrixManager::Multiply(CMatrix44 &Matrix)
{
	CMatrix44 *OldMatrix = (CMatrix44 *)((float*)m_StackPointer - 16);
	OldMatrix->Multiply(Matrix);
}

void CMatrixManager::Multiply(const GLfloat *Matrix)
{
	CMatrix44 *OldMatrix = (CMatrix44 *)((float*)m_StackPointer - 16);
	OldMatrix->Multiply(*(CMatrix44*)Matrix);
}

void CMatrixManager::Translate(GLfloat X, GLfloat Y, GLfloat Z)
{
	CMatrix44 Translation;
	Translation.Translation(X, Y, Z);

	Multiply(Translation);
}

void CMatrixManager::Rotate(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z)
{
	CMatrix44 Rotation;
	Rotation.Rotation(Angle, X, Y, Z);

	Multiply(Rotation);
}

void CMatrixManager::Scale(GLfloat X, GLfloat Y, GLfloat Z)
{
	CMatrix44 Scale;
	Scale.Scale(X, Y, Z);

	Multiply(Scale);
}

void CMatrixManager::SetProjection(CMatrix44 &Matrix)
{
	memcpy_s(m_ProjectionMatrix->m_Data, 64, Matrix.m_Data, 64);
}

void CMatrixManager::SetPerspective(GLfloat FOV, GLfloat AspectRatio, GLfloat Near, GLfloat Far)
{
	CMatrix44 Matrix;

	float yMax = Near * tanf(FOV * 0.5f);
    float yMin = -yMax;
	float xMin = yMin * AspectRatio;
    float xMax = -xMin; 

	Matrix.m_Data[0] = (2.0f * Near) / (xMax - xMin);
	Matrix.m_Data[5] = (2.0f * Near) / (yMax - yMin);
	Matrix.m_Data[8] = (xMax + xMin) / (xMax - xMin);
	Matrix.m_Data[9] = (yMax + yMin) / (yMax - yMin);
	Matrix.m_Data[10] = -((Far + Near) / (Far - Near));
	Matrix.m_Data[11] = -1.0f;
	Matrix.m_Data[14] = -((2.0f * (Far * Near))/(Far - Near));
	Matrix.m_Data[15] = 0.0f;

	memcpy_s(m_ProjectionMatrix->m_Data, 64, Matrix.m_Data, 64);
}

GLfloat *CMatrixManager::GetMVP(void)
{
	m_MVPMatrix->Identity();

	CMatrix44 *MatrixMV = (CMatrix44*)(m_StackPointer - 16);
	m_ProjectionMatrix->Multiply(*MatrixMV, *m_MVPMatrix);

	return (GLfloat *)m_MVPMatrix;
}

GLfloat *CMatrixManager::GetMV(void)
{
	return m_StackPointer - 16;
}

GLfloat *CMatrixManager::GetP(void)
{
	return m_ProjectionMatrix->m_Data;
}

CMatrixManager::~CMatrixManager(void)
{
	delete [] m_StackBottom;
	delete m_ProjectionMatrix;
	delete m_MVPMatrix;
}
