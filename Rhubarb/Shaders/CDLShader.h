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

#include "Shaders/CShaderBase.h"
#include "Math/CVector4.h"

namespace rb
{
	class CDLShader : public CShaderBase
	{
		public:
			CDLShader(std::string VertexShaderFile, std::string FragmentShaderFile);
			~CDLShader(void);

			virtual void InitializeAttributes(void);

			virtual void Use(GLfloat *MVMatrix, GLfloat *MVPMatrix, CVector4 &Light, CVector4 &Ambient, CVector4 &Diffuse, GLfloat Shininess);
		private:
			GLint m_LocationAmbient;
			GLint m_LocationDiffuse;
			GLint m_LocationShininess;

			GLint m_LocationMVMatrix;
			GLint m_LocationMVPMatrix;
			GLint m_LocationNormalMatrix;
			GLint m_LocationLight;

			GLint m_LocationTexture;

			bool m_FoundLocations;
	};
}

