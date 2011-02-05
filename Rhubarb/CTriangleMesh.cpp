#include "CTriangleMesh.h"
using namespace rb;

#include <math.h>
#include <stdio.h>
#include <iostream>

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
}

bool CTriangleMesh::CompareVectors(GLfloat *VertexA, GLfloat *VertexB)
{
	const GLfloat Error = 0.0001f;
	if (abs(VertexA[0]  - VertexB[0]) <= Error &&
		abs(VertexA[1]  - VertexB[1]) <= Error &&
		abs(VertexA[2]  - VertexB[2]) <= Error)
		return true;
	else
		return false;
}

void CTriangleMesh::AddTriangle(CVector4 Vertices[3], CVector4 Normals[3])
{
	//compare each vertex from face against...
	for (GLuint i = 0; i < 3; i++)
	{
		GLfloat *NewVertex = Vertices[i].m_Data;

		CVector4 NormalizedNormal;
		Normals[i].Normalize(NormalizedNormal);
		GLfloat *NewNormal = NormalizedNormal.m_Data;

		//each vertex from current vertex list.
		GLuint j = 0;
		for (j = 0; j < m_VertexCount / 3; j++)
		{
			GLfloat *OldVertex = m_Vertices + j * 3;
			GLfloat *OldNormal = m_Normals + j * 3;

			if (CompareVectors(NewVertex, OldVertex) &&
				CompareVectors(NewNormal, OldNormal))
			{
				m_Indices[m_IndexCount] = j;
				m_IndexCount++;
				break;
			}
		}

		if (j == m_VertexCount / 3 && m_VertexCount / 3 < m_Maximum)
		{
			//std::cout << "Adding vertex..." << std::endl;
			memcpy_s(m_Vertices + m_VertexCount, sizeof(GLfloat) * 3, NewVertex, sizeof(GLfloat) * 3);
			memcpy_s(m_Normals + m_VertexCount, sizeof(GLfloat) * 3, NewNormal, sizeof(GLfloat) * 3);

			m_Indices[m_IndexCount] = m_VertexCount / 3;
			m_IndexCount++;
			m_VertexCount += 3;
		}
	}
}

void CTriangleMesh::End(void)
{
	/*std::cout << "Listing..." << std::endl;

	for (int i = 0; i < m_CurrentIndex; i++)
	{
		std::cout << "	Index " << i << ", vertex " << m_Indices[i] << std::endl;
		CVector4 *Vertex = (CVector4 *)(m_Vertices + m_Indices[i] * 3);
		std::cout << "		" << Vertex->m_Data[0] << " " << Vertex->m_Data[1] << " " << Vertex->m_Data[2] << std::endl;
	}*/

	glGenVertexArrays(1, &m_VertexObject);
	glBindVertexArray(m_VertexObject);

	glGenBuffers(1, &m_VertexArray);
	glGenBuffers(1, &m_IndexArray);
	glGenBuffers(1, &m_NormalArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, m_Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_NormalArray);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, m_Normals, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_IndexCount, m_Indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	delete [] m_Indices;
	delete [] m_Vertices;
	delete [] m_Normals;

	m_Indices = 0;
	m_Vertices = 0;
	m_Normals = 0;
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

CTriangleMesh::~CTriangleMesh(void)
{
	delete [] m_Indices;
	delete [] m_Vertices;
}
