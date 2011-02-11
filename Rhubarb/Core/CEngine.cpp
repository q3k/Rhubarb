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

#include "Core/CEngine.h"
using namespace rb;

#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#else
extern int __argc;
extern char **__argv;
#endif

CEngine *CEngine::Get(void)
{
	if (!m_Spawned)
		m_Singleton =  new CEngine();
	
	return m_Singleton;
}

CEngine::CEngine(void)
{
	m_Spawned = true;
	m_Initialized = false;

	Log("Spawning Engine...\n");

	m_TextureManager = 0;
	m_ShaderManager = 0;
	m_MatrixManager = 0;
	m_Camera = 0;
	m_Timer = 0;

	m_Width = 0;
	m_Height = 0;
	m_WindowName = "";

	m_ClientRenderFunction = 0;
}

void CEngine::SetClearColor(float R, float G, float B)
{
	glClearColor(R, G, B, 1.0f);
}

void CEngine::Initialize(unsigned int Width, unsigned int Height, std::string WindowName)
{
	Log("Initializing Engine...\n");

	m_WindowName = WindowName;
	m_Width = Width;
	m_Height = Height;

	glutInit(&__argc, __argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutInitWindowSize(Width, Height);
	glutCreateWindow(m_WindowName.c_str());
	glutReshapeFunc(m_sChangeSizeFunction);
	glutDisplayFunc(m_sRenderFunction);
	glutMotionFunc(m_sMouseMotionFunction);

	GLenum Error = glewInit();
	if (Error != GLEW_OK)
		Fatal(std::string("GLEW Error: ") + (char *)glewGetErrorString(Error));

	if (!GLEW_VERSION_3_0)
		Fatal(std::string("Sorry, but you need OpenGL 3.0!"));

	//Fatal(std::string("lol"));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_ShaderManager = new CShaderManager();
	m_TextureManager = new CTextureManager();
	m_MatrixManager = new CMatrixManager();
	m_Timer = new CTimer();

	m_FPSTimer.Start();
}

void CEngine::GetManagers(CMatrixManager **MatrixManager, CShaderManager **ShaderManager, CTextureManager **TextureManager)
{
	if (MatrixManager)
		*MatrixManager = m_MatrixManager;

	if (ShaderManager)
		*ShaderManager = m_ShaderManager;

	if (TextureManager)
		*TextureManager = m_TextureManager;
}

void CEngine::m_sChangeSizeFunction(int Width, int Height) { m_Singleton->ChangeSizeFunction(Width, Height); }
void CEngine::m_sRenderFunction(void) { m_Singleton->RenderFunction(); }
void CEngine::m_sMouseMotionFunction(int X, int Y) { m_Singleton->MouseMotionFunction(X, Y); };

void CEngine::ChangeSizeFunction(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	m_MatrixManager->SetPerspective(rbDegToRad(35.0f), float(Width)/float(Height), 1.0f, 1000.0f);
}

void CEngine::RenderFunction(void)
{
	static unsigned int Frames = 0;

	if (m_Camera)
		m_MatrixManager->Push(*m_Camera);
	else
		m_MatrixManager->PushIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (m_ClientRenderFunction)
	{
		bool Result = m_ClientRenderFunction(m_Timer->GetElapsedSeconds());
		if (!Result)
		{
			Log("Terminating main loop...\n");
			glutLeaveMainLoop();
		}
	}

	if (m_FPSTimer.GetElapsedSeconds() > 1.0f)
	{
		std::stringstream FPSData;
		FPSData << Frames / m_FPSTimer.GetElapsedSeconds();
		FPSData << " FPS\n";
		Log(FPSData.str());

		m_FPSTimer.Start();
		Frames = 0;
	}

	Frames++;

	glutSwapBuffers();
	glutPostRedisplay();

	m_MatrixManager->Pop();

	m_Timer->Start();
}

void CEngine::MouseMotionFunction(int X, int Y)
{
	
}

void CEngine::SetRenderFunction(TRenderFunction Function)
{
	m_ClientRenderFunction = Function;
}

void CEngine::SetCamera(CCamera *Camera)
{
	m_Camera = Camera;
}

CCamera *CEngine::GetCamera(void)
{
	return m_Camera;
}

void CEngine::Log(std::string Message)
{
	//Just stdout now.
	std::cout << "[i] " << Message;
}

void CEngine::Error(std::string Message)
{
	std::cerr << "[!] " << Message;
}

void CEngine::Fatal(std::string Message)
{
	std::cerr << "[e] " << Message;
#ifdef _WIN32
	MessageBoxA(0, Message.c_str(), "Fatal error", 0);
#endif
	//throw Exception::FatalException(Message);
	exit(0);
}

void CEngine::Start(void)
{
	Log("Entering render loop...\n");

	glutMainLoop();
}

CEngine::~CEngine(void)
{
}

bool CEngine::m_Spawned = false;
bool CEngine::m_Initialized = false;
CEngine *CEngine::m_Singleton = 0;
