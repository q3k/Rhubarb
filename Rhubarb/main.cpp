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

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include "Rhubarb.h"

#define DegToRad(x)	((x)*0.017453292519943296f)
#define CUBE_NUM 1

rb::CMatrixManager g_MatrixManager;
rb::CCamera g_Camera;
rb::CTextureManager g_TextureManager;
rb::CModel g_Cubes[CUBE_NUM];
rb::CTimer g_Timer;

unsigned int g_NumFrames = 0;

void fnChangeSize(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	g_MatrixManager.SetPerspective(DegToRad(35.0f), float(Width)/float(Height), 1.0f, 1000.0f);
}

void fnRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	for (int i = 0; i < CUBE_NUM; i++)
	{
		g_Cubes[i].RotateWorld(DegToRad(0.1f), 0.0f, 1.0f, 0.0f);
		g_Cubes[i].RotateWorld(DegToRad(0.05f), 1.0f, 0.0f, 0.0f);
		g_Cubes[i].Draw();
	}

	glutSwapBuffers();
	glutPostRedisplay();

	if (g_Timer.GetElapsedSeconds() > 5.0f)
	{
		float Seconds = g_Timer.GetElapsedSeconds();
		float FPS = g_NumFrames / Seconds;
		std::cout << "[i] FPS: " << FPS << std::endl;

		g_Timer.Start();
		g_NumFrames = 0;
	}
	g_NumFrames++;
}

int main(int argc, char **argv)
{
	//Some day all of this will go in its own class...
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Rhubarb");
	glutReshapeFunc(fnChangeSize);
	glutDisplayFunc(fnRenderScene);

	GLenum Error = glewInit();
	if (Error != GLEW_OK)
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(Error) << std::endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//Begin "proper" code.
	for (int i = 0; i < CUBE_NUM; i++)
	{
		g_Cubes[i].Bind(&g_TextureManager, &g_MatrixManager);
		g_Cubes[i].Load("Data/cube.model");
		g_Cubes[i].SetPosition(0.0f, 0.0f, -20.0f);
		//g_Cubes[i].SetPosition(i * 3.0f - (CUBE_NUM * 1.5f), 0.0f, -10.0f);
	}

	
	//g_Camera.RotateWorld(DegToRad(180), 0.0f, 1.0f, 0.0f);
	g_Camera.SetPosition(0.0f, 8.0f, 5.0f);
	g_Camera.LookAt(rb::CVector4(0.0f, 0.0f, -20.0f));

	g_MatrixManager.Push(g_Camera);

	g_Timer.Start();
	g_NumFrames = 0;
	glutMainLoop();
}