#pragma once
#include "CShaderBase.h"

#include "CMatrix44.h"

namespace rb
{
	class CFlatShader : public CShaderBase
	{
		public:
			CFlatShader(void);
			~CFlatShader(void);

			virtual void InitializeAttributes(void);

			virtual void Use(float *Color, GLfloat *Matrix);
	};
};

