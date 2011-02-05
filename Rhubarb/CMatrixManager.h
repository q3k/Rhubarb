#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CMatrix44.h"
#include "CCamera.h"

namespace rb
{
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
			//Push a Camera view
			void Push(CCamera &Camera);

			//Transform top matrix
			void Translate(GLfloat X, GLfloat Y, GLfloat Z);
			void Rotate(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
			void Scale(GLfloat X, GLfloat Y, GLfloat Z);
			void Multiply(CMatrix44 &Matrix);

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