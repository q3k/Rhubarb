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
#include <sstream>

#include "Helpers/CObjReader.h"
#include "Core/CEngine.h"

CModel::CModel(void)
{
	m_Loaded = false;
	m_HasTexture = false;

	m_Mesh = 0;
	m_Shader = 0;

	CEntity::CEntity();

	m_Shininess = 128.0f;
}

void CModel::Load(std::string Filename)
{
	CEngine::Get()->GetManagers(&m_MatrixManager, 0, &m_TextureManager);

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
		else if (Keyword == "ambient")
			File >> m_Ambient.m_Data[0] >> m_Ambient.m_Data[1] >> m_Ambient.m_Data[2] >> m_Ambient.m_Data[3];
		else if (Keyword == "diffuse")
			File >> m_Diffuse.m_Data[0] >> m_Diffuse.m_Data[1] >> m_Diffuse.m_Data[2] >> m_Diffuse.m_Data[3];
		else if (Keyword == "shininess")
			File >> m_Shininess;
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

	std::stringstream Message;
	Message << "Loading model " << m_Name << "...\n";
	CEngine::Get()->Log(Message.str());

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

	std::stringstream Message2;
	Message2 << "Finished loading model " << m_Name << ".\n";
	CEngine::Get()->Log(Message2.str());

	m_Loaded = true;
}

void CModel::Draw(void)
{
	if (m_Loaded)
	{
		m_MatrixManager->Push();
		m_MatrixManager->Multiply(GetMatrix());

		m_Shader->Use(m_MatrixManager->GetMV(), m_MatrixManager->GetMVP(), CVector4(100.0f, 50.0f, 70.0f), m_Ambient, m_Diffuse, m_Shininess);

		if (m_HasTexture)
			glBindTexture(GL_TEXTURE_2D, m_Texture);

		m_Mesh->Draw();

		m_MatrixManager->Pop();
	}
}

void CModel::SetDiffuseColor(float R, float G, float B, float A)
{
	m_Diffuse.m_Data[0] = R;
	m_Diffuse.m_Data[1] = G;
	m_Diffuse.m_Data[2] = B;
	m_Diffuse.m_Data[3] = A;
}

CModel::~CModel(void)
{
	delete m_Mesh;
	delete m_Shader;
}
