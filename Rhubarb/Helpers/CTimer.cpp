#include "Helpers/CTimer.h"
using namespace rb;

CTimer::CTimer(void)
{
#ifdef _WIN32
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_Last);
#else
	gettimeofday(&m_Last, 0);
#endif
}

void CTimer::Start(void)
{
#ifdef _WIN32
	QueryPerformanceCounter(&m_Last);
#else
	gettimeofday(&m_Last, 0);
#endif
}

float CTimer::GetElapsedSeconds(void)
{
#ifdef _WIN32
	LARGE_INTEGER Current;
	QueryPerformanceCounter(&Current);

	return float((Current.QuadPart - m_Last.QuadPart) / double(m_Frequency.QuadPart));
#else
	timeval Current;
	gettimeofday(&Current, 0);
	float Seconds = (float)(Current.tv_sec - m_Last.tv_sec);
	float Fraction = (float)(Current.tv_usec - m_Last.tv_usec) * 0.000001f;
	return Seconds + Fraction;
#endif
}

CTimer::~CTimer(void)
{
}
