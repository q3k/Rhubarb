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

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include <exception>
#include <string>

#include "Math/CMatrix44.h"
#include "Core/CCamera.h"

namespace rb
{
	namespace Exception
	{
		class MatrixManagerException : public std::exception
		{
			public:
				MatrixManagerException(const std::string Error) { m_Error = std::string(Error); }
				~MatrixManagerException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};

	class CMatrixManager
	{
		public:
			CMatrixManager(unsigned int StackSize = 64);
			~CMatrixManager(void);

			////// Model & View Matrix methods (in form of a stack)
			//Push the top matrix (copy)
			void Push(void);
			void Pop(void);

			//Push a new matrix
			void PushIdentity();
			//Push an existing matrix
			void Push(CMatrix44 &Matrix);
			void Push(const GLfloat *Matrix);
			//Push a Camera view
			void Push(CCamera &Camera);

			//Transform top matrix
			void Translate(GLfloat X, GLfloat Y, GLfloat Z);
			void Rotate(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
			void Scale(GLfloat X, GLfloat Y, GLfloat Z);
			void Multiply(CMatrix44 &Matrix);
			void Multiply(const GLfloat *Matrix);

			////// Projection Matrix methods
			//Set projection matrix
			void SetProjection(CMatrix44 &ProjectionMatrix);
			//Quickly set perspective
			void SetPerspective(GLfloat FOV, GLfloat AspectRatio, GLfloat Near, GLfloat Far);


			
			//Get combined matrix (to feed to a shader)
			GLfloat *GetMVP(void);
			GLfloat *GetMV(void);
			GLfloat *GetP(void);
		private:
			float *m_StackBottom;
			float *m_StackPointer;
			unsigned int m_MaxSize;

			CMatrix44 *m_ProjectionMatrix;
			CMatrix44 *m_MVPMatrix;

			bool CanAllocate(void);
	};
};