// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../../Prog2D-Raylib/Source/Prog2D-Raylib/raylib.h"
#include "../../Prog2D-Raylib/Source/Prog2D-Raylib/raymath.h"


int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;
  Vector2 RectanglePos = { 400, 225 };
  int speed = 200;
  float angle = 0.0f;    
  float radius = 50.0f;
  float fRotation = 0.2f;
  

  
  InitWindow(screenWidth, screenHeight,"Programacion 2D 25-26");

  Image oImage = LoadImage("resources/Ethan-SpriteSheet.png");
  Texture2D oTexture = LoadTextureFromImage(oImage);
  UnloadImage(oImage);



  //int iLightSize = 100;
  //float fRadius = 20.f;
  //Vector2 vPivotCircle;
  //vPivotCircle.x = iLightSize / 2;
  //vPivotCircle.y = iLightSize / 2;
  //Color* cColor = new Color(sizeof(Color) * iLightSize * iLightSize);

  //for (int y = 0; y < iLightSize; y++)
  //{
  //    for (int x = 0; x < iLightSize; x++)
  //    {
  //        Vector2 V2(x, y);
  //        float dist = Vector2Distance(vPivotCircle, V2);
  //        if (dist < fRadius)
  //        {
  //            cColor[x + y * iLightSize] = WHITE;
  //        }
  //        else
  //        {
  //            cColor[x + y * iLightSize] = BLACK;

  //        }
  //    }
  //};

  //Image oLight;
  //oLight.data = cColor;
  //oLight.width = 100;
  //oLight.height = 100;
  //oLight.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
  //oLight.mipmaps = 1;


  //Texture2D oLightText = LoadTextureFromImage(oLight);
  //UnloadImage(oLight);

  while (!WindowShouldClose())
  {
      Vector2 CirclePos = GetMousePosition();
	  
      // Update 
    // ----------------------------------------------------------------------------------
      
      if (IsKeyDown(KEY_W) /*|| IsKeyPressed(KEY_W)*/)
      {
          RectanglePos.y -= speed * GetFrameTime() ;
      };
      if (IsKeyDown(KEY_S) /*|| IsKeyPressed(KEY_W)*/)
      {
          RectanglePos.y += speed * GetFrameTime() ;
      };
      if (IsKeyDown(KEY_A) /*|| IsKeyPressed(KEY_W)*/)
      {
          RectanglePos.x -= speed * GetFrameTime() ;
      };
      if (IsKeyDown(KEY_D) /*|| IsKeyPressed(KEY_W)*/)
      {
          RectanglePos.x += speed * GetFrameTime() ;
      };

     /* if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
      {

      }*/


    // Draw
    // ----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RED);
    HideCursor();

    /*DrawTexture(oTexture, 0.f, 0.f, WHITE);*/
    Rectangle oRectSource;
    oRectSource.x = 0; //pix inicio del Quad
    oRectSource.y = 0;
    oRectSource.width = oTexture.width / 9; //
    oRectSource.height = oTexture.height / 9;

    Rectangle oRectDest;
    oRectDest.x = 400.f; //world position
    oRectDest.y = 225.f;
    oRectDest.width  = oTexture.width ;
    oRectDest.height = oTexture.height ;

    Vector2 raton = GetMousePosition();
    
    Rectangle oRectDest2;
    oRectDest2.x = raton.x; //world position
    oRectDest2.y = raton.y;
    oRectDest2.width = oTexture.width;
    oRectDest2.height = oTexture.height;

   
    Vector2 vPivot;
    vPivot.x = oRectDest.width ;//coor de Quad de el pivote
    vPivot.y = oRectDest.height ;
    fRotation += fRotation * GetFrameTime();
    float fRotation2 = 0;

    Vector4 vUvs;
    vUvs.x = 0.f;
    vUvs.y = 0.f;
    vUvs.z = 1.f / 9.f;
    vUvs.w = 1.f / 9.f;

    Vector4 vUvs2;
    vUvs2.x = 0.f;
    vUvs2.y = 0.f;
    vUvs2.z = 1.f;
    vUvs2.w = 1.f;

    Vector4 vUvs3;
    vUvs3.x = 0.f;
    vUvs3.y = 0.f;
    vUvs3.z = 0.f;
    vUvs3.w = 0.f;


    Vector2 vPivotUVs;
    vPivotUVs.x = 0.5f;
    vPivotUVs.y = 0.5f;

    Vector2 vPivotUVs2;
    vPivotUVs2.x = 0;
    vPivotUVs2.y = 0;

    Vector2 vPivotUVs3;
    vPivotUVs3.x = 1;
    vPivotUVs3.y = 1;

    //--------------------------------------------------------




    


    /*DrawTexturePro(oTexture, oRectSource, oRectDest, vPivot, fRotation, WHITE);*/

   /* DrawTextureProUV(oTexture, vUvs, oRectDest2, vPivotUVs, fRotation, WHITE);
    DrawTextureProUV(oTexture, vUvs2, oRectDest, vPivotUVs2, fRotation2, WHITE);
    DrawTextureProUV(oTexture, vUvs2, oRectDest, vPivotUVs3, fRotation2, WHITE);*/


    /*DrawRectangle(RectanglePos.x, RectanglePos.y, 50, 50, BLACK);
    DrawCircle(CirclePos.x, CirclePos.y, 10.f, RED);*/
    
   /* BeginBlendMode(BLEND_MULTIPLIED);
    {
        DrawTextureProUV(oLightText, Vector4(0.f, 0.f, 1.f, 1.f), oRectDest, Vector2(0.5f, 0.5f), fRotation, WHITE);
    }
    EndBlendMode();*/

    EndDrawing();
  }

  // Texture unloading
  UnloadTexture(oTexture);
  //UnloadTexture(oLightText);

  CloseAppWindow();

  return 0;
}