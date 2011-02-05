#pragma once

#include <GL/glew.h>

#define RB_SHADER_MAX_SIZE 1024

namespace rb
{
	class CShaderBase
	{
		public:
			CShaderBase(void);
			~CShaderBase(void);

		protected:
			void CompileAndLink();
			void ReadSource(const char *VertexFile, const char *FragmentFile);

			char m_FragmentSource[RB_SHADER_MAX_SIZE];
			char m_VertexSource[RB_SHADER_MAX_SIZE];

			GLuint m_Program;

		private:
			void LoadShader(const char *Source, GLuint Shader);
			void CompileShader(GLuint Shader);
	};
};