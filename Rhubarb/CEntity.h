#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CVector4.h"
#include "CMatrix44.h"

namespace rb
{
	class CEntity
	{
		public:
			CEntity(void);
			~CEntity(void);

			void SetPosition(CVector4 &Position);
			void SetPosition(GLfloat X, GLfloat Y, GLfloat Z);

			void GetPosition(CVector4 &Position);
			void GetPosition(GLfloat *Position);

			GLfloat GetX(void);
			GLfloat GetY(void);
			GLfloat GetZ(void);

			void TranslateWorld(GLfloat X, GLfloat Y, GLfloat Z);
			void TranslateLocal(GLfloat X, GLfloat Y, GLfloat Z);

			void MoveForward(float Amount);
			void MoveUp(float Amount);
			void MoveRight(float Amount);

			void GetMatrix(CMatrix44 &Matrix);
			void GetMatrix(GLfloat *Matrix);

			void RotateWorld(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
			void RotateLocal(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
		protected:
			CVector4 m_Position;
			CVector4 m_Up;
			CVector4 m_Forward;

			void ResetRotation(void);
	};
};