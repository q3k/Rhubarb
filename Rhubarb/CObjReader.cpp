#include "CObjReader.h"
using namespace rb;

#include <fstream>
#include <iostream>
#include <cstring>

#include "CVector4.h"

CObjReader::CObjReader(std::string Filename)
{
	m_Filename = std::string(Filename);
}

void CObjReader::Read(CTriangleMesh &Target)
{
	std::ifstream File;
	File.open(m_Filename, std::ios::binary | std::ios::in);

	if (!File.is_open())
		return;

	std::string Keyword;
	std::string Line;

	while (!File.eof())
	{
		File >> Keyword;

		if (Keyword == "v")
		{
			GLfloat X, Y, Z;
			File >> X >> Y >> Z;

			m_Vertices.push_back(X);
			m_Vertices.push_back(Y);
			m_Vertices.push_back(Z);
		}
		else if (Keyword == "f")
		{
			GLushort A, B, C;
			File >> A >> B >> C;

			m_Indices.push_back(A - 1);
			m_Indices.push_back(B - 1);
			m_Indices.push_back(C - 1);
		}
		else
			std::getline(File, Line);
	}

	int NumFloats = m_Vertices.size();
	int NumShorts = m_Indices.size();

	std::cout << "CObjReader: Read " << NumFloats / 3 << " vertices and " << NumShorts / 3 << " faces." << std::endl;

	Target.ReadLists(&m_Indices[0], NumShorts, &m_Vertices[0], NumFloats);
}

CObjReader::~CObjReader(void)
{
}
