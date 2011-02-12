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

// Use from client application ONLY
// Just include EVERYTHING

#ifndef __RB_EXTERNAL_ARGS__
#define __RB_EXTERNAL_ARGS__

#ifndef _WIN32
int __argc;
char **__argv;
#endif

#define RB_PARSE_ARGUMENTS(c, v) __argc = c; __argv = v;

#endif

#include "Core/Platform.h"
#include "Core/CEngine.h"

#include "Core/CCamera.h"
#include "Core/CEntity.h"
#include "Core/CMesh.h"
#include "Core/CModel.h"
#include "Core/CTriangleMesh.h"

#include "Helpers/CMatrixManager.h"
#include "Helpers/CObjReader.h"
#include "Helpers/CTextureManager.h"
#include "Helpers/CTimer.h"

#include "Shaders/CDLShader.h"
#include "Shaders/CFlatShader.h"
#include "Shaders/CIdentityShader.h"
#include "Shaders/CPhongShader.h"
#include "Shaders/CShaderBase.h"
