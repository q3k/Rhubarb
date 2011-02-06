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

#include "CDLShader.h"
using namespace rb;

CDLShader::CDLShader(std::string VertexShaderFile, std::string FragmentShaderFile)
{
	ReadSource(VertexShaderFile.c_str(), FragmentShaderFile.c_str());
}

void CDLShader::InitializeAttributes(void)
{
	//Standarized for my CModel class
	glBindAttribLocation(m_Program, 0, "vVertex");
	glBindAttribLocation(m_Program, 1, "vNormal");
	glBindAttribLocation(m_Program, 2, "vTexture");
}

void CDLShader::Use(GLfloat *MVMatrix, GLfloat *PMatrix, CVector4 &Light)
{
	glUseProgram(m_Program);

	GLint MVMatrixLocation = glGetUniformLocation(m_Program, "mvMatrix");
	glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, MVMatrix);

	GLint PMatrixLocation = glGetUniformLocation(m_Program, "pMatrix");
	glUniformMatrix4fv(PMatrixLocation, 1, GL_FALSE, PMatrix);

	GLint LightLocation = glGetUniformLocation(m_Program, "vLightPos");
	glUniform3fv(LightLocation, 1, Light.m_Data);

	GLint TextureLocation = glGetUniformLocation(m_Program, "tTexture");
	glUniform1i(TextureLocation, 0);
}

CDLShader::~CDLShader(void)
{
}
