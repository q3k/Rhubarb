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
#include <GL/gl.h>

#include "Math/CVector4.h"
#include "Math/CMatrix44.h"

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
			const GLfloat *GetMatrix(void);

			void RotateWorld(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
			void RotateLocal(GLfloat Angle, GLfloat X, GLfloat Y, GLfloat Z);
		protected:
			CVector4 m_Position;
			CVector4 m_Up;
			CVector4 m_Forward;

			void ResetRotation(void);

		private:
			GLfloat *m_TempMatrix;
	};
};
