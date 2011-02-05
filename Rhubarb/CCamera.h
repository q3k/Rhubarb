#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CEntity.h"
#include "CMatrix44.h"
#include "CVector4.h"

namespace rb
{
	class CCamera : public CEntity
	{
		public:
			CCamera(void);
			~CCamera(void);

			void GetCameraMatrix(CMatrix44 &Matrix);
			void GetCameraMatrix(GLfloat *Matrix);

			void LookAt(CVector4 &Target);
	};
};