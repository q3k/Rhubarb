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

#include <string>

#include "CShaderBase.h"
#include "CVector4.h"

namespace rb
{
	class CDLShader : public CShaderBase
	{
		public:
			CDLShader(std::string VertexShaderFile, std::string FragmentShaderFile);
			~CDLShader(void);

			virtual void InitializeAttributes(void);

			virtual void Use(GLfloat *MVMatrix, GLfloat *PMatrix, CVector4 &Light);
	};
}

