#include "CFlatShader.h"
#include <string>

using namespace rb;

CFlatShader::CFlatShader(void)
{
	std::string VertexSource =		"uniform mat4 mvpMatrix;"
									"attribute vec4 vVertex;"
									"void main(void) "
									"{ gl_Position = mvpMatrix * vVertex; "
									"}";
	strncpy_s(m_VertexSource, RB_SHADER_MAX_SIZE, VertexSource.c_str(), VertexSource.length());

	std::string FragmentSource =	"uniform vec4 vColor;"
									"void main(void) "
									"{ gl_FragColor = vColor; "
									"}";
	strncpy_s(m_FragmentSource, RB_SHADER_MAX_SIZE, FragmentSource.c_str(), FragmentSource.length());
}

void CFlatShader::Initialize(void)
{
	CompileAndLink();

	glBindAttribLocation(m_Program, 0, "vVertex");
}

void CFlatShader::Use(float *Color, GLfloat *Matrix)
{
	glUseProgram(m_Program);

	GLint ColorLocation = glGetUniformLocation(m_Program, "vColor");
	glUniform4fv(ColorLocation, 1, Color);

	GLint MatrixLocation = glGetUniformLocation(m_Program, "mvpMatrix");
	glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, Matrix);
}


CFlatShader::~CFlatShader(void)
{
}
