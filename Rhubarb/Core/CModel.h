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

#include "Core/CEntity.h"
#include "Core/CTriangleMesh.h"

#include "Shaders/CDLShader.h"
#include "Helpers/CTextureManager.h"
#include "Helpers/CMatrixManager.h"

#include "Math/CVector4.h"

namespace rb
{
	namespace Exception
	{
		class ModelException : public std::exception
		{
			public:
				ModelException(const std::string Error) { m_Error = std::string(Error); }
				~ModelException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};
	class CModel : public CEntity
	{
		public:
			CModel(void);
			~CModel(void);

			void Load(std::string Filename);
			void Draw(void);

			void SetDiffuseColor(float R, float G, float B, float A);
		private:
			CDLShader *m_Shader;
			CTriangleMesh *m_Mesh;
			TTexture m_Texture;

			CTextureManager *m_TextureManager;
			CMatrixManager *m_MatrixManager;

			bool m_Loaded;
			bool m_HasTexture;

			std::string m_Name;
			std::string m_VertexShaderName;
			std::string m_FragmentShaderName;
			std::string m_MeshName;
			std::string m_TextureName;

			CVector4 m_Ambient;
			CVector4 m_Diffuse;
			float m_Shininess;
	};
};
