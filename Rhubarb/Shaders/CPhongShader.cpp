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

#include "Shaders/CPhongShader.h"

#include "Core/Platform.h"

#include <string>
#include <cassert>

using namespace rb;

CPhongShader::CPhongShader(void)
{
std::string VertexSource =	"uniform mat4 mvMatrix;\
							uniform mat4 pMatrix;\
							uniform vec3 vLightPos;\
							uniform vec4 vColor;\
							attribute vec4 vVertex;\
							attribute vec3 vNormal;\
							varying vec4 vFragColor;\
							void main(void) {\
								mat3 mNormalMatrix;\
								mNormalMatrix[0] = normalize(mvMatrix[0].xyz);\
								mNormalMatrix[1] = normalize(mvMatrix[1].xyz);\
								mNormalMatrix[2] = normalize(mvMatrix[2].xyz);\
								vec3 vNorm = normalize(mNormalMatrix * vNormal);\
								vec4 ecPosition;\
								vec3 ecPosition3;\
								ecPosition = mvMatrix * vVertex;\
								ecPosition3 = ecPosition.xyz /ecPosition.w;\
								vec3 vLightDir = normalize(vLightPos - ecPosition3);\
								float fDot = max(0.0, dot(vNorm, vLightDir));\
								vFragColor.rgb = vColor.rgb * fDot;\
								vFragColor.a = vColor.a;\
								mat4 mvpMatrix;\
								mvpMatrix = pMatrix * mvMatrix;\
								gl_Position = mvpMatrix * vVertex;\
							}";
	strncpy_s(m_VertexSource, RB_SHADER_MAX_SIZE, VertexSource.c_str(), VertexSource.length());

	std::string FragmentSource =	
									"varying vec4 vFragColor;\
									void main(void) {\
										gl_FragColor = vFragColor;\
									}";
	strncpy_s(m_FragmentSource, RB_SHADER_MAX_SIZE, FragmentSource.c_str(), FragmentSource.length());
}

void CPhongShader::InitializeAttributes(void)
{
	glBindAttribLocation(m_Program, 0, "vVertex");
	glBindAttribLocation(m_Program, 1, "vNormal");
}

void CPhongShader::Use(float *Color, GLfloat *MVMatrix, GLfloat *PMatrix, CVector4 &Light)
{
	glUseProgram(m_Program);

	GLint ColorLocation = glGetUniformLocation(m_Program, "vColor");
	glUniform4fv(ColorLocation, 1, Color);

	GLint MVMatrixLocation = glGetUniformLocation(m_Program, "mvMatrix");
	glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, MVMatrix);

	GLint PMatrixLocation = glGetUniformLocation(m_Program, "pMatrix");
	glUniformMatrix4fv(PMatrixLocation, 1, GL_FALSE, PMatrix);

	GLint LightLocation = glGetUniformLocation(m_Program, "vLightPos");
	glUniform3fv(LightLocation, 1, Light.m_Data);
}


CPhongShader::~CPhongShader(void)
{
}
