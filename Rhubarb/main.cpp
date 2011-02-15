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

#include <iostream>
#include <cmath>

#include "Rhubarb.h"

rb::CEngine *g_Engine = rb::CEngine::Get();
rb::CModel Model;
//rb::CModel Text;
rb::CCamera Camera;

bool fnRender(float DeltaTime)
{
	static float Color = 0.0f;
	Color += DeltaTime;

	Model.RotateLocal(rbDegToRad(DeltaTime * 100), 0.0f, 1.0f, 0.0f);
	//Text.RotateWorld(-rbDegToRad(DeltaTime * 100), 0.0f, 1.0f, 0.0f);

	//Text.SetDiffuseColor((sinf(Color) / 2.0f) + 0.5f, (sinf(Color + 2.094f) / 2.0f) + 0.5f, (sinf(Color + 4.188f) / 2.0f) + 0.5f, 1.0f);

	Model.Draw();
	//Text.Draw();

	return true;
}

int main(int argc, char **argv)
{
	RB_PARSE_ARGUMENTS(argc, argv);
	g_Engine->Initialize(800, 600, "Rhubarb Demo");

	Model.Load("Data/japanknife.model");
	//Text.Load("Data/text.model");
	Model.RotateLocal(rbDegToRad(45.0f), 0.0f, 0.0f, 1.0f);
	
	Camera.SetPosition(0.0f, 14.0f, 20.0f);

    rb::CVector4 LookTarget(-2.0f, 4.0f, 0.0f);
	Camera.LookAt(LookTarget);

	g_Engine->SetClearColor(0.05f, 0.05f, 0.05f);
	g_Engine->SetRenderFunction(fnRender);
	g_Engine->SetCamera(&Camera);
	g_Engine->Start();
}
