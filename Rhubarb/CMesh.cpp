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

#include "CMesh.h"
using namespace rb;

CMesh::CMesh(void)
{
	m_NumVertices = 0;
	m_VertexArray = 0;

	m_BeingFed = false;
}


CMesh::~CMesh(void)
{
}


void CMesh::Begin(GLenum Primitive, GLuint NumberVertices)
{
	m_Primitive = Primitive;
	m_NumVertices = NumberVertices;

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	m_BeingFed = true;
}

void CMesh::CopyVertexData(float *Data)
{
	glGenBuffers(1, &m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m_NumVertices, Data, GL_DYNAMIC_DRAW);
}

void CMesh::End(void)
{
	glBindVertexArray(m_VertexArrayObject);

	if (m_VertexArray != 0)
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindVertexArray(0);

	m_BeingFed = false;
}

void CMesh::Draw(void)
{
	if (m_BeingFed) return;

	glBindVertexArray(m_VertexArrayObject);
	glDrawArrays(m_Primitive, 0, m_NumVertices);
	glBindVertexArray(0);
}