#include <stdio.h>
#include <assert.h>

#include "CShaderBase.h"
using namespace rb;

CShaderBase::CShaderBase(void)
{
}

void CShaderBase::ReadSource(const char *VertexFile, const char *FragmentFile)
{
	FILE *fp;

	fopen_s(&fp, VertexFile, "r");
	fseek(fp, 0, SEEK_END);
	size_t Size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	assert(Size < RB_SHADER_MAX_SIZE);
	fread_s(m_VertexSource, RB_SHADER_MAX_SIZE, Size, 1, fp);
	fclose(fp);

	fopen_s(&fp, FragmentFile, "r");
	fseek(fp, 0, SEEK_END);
	Size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	assert(Size < RB_SHADER_MAX_SIZE);
	fread_s(m_FragmentSource, RB_SHADER_MAX_SIZE, Size, 1, fp);
	fclose(fp);
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
    assert(Test != GL_FALSE);
}

void CShaderBase::CompileAndLink(void)
{
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

	glLinkProgram(m_Program);

	GLint Test;
	glGetProgramiv(m_Program, GL_COMPILE_STATUS, &Test);
    assert(Test != GL_FALSE);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

CShaderBase::~CShaderBase(void)
{
}
