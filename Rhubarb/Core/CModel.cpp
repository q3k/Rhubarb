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

#include "CModel.h"
using namespace rb;

#include <fstream>

#include "Helpers/CObjReader.h"

CModel::CModel(void)
{
	m_Loaded = false;
	m_HasTexture = false;

	m_Mesh = 0;
	m_Shader = 0;

	CEntity::CEntity();
}

void CModel::Bind(CTextureManager *TextureManager, CMatrixManager *MatrixManager)
{
	m_TextureManager = TextureManager;
	m_MatrixManager = MatrixManager;
}

void CModel::Load(std::string Filename)
{
	std::ifstream File;
	File.open(Filename, std::ios::in);

	std::string Keyword;

	m_Name = "";
	m_VertexShaderName = "";
	m_FragmentShaderName = "";
	m_MeshName = "";
	m_TextureName = "";

	while (!File.eof())
	{
		File >> Keyword;

		if (Keyword == "name")
			File >> m_Name;
		else if (Keyword == "vertex")
			File >> m_VertexShaderName;
		else if (Keyword == "fragment")
			File >> m_FragmentShaderName;
		else if (Keyword == "mesh")
			File >> m_MeshName;
		else if (Keyword == "texture")
			File >> m_TextureName;
		else if (Keyword == "#" || Keyword == "")
			{}
		else
			throw Exception::ModelException("Parse error in model file. \
											Unknown keyword" + Keyword + ".");

		// Read until end of line
		std::getline(File, Keyword);
	}

	if (m_Name == "" || m_VertexShaderName == "" || m_FragmentShaderName == ""
		|| m_MeshName == "")
		throw Exception::ModelException("Mesh file does not contain all \
										required keywords!");

	try
	{
		m_Shader = new CDLShader(m_VertexShaderName, m_FragmentShaderName);
		m_Shader->Initialize();
	}
	catch (Exception::ShaderCompileException &e)
	{
		throw Exception::ModelException("Shader error! " + std::string(e.what()));
	}

	try
	{
		m_Mesh = new CTriangleMesh();
		m_Mesh->LoadFromObj(m_MeshName);
	}
	catch (Exception::ObjReaderException &e)
	{
		throw Exception::ModelException("Mesh error! " + std::string(e.what()));
	}

	if (m_TextureName != "")
	{
		try
		{
			m_Texture = m_TextureManager->GetTexture(m_TextureName);
			m_HasTexture = true;
		}
		catch (Exception::TextureManagerException &e)
		{
			throw Exception::ModelException("Texture error! " + std::string(e.what()));
		}
	}

	m_Loaded = true;
}

void CModel::Draw(void)
{
	if (m_Loaded)
	{
		m_MatrixManager->Push();
		m_MatrixManager->Multiply(GetMatrix());

		m_Shader->Use(m_MatrixManager->GetMV(), m_MatrixManager->GetP(), CVector4(0.0f, 0.0f, 0.0f));

		if (m_HasTexture)
			glBindTexture(GL_TEXTURE_2D, m_Texture);

		m_Mesh->Draw();

		m_MatrixManager->Pop();
	}
}

CModel::~CModel(void)
{
	delete m_Mesh;
	delete m_Shader;
}
