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

#include "CGLContext.h"
using namespace rb;

#include "Core/CEngine.h"
#include <sstream>

#ifdef _WIN32
#include <GL/wglew.h>
#endif

CGLContext::CGLContext(std::string Title, unsigned int Width, unsigned int Height)
{
#ifdef _WIN32
	WNDCLASSEX WindowClass;
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc = WindowEvent;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "RhubarbGLWindow";
	WindowClass.hInstance = 0;
	RegisterClassEx(&WindowClass);

	RECT DesktopSize;
	GetClientRect(GetDesktopWindow(), &DesktopSize);

	RECT WindowSize;
	WindowSize.left = 0;
	WindowSize.top = 0;
	WindowSize.right = Width;
	WindowSize.bottom = Height;
	AdjustWindowRect(&WindowSize, WS_OVERLAPPEDWINDOW, false);

	unsigned int RealWidth = WindowSize.right - WindowSize.left;
	unsigned int RealHeight = WindowSize.bottom - WindowSize.top;

	//Temporary window to get context.
	m_Window = CreateWindowEx(	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
								"RhubarbGLWindow",
								Title.c_str(),
								WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								(DesktopSize.right - RealWidth) / 2,
								(DesktopSize.bottom - RealHeight) / 2,
								RealWidth,
								RealHeight,
								NULL,
								NULL,
								GetModuleHandle(NULL),
								this);

	m_DC = GetDC(m_Window);
	PIXELFORMATDESCRIPTOR FormatDescriptor;
	SetPixelFormat(m_DC, 1, &FormatDescriptor);
	m_Context = wglCreateContext(m_DC);
	wglMakeCurrent(m_DC, m_Context);

	if (m_DC == 0 || m_Context == 0)
		CEngine::Get()->Fatal("Win32Context: Could not create dummy OpenGL context.");

	GLenum Error = glewInit();
	if (Error != GLEW_OK)
		CEngine::Get()->Fatal("Win32Context: Could not initialize GLEW.");

	const GLubyte *GLVersion = glGetString(GL_VERSION);
	CEngine::Get()->Log(std::string("Win32Context: OpenGL version ") + std::string((char *)GLVersion) + "\n");
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_Context);
	ReleaseDC(m_Window, m_DC);
	DestroyWindow(m_Window);

	//Real context
	m_Window = CreateWindowEx(	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
								"RhubarbGLWindow",
								Title.c_str(),
								WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								(DesktopSize.right - RealWidth) / 2,
								(DesktopSize.bottom - RealHeight) / 2,
								RealWidth,
								RealHeight,
								NULL,
								NULL,
								GetModuleHandle(NULL),
								this);
	m_DC = GetDC(m_Window);

	int Formats = 0;
	int Format = -1;

	int Attributes[] = {
		WGL_SUPPORT_OPENGL_ARB, 1,
		WGL_DRAW_TO_WINDOW_ARB, 1,
		WGL_ACCELERATION_ARB, 1,
		WGL_COLOR_BITS_ARB, 24,
		WGL_DEPTH_BITS_ARB, 16, 
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 8,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		0
	};
	wglChoosePixelFormatARB(m_DC, Attributes, NULL, 1, &Format, (UINT*)&Formats);

	if (Format == -1)
	{
		CEngine::Get()->Log("Win32Context: No MSAA available.");

		Attributes[15] = 1;
		wglChoosePixelFormatARB(m_DC, Attributes, NULL, 1, &Format, (UINT*)&Formats);

		if (Format == -1)
		{
			m_DC = 0;
			m_Context = 0;
			CEngine::Get()->Error("Win32Context: Could not get proper pixel format.");
		}
	}	

	if (Format != -1)
	{
		int AttributesMSAA[] = {WGL_SAMPLES_ARB};
		int Result = 0;

		wglGetPixelFormatAttribivARB(m_DC, Format, 0, 1, AttributesMSAA, &Result);
		std::stringstream Message;
		Message << "Win32Context: Using " << Result << " samples per pixel.\n";
		CEngine::Get()->Log(Message.str());

		SetPixelFormat(m_DC, Format, &FormatDescriptor);

		GLint GLAttributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			0
		};

		m_Context = wglCreateContextAttribsARB(m_DC, 0, GLAttributes);
		if (m_Context == NULL)
		{
			CEngine::Get()->Log("Win32Context: OpenGL 3.3 not available...\n");
			GLAttributes[3] = 2;

			m_Context = wglCreateContextAttribsARB(m_DC, 0, GLAttributes);
			if (m_Context == NULL)
			{
				CEngine::Get()->Log("Win32Context: OpenGL 3.2 not available...\n");
				GLAttributes[3] = 1;

				m_Context = wglCreateContextAttribsARB(m_DC, 0, GLAttributes);
				if (m_Context == NULL)
				{
					CEngine::Get()->Log("Win32Context: OpenGL 3.1 not available...\n");
					GLAttributes[3] = 0;

					m_Context = wglCreateContextAttribsARB(m_DC, 0, GLAttributes);
					if (m_Context == NULL)
					{
						CEngine::Get()->Fatal("Win32Context: OpenGL 3.0 is not supported!\n");
					}
				}
			}
		}

		wglMakeCurrent(m_DC, m_Context);
	}

	if (m_DC == 0 || m_Context == 0)
		CEngine::Get()->Fatal("Win32Context: Could not create OpenGL context!");

	ShowWindow(m_Window, SW_SHOW);
	SetForegroundWindow(m_Window);
	SetFocus(m_Window);
#else
#error No support for Linux yet!
#endif

	m_Open = true;
	m_Width = Width;
	m_Height = Height;
	m_ResizeFunction = 0;
}


CGLContext::~CGLContext(void)
{
#ifdef _WIN32
	wglDeleteContext(m_Context);
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(m_Window, m_DC);
#endif
}

#ifdef _WIN32
LRESULT CALLBACK CGLContext::WindowEvent(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	CGLContext *Context;

	if (Message == WM_NCCREATE)
	{
		Context = (CGLContext*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		Context->m_Window = hWnd;

		SetWindowLong(hWnd, GWL_USERDATA, (long)Context);

		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	else
	{
		Context = (CGLContext*)GetWindowLong(hWnd, GWL_USERDATA);
		return Context->HandleWindowEvent(Message, wParam, lParam);
	}
}

LRESULT CGLContext::HandleWindowEvent(UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_DESTROY:
			m_Open = false;
			break;
		case WM_SIZE:
			if (m_ResizeFunction)
				m_ResizeFunction(LOWORD(lParam), HIWORD(lParam));
			break;
		default:
			return DefWindowProc(m_Window, Message, wParam, lParam);
	}

	return 0;
}
#endif

void CGLContext::Flip(void)
{
#ifdef _WIN32
	SwapBuffers(m_DC);
#endif
}

void CGLContext::ProcessEvents(void)
{
#ifdef _WIN32
	if (!m_Open) return;

	MSG Message;

	while (PeekMessage(&Message, m_Window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
#endif
}

bool CGLContext::GetOpen(void)
{
	return m_Open;
}

void CGLContext::SetResizeFunction(TResizeFunction Function)
{
	m_ResizeFunction = Function;
}