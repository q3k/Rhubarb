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

#include "Shaders/CDLShader.h"
using namespace rb;

#include "Math/CMatrix44.h"

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

	m_FoundLocations = false;
}

void CDLShader::Use(GLfloat *MVMatrix, GLfloat *MVPMatrix, CVector4 &Light, CVector4 &Ambient, CVector4 &Diffuse, GLfloat Shininess)
{
	glUseProgram(m_Program);

	//precalculate normal matrix - not a good idea?
	GLfloat NormalMatrix[9];
	CVector4 *X = (CVector4*) MVMatrix;
	CVector4 *Y = (CVector4*) (MVMatrix + 4);
	CVector4 *Z = (CVector4*) (MVMatrix + 8);

	X->Normalize(*(CVector4*)NormalMatrix);
	Y->Normalize(*(CVector4*)(NormalMatrix + 3));
	Z->Normalize(*(CVector4*)(NormalMatrix + 6));

	if (!m_FoundLocations)
	{
		m_LocationAmbient = glGetUniformLocation(m_Program, "AmbientColor");
		m_LocationDiffuse = glGetUniformLocation(m_Program, "DiffuseColor");
		m_LocationShininess = glGetUniformLocation(m_Program, "Shininess");

		m_LocationMVMatrix = glGetUniformLocation(m_Program, "mvMatrix");
		m_LocationMVPMatrix = glGetUniformLocation(m_Program, "mvpMatrix");
		m_LocationNormalMatrix = glGetUniformLocation(m_Program, "normalMatrix");
		m_LocationLight = glGetUniformLocation(m_Program, "LightPosition");

		m_LocationTexture = glGetUniformLocation(m_Program, "Texture");

		m_FoundLocations = true;
	}

	glUniform4fv(m_LocationAmbient, 1, Ambient.m_Data);
	glUniform4fv(m_LocationDiffuse, 1, Diffuse.m_Data);
	glUniform1f(m_LocationShininess, Shininess);

	glUniformMatrix4fv(m_LocationMVMatrix, 1, GL_FALSE, MVMatrix);
	glUniformMatrix4fv(m_LocationMVPMatrix, 1, GL_FALSE, MVPMatrix);
	glUniformMatrix3fv(m_LocationNormalMatrix, 1, GL_FALSE, NormalMatrix);
	glUniform3fv(m_LocationLight, 1, Light.m_Data);
	
	glUniform1i(m_LocationTexture, 0);
}

CDLShader::~CDLShader(void)
{
}
