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

#include "CMatrix44.h"
#include "CMatrixManager.h"
#include "CCamera.h"
#include "CTextureManager.h"
#include "CModel.h"

#define DegToRad(x)	((x)*0.017453292519943296f)

rb::CMatrixManager g_MatrixManager;
rb::CCamera g_Camera;
rb::CTextureManager g_TextureManager;
rb::CModel g_Cube;

void fnChangeSize(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	g_MatrixManager.SetPerspective(DegToRad(35.0f), float(Width)/float(Height), 1.0f, 1000.0f);
}

void fnRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	g_Cube.RotateWorld(DegToRad(0.1f), 0.0f, 1.0f, 0.0f);
	g_Cube.RotateWorld(DegToRad(0.05f), 1.0f, 0.0f, 0.0f);
	g_Cube.Draw();

	glutSwapBuffers();
	glutPostRedisplay();
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
	g_Cube.Bind(&g_TextureManager, &g_MatrixManager);
	g_Cube.Load("cube.model");

	g_Camera.SetPosition(0.0f, 4.0f, 6.0f);
	g_Camera.LookAt(rb::CVector4(0.0f, 0.0f, 0.0f));

	g_MatrixManager.Push(g_Camera);
	glutMainLoop();
}