#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace rb
{
	class CTimer
	{
		public:
			CTimer(void);
			~CTimer(void);

			void Start(void);
			float GetElapsedSeconds(void);
		private:
#ifdef _WIN32
			LARGE_INTEGER m_Frequency;
			LARGE_INTEGER m_Last;
#else
			timeval m_Last;
#endif
	};
};
