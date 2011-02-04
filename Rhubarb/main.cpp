#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include "CFlatShader.h"
#include "CMesh.h"
#include "CMatrix44.h"
#include "CMatrixManager.h"

#define DegToRad(x)	((x)*0.017453292519943296f)

rb::CFlatShader gCubeShader;
rb::CMesh gCube;
rb::CMatrixManager gManager;

float gCubeSize = 0.25f;
float gCubeVertices[] = {
		-gCubeSize, -gCubeSize, 0.0f,
		gCubeSize, -gCubeSize, 0.0f,
		gCubeSize, gCubeSize, 0.0f,
		-gCubeSize, gCubeSize, 0.0f
	};

void fnChangeSize(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	gManager.SetPerspective(DegToRad(35.0f), float(Width)/float(Height), 1.0f, 100.0f);
}

void fnRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	static float Rotation = 0.0f;
	Rotation += 0.1f;

	float Red [] = {1.0f, 0.0f, 0.0f, 1.0f};

	gManager.Push();
		gManager.Translate(sinf(DegToRad(Rotation)), 0.0f, -2.0f);
		gManager.Rotate(DegToRad(Rotation), 0.0f, 0.0f, 1.0f);
		gCubeShader.Use(Red, gManager.GetMVP());
		gCube.Draw();
	gManager.Pop();


	gManager.Push();
		gManager.Translate(cosf(DegToRad(Rotation)), 0.0f, -4.0f);
		gManager.Rotate(-DegToRad(Rotation), 0.0f, 0.0f, 1.0f);
		gCubeShader.Use(Red, gManager.GetMVP());
		gCube.Draw();
	gManager.Pop();

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	rb::CMatrix44 *Matrix = new rb::CMatrix44();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	gCubeShader.Initialize();

	gCube.BeginRaw(GL_TRIANGLE_FAN, 4);
	gCube.CopyRawVertexData(gCubeVertices);
	gCube.EndRaw();

	glutMainLoop();
}