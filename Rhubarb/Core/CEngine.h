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

#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Core/CCamera.h"
#include "Helpers/CMatrixManager.h"
#include "Helpers/CTextureManager.h"
#include "Helpers/CShaderManager.h"
#include "Helpers/CTimer.h"

#include <string>
#include <exception>

#define rbDegToRad(x)	((x)*0.017453292519943296f)

namespace rb
{
	typedef bool(*TRenderFunction)(float);

	namespace Exception
	{
		class FatalException : public std::exception
		{
			public:
				FatalException(const std::string Error) { m_Error = std::string(Error); }
				~FatalException(void) throw() {};
				virtual const char* what() const throw() { return m_Error.c_str(); }
			private:
				std::string m_Error;
		};
	};

	class CEngine
	{
		public:
			static CEngine *Get(void);

			void Initialize(unsigned int Width, unsigned int Height, std::string WindowName);
			void Start(void);

			void GetManagers(CMatrixManager **MatrixManager = 0, CShaderManager **ShaderManager = 0, CTextureManager **TextureManager = 0);
			void SetRenderFunction(TRenderFunction Function);

			void SetClearColor(float R, float G, float B);

			void Log(std::string Message);
			void Error(std::string Message);
			void Fatal(std::string Message);

			void SetCamera(CCamera *Camera);
			CCamera *GetCamera(void);
		private:
			CEngine(void);
			~CEngine(void);

			static CEngine *m_Singleton;
			static bool m_Spawned;
			static bool m_Initialized;
			static void m_sRenderFunction(void);
			static void m_sChangeSizeFunction(int Width, int Height);
			static void m_sMouseMotionFunction(int X, int Y);

			CMatrixManager *m_MatrixManager;
			CTextureManager *m_TextureManager;
			CShaderManager *m_ShaderManager;
			CTimer *m_Timer;			
			CCamera *m_Camera;

			CTimer m_FPSTimer;

			unsigned int m_Width;
			unsigned int m_Height;

			std::string m_WindowName;

			TRenderFunction m_ClientRenderFunction;

			void RenderFunction(void);
			void ChangeSizeFunction(int Width, int Height);		
			void MouseMotionFunction(int X, int Y);
	};
};

