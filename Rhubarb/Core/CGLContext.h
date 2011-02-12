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

#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace rb
{
	typedef void(*TResizeFunction)(int, int);

	class CGLContext
	{
		public:
			CGLContext(std::string Title, unsigned int Width, unsigned int Heightm);
			~CGLContext(void);

			void Flip(void);
			void ProcessEvents(void);
			bool GetOpen(void);

			void SetResizeFunction(TResizeFunction Function);
		private:
			bool m_Open;
			unsigned int m_Width;
			unsigned int m_Height;
			TResizeFunction m_ResizeFunction;

#ifdef _WIN32
			HWND m_Window;
			HDC m_DC;
			HGLRC m_Context;

			LRESULT HandleWindowEvent(UINT Message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowEvent(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
#endif
	};
};

