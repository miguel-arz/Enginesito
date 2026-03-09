// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Core/GlobalDefines.h"
#include <iostream>
#include "Prog2D-Raylib/raylib.h"
#include "Prog2D-Raylib/raymath.h"
#include "Render/RenderEngine.h"


#include "Core/Entity.h"
#include "Core/Component.h"
#include "Components/Render/SpriteRendererComponent.h"
#include "Core/Level.h"

#include "Core/pugixml.hpp"



int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;
  const char* sTitle = { "Ventana" };
  //
  CRenderEngine::Initialize();
  CRenderEngine::GetInstance()->InitializeRenderer(screenWidth, screenHeight, sTitle);

  CLevel oLevels;
  oLevels.LoadLevel("resources/levels/levels.ld");

  oLevels.Configure();
  oLevels.BeginPlay();

  while (!WindowShouldClose())
  {
	   float fTimeStep = GetFrameTime();
	  oLevels.PrePhysics(fTimeStep);
	  oLevels.PostPhysics(fTimeStep);
	  CRenderEngine::GetInstance()->Draw();
  }

  oLevels.EndPlay();
  oLevels.Delete();

  CRenderEngine::GetInstance()->DeleteRenderer();
  CRenderEngine::Delete();

  CloseAppWindow();

  ////Orkito----------------------------------

  //CEntity m_oOrkito;
  //m_oOrkito.SetPos(Vector2Scale(CRenderEngine::GetInstance()->GetWindowSize(), 0.5f));
  //m_oOrkito.SetRot(0.f);

 
  //pugi::xml_document oDoc;
  //pugi::xml_parse_result oResult = oDoc.load_file("resources/orkito/orkito.ed");

  //if (oResult)
  //{
	 // 

  //}


  //m_oOrkito.BeginPlay();

  //while (!WindowShouldClose())
  //{
  //  float fTimeStep = GetFrameTime();
  //  m_oOrkito.PrePhyshics(fTimeStep);
  //  m_oOrkito.PostPhyshics(fTimeStep);
  //     
  //  CRenderEngine::GetInstance()->Draw();
  //}

  //m_oOrkito.EndPlay();
  //
  //m_oOrkito.Delete();
  //
  //CRenderEngine::GetInstance()->DeleteRenderer();
  //CRenderEngine::Delete();

  //

  //CloseAppWindow();

  return 0;
}