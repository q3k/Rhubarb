#pragma once
#include "CShaderBase.h"

namespace rb
{
	class CIdentityShader : public CShaderBase
	{
		public:
			CIdentityShader(void);
			~CIdentityShader(void);

			virtual void InitializeAttributes(void);

			virtual void Use(float *Color);
	};
};

