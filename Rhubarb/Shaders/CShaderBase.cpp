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

#include <stdio.h>

#include "Shaders/CShaderBase.h"
using namespace rb;

#include "Core/CEngine.h"

#include <sstream>
#include <fstream>

CShaderBase::CShaderBase(void)
{
}

void CShaderBase::ReadSource(const char *VertexFile, const char *FragmentFile)
{
	std::ifstream File;
	File.open(VertexFile, std::ios::in | std::ios::binary);
	File.seekg(0, std::ios::end);
	int Size = (int)File.tellg();
	File.seekg(0, std::ios::beg);

	if (Size > RB_SHADER_MAX_SIZE)
		throw Exception::ShaderCompileException("Vertex shader source too large!");

	File.read(m_VertexSource, Size);
	File.close();
	m_VertexSource[Size] = 0;

	File.open(FragmentFile, std::ios::in | std::ios::binary);
	File.seekg(0, std::ios::end);
	Size = (int)File.tellg();
	File.seekg(0, std::ios::beg);

	if (Size > RB_SHADER_MAX_SIZE)
		throw Exception::ShaderCompileException("Fragment shader source too large!");

	File.read(m_FragmentSource, Size);
	File.close();
	m_FragmentSource[Size] = 0;
}

void CShaderBase::LoadShader(const char *Source, GLuint Shader)
{
	GLchar *StringPtr[1];

    StringPtr[0] = (GLchar *)Source;

    glShaderSource(Shader, 1, (const GLchar **)StringPtr, NULL);
}

void CShaderBase::CompileShader(GLuint Shader)
{
	glCompileShader(Shader);

	GLint Test;

	glGetShaderiv(Shader, GL_COMPILE_STATUS, &Test);

	if (Test == GL_FALSE)
	{
		GLint Length;
		glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &Length);
		
		GLchar *Error = new GLchar[Length];
		glGetShaderInfoLog(Shader, Length, NULL, Error);

		throw Exception::ShaderCompileException("Could not compile shader source! " + std::string(Error));

		delete [] Error;
	}
}

void CShaderBase::Initialize(void)
{
	std::stringstream Message;
	Message << "Compiling shader..." << std::endl;
	CEngine::Get()->Log(Message.str());

	GLuint VertexShader, FragmentShader;

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	LoadShader(m_VertexSource, VertexShader);
	LoadShader(m_FragmentSource, FragmentShader);

	CompileShader(VertexShader);
	CompileShader(FragmentShader);

	m_Program = glCreateProgram();
	glAttachShader(m_Program, VertexShader);
	glAttachShader(m_Program, FragmentShader);

	InitializeAttributes();

	glLinkProgram(m_Program);

	GLint Test;
	glGetProgramiv(m_Program, GL_COMPILE_STATUS, &Test);

    if (Test == GL_FALSE)
	{
		GLint Length;
		glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &Length);
		
		GLchar *Error = new GLchar[Length];
		glGetProgramInfoLog(m_Program, Length, NULL, Error);

		throw Exception::ShaderCompileException("Could not link shader program! " + std::string(Error));
	}

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	std::stringstream Message2;
	Message2 << "Succesfully compiled shader." << std::endl;
	CEngine::Get()->Log(Message2.str());
}

CShaderBase::~CShaderBase(void)
{
}
