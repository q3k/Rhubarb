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

void CFlatShader::InitializeAttributes(void)
{
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
