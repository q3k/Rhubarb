#pragma once

namespace rb
{
	class CVector4
	{
		public:
			CVector4(void);
			~CVector4(void);

			float Dot(CVector4 &Vector);
			void Cross(CVector4 &Vector, CVector4 &Target);

			void Add(CVector4 &Vector, CVector4 &Target);
			void Subtract(CVector4 &Vector, CVector4 &Target);
			
			void Add(CVector4 &Vector);
			void Subtract(CVector4 &Vector);

			void Normalize(void);
			void Normalize(CVector4 &Target);

			float m_Data[4];
	};
}

