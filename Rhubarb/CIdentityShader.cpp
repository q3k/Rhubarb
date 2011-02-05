#include "CIdentityShader.h"

#include <string>
#include <cstring>
#include <assert.h>

#include <GL/glew.h>
#include <GL/GL.h>

using namespace rb;

CIdentityShader::CIdentityShader(void)
{
	std::string VertexSource =		"attribute vec4 vVertex;"
									"void main(void) "
									"{ "
									"	gl_Position = vVertex; "
									"}";
	strncpy_s(m_VertexSource, RB_SHADER_MAX_SIZE, VertexSource.c_str(), VertexSource.length());

	std::string FragmentSource =	"uniform vec4 vColor;"
									"void main(void) "
									"{ "
									"	gl_FragColor = vColor;"
									"}";
	strncpy_s(m_FragmentSource, RB_SHADER_MAX_SIZE, FragmentSource.c_str(), FragmentSource.length());
}

void CIdentityShader::InitializeAttributes(void)
{
	glBindAttribLocation(m_Program, 0, "vVertex");
}

void CIdentityShader::Use(float *Color)
{
	glUseProgram(m_Program);

	GLint ColorLocation = glGetUniformLocation(m_Program, "vColor");
	glUniform4fv(ColorLocation, 1, Color);
}

CIdentityShader::~CIdentityShader(void)
{
}
