#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include "CFlatShader.h"
#include "CTriangleMesh.h"
#include "CMatrix44.h"
#include "CMatrixManager.h"
#include "CCamera.h"
#include "CObjReader.h"

#define DegToRad(x)	((x)*0.017453292519943296f)

rb::CFlatShader gCubeShader;
rb::CTriangleMesh gCube;
rb::CMatrixManager gManager;
rb::CCamera gCamera;

float gCubeSize = 0.25f;
rb::CVector4 gCubeData[] = {
	rb::CVector4(-gCubeSize, -gCubeSize, 0.0f),
	rb::CVector4(gCubeSize, -gCubeSize, 0.0f),
	rb::CVector4(gCubeSize, gCubeSize, 0.0f),

	rb::CVector4(-gCubeSize, -gCubeSize, 0.0f),
	rb::CVector4(gCubeSize, gCubeSize, 0.0f),
	rb::CVector4(-gCubeSize, gCubeSize, 0.0f)
};
/*float gCubeVertices[] = {
		-gCubeSize, -gCubeSize, 0.0f,
		gCubeSize, -gCubeSize, 0.0f,
		gCubeSize, gCubeSize, 0.0f,
		-gCubeSize, gCubeSize, 0.0f
	};*/

void fnSpecialKeys(int Key, int X, int Y)
{
	float Linear = 0.1f;
	float Angular = DegToRad(1.0f);

	switch (Key)
	{
		case GLUT_KEY_UP:
			gCamera.MoveForward(Linear);
			break;
		case GLUT_KEY_DOWN:
			gCamera.MoveForward(-Linear);
			break;
		case GLUT_KEY_LEFT:
			gCamera.RotateWorld(Angular, 0.0f, 1.0f, 0.0f);
			break;
		case GLUT_KEY_RIGHT:
			gCamera.RotateWorld(-Angular, 0.0f, 1.0f, 0.0f);
			break;
	}		
}

void fnChangeSize(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	gManager.SetPerspective(DegToRad(35.0f), float(Width)/float(Height), 1.0f, 1000.0f);
}

void fnRenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	static float Rotation = 0.0f;
	Rotation += 0.1f;

	float Red [] = {1.0f, 0.0f, 0.0f, 1.0f};

	//Camera
	gManager.Push(gCamera);

		gManager.Push();
			gManager.Scale(0.5f, 0.5f, 0.5f);
			gManager.Rotate(DegToRad(Rotation), 0.0f, 1.0f, 0.0f);
			gCubeShader.Use(Red, gManager.GetMVP());
			gCube.Draw();
		gManager.Pop();

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
	glutSpecialFunc(fnSpecialKeys);

	GLenum Error = glewInit();
	if (Error != GLEW_OK)
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(Error) << std::endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	gCubeShader.Initialize();

	rb::CObjReader Reader("teapot.obj");
	Reader.Read(gCube);

	gCamera.SetPosition(0.0f, 60.0f, 100.0f);
	gCamera.LookAt(rb::CVector4(0.0f, 0.0f, 0.0f));

	glutMainLoop();
}