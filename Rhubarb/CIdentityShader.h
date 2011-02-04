#pragma once
#include "CShaderBase.h"

namespace rb
{
	class CIdentityShader : public CShaderBase
	{
		public:
			CIdentityShader(void);
			~CIdentityShader(void);

			void Initialize(void);

			virtual void Use(float *Color);
	};
};

