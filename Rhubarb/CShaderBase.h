#pragma once

#include <GL/glew.h>

#include <exception>
#include <string>

#define RB_SHADER_MAX_SIZE 1024

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

namespace rb
{
	namespace Exception
	{
		class ShaderCompileException : public std::exception
		{
			public:
				ShaderCompileException(const std::string Error) { m_Error = std::string(Error); }
				~ShaderCompileException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};
	class CShaderBase
	{
		public:
			CShaderBase(void);
			~CShaderBase(void);

			void Initialize(void);
		protected:
			void CompileAndLink();
			void ReadSource(const char *VertexFile, const char *FragmentFile);

			char m_FragmentSource[RB_SHADER_MAX_SIZE];
			char m_VertexSource[RB_SHADER_MAX_SIZE];

			GLuint m_Program;

			virtual void InitializeAttributes(void) = 0;	

			void LoadShader(const char *Source, GLuint Shader);
			void CompileShader(GLuint Shader);
	};
};
