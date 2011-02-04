#include "CVector4.h"
using namespace rb;

CVector4::CVector4(void)
{
	m_Data[0] = 0.0f;
	m_Data[1] = 0.0f;
	m_Data[2] = 0.0f;
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
	Target.m_Data[0] = m_Data[1] * Target.m_Data[2] - m_Data[2] * Target.m_Data[1];
	Target.m_Data[1] = m_Data[2] * Target.m_Data[0] - m_Data[0] * Target.m_Data[2];
	Target.m_Data[2] = m_Data[0] * Target.m_Data[1] - m_Data[1] * Target.m_Data[0];
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

void CVector4::Normalize(void)
{

}