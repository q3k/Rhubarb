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

#include "CTriangleMesh.h"
using namespace rb;

#include <math.h>
#include <stdio.h>
#include <iostream>

#include "Helpers/CObjReader.h"

CTriangleMesh::CTriangleMesh(void)
{
	m_Indices = 0;
	m_Vertices = 0;
	m_Normals = 0;

	m_Maximum = 0;
}

void CTriangleMesh::Begin(GLint NumberVertices)
{
	delete [] m_Indices;
	delete [] m_Vertices;
	delete [] m_Normals;

	m_Maximum = NumberVertices;
	m_IndexCount = 0;
	m_VertexCount = 0;

	m_VertexObject = 0;

	m_Indices = new GLushort[m_Maximum];
	m_Vertices = new GLfloat[m_Maximum * 3];
	m_Normals = new GLfloat[m_Maximum * 3];
	m_TextureVertices = new GLfloat[m_Maximum * 2];
}







void CTriangleMesh::End(void)
{
	/*std::cout << "Listing..." << std::endl;

	for (int i = 0; i < m_IndexCount; i++)
	{
		std::cout << "	Index " << i << ", vertex " << m_Indices[i] << std::endl;
		
		CVector4 *Vertex = (CVector4 *)(m_Vertices + m_Indices[i] * 3);
		CVector4 *Normal = (CVector4 *)(m_Normals + m_Indices[i] * 3);
		GLfloat *TV = m_TextureVertices + m_Indices[i] * 2;

		std::cout << "		v: " << Vertex->m_Data[0] << " " << Vertex->m_Data[1] << " " << Vertex->m_Data[2] << std::endl;
		std::cout << "		n: " << Normal->m_Data[0] << " " << Normal->m_Data[1] << " " << Normal->m_Data[2] << std::endl;
		std::cout << "		t: " << TV[0] << " " << TV[1] << std::endl;
	}*/

	glGenVertexArrays(1, &m_VertexObject);
	glBindVertexArray(m_VertexObject);

	glGenBuffers(1, &m_VertexArray);
	glGenBuffers(1, &m_NormalArray);
	glGenBuffers(1, &m_IndexArray);
	glGenBuffers(1, &m_TextureVertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, m_Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalArray);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, m_Normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureVertexArray);
	glEnableVertexAttribArray(2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * m_VertexCount, m_TextureVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_IndexCount, m_Indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	delete [] m_Indices;
	delete [] m_Vertices;
	delete [] m_Normals;
	delete [] m_TextureVertices;

	m_Indices = 0;
	m_Vertices = 0;
	m_Normals = 0;
	m_TextureVertices = 0;
}

void CTriangleMesh::Draw(void)
{
	if (m_VertexObject)
	{
		glBindVertexArray(m_VertexObject);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}
}

void CTriangleMesh::ReadLists(GLushort *Indices, GLuint NumberIndices, GLfloat *Vertices, GLuint NumberVertices, GLfloat *Normals)
{
	glGenVertexArrays(1, &m_VertexObject);
	glBindVertexArray(m_VertexObject);

	glGenBuffers(1, &m_VertexArray);
	glGenBuffers(1, &m_IndexArray);
	glGenBuffers(1, &m_NormalArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NumberVertices, Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_NormalArray);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NumberVertices, Normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * NumberIndices, Indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	m_IndexCount = NumberIndices;
}

void CTriangleMesh::LoadFromObj(std::string File)
{
	CObjReader Reader(File);
	Reader.Read(*this);
}

CTriangleMesh::~CTriangleMesh(void)
{
	delete [] m_Indices;
	delete [] m_Vertices;
}
