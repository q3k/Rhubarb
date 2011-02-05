#pragma once
#include "CShaderBase.h"

#include "CMatrix44.h"
#include "CVector4.h"

namespace rb
{
	class CPhongShader : public CShaderBase
	{
		public:
			CPhongShader(void);
			~CPhongShader(void);

			virtual void InitializeAttributes(void);

			virtual void Use(float *Color, GLfloat *MVMatrix, GLfloat *PMatrix, CVector4 &Light);
	};
};

