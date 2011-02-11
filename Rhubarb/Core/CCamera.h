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

#include "Core/CEntity.h"
#include "Math/CMatrix44.h"
#include "Math/CVector4.h"

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
