#include "raylib.h"
#include "cmath"
#include "raymath.h"
#include "iostream"
// 
using namespace std;

int main()
{
    // Inicialización
    InitWindow(1080, 720, "Asteroid");

    const int MAXSHOOTS = 100;
    const int RADIUSBULLET = 3;
    Vector2 origin;
    Vector2 mousePos;
    Vector2 shipPos;
    Vector2 dir;
    Vector2 dirNormalized;
    Vector2 shipAce;

    struct Bullet
    {
        float centerX;
        float centerY;
        float radius;
        int timeLife;
        Vector2 vectorNormalizedbul;
        Color color;
        bool bulletActive;
    };
  
    Rectangle ship;
    ship.x = 320;
    ship.y = 240;
    ship.width = 50;
    ship.height = 50;

    
    origin.x = ship.width / 2;
    origin.y = ship.height /2;
    float rotation=0;

    
    shipAce.x = 1;
    shipAce.y = 1;

    Bullet bullet[MAXSHOOTS];

    for (int i = 0; i < MAXSHOOTS; i++)
    {
        bullet[i].centerX = 0;
        bullet[i].centerY = 0;
        bullet[i].radius = RADIUSBULLET;
        bullet[i].bulletActive = false;
        bullet[i].timeLife = 0;
        bullet[i].color = WHITE;
    }

    // Loop

    while (!WindowShouldClose())
    {
   
        // Actualización

        mousePos.x = static_cast<float> (GetMouseX());
        mousePos.y = static_cast<float> (GetMouseY());
        shipPos.x = ship.x + origin.x;
        shipPos.y = ship.y + origin.y;
        dir.x = mousePos.x - shipPos.x;
        dir.y = mousePos.y - shipPos.y;
        rotation = atan(dir.y / dir.x)* 180 / PI;

     
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            dirNormalized = Vector2Normalize(dir);
            shipAce.x += dirNormalized.x*0.1f;
            shipAce.y += dirNormalized.y *0.1f;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (int i = 0; i < MAXSHOOTS; i++)
            {
                if (!bullet[i].bulletActive)
                {
                    bullet[i].centerX = shipPos.x;
                    bullet[i].centerY = shipPos.y;
                    bullet[i].vectorNormalizedbul = Vector2Normalize(dir);
                    bullet[i].bulletActive = true;
                    break;
                }
             
            }

        }
     

        ship.x = ship.x + shipAce.x * GetFrameTime()*1;
        ship.y = ship.y + shipAce.y * GetFrameTime()*1;
        
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive)
            {
           
                    bullet[i].centerX += bullet[i].vectorNormalizedbul.x * GetFrameTime()*350;
                    bullet[i].centerY += bullet[i].vectorNormalizedbul.y * GetFrameTime()*350;
        
             
            }
        }
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive) bullet[i].timeLife++;
        }

        
        // Dibujado

        BeginDrawing();
        ClearBackground(BLACK); 
        DrawRectanglePro(ship,origin, rotation,RED);       
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive) DrawCircle(bullet[i].centerX , bullet[i].centerY, bullet[i].radius, bullet[i].color);
        }

        EndDrawing();
    }

    // Cierre
    CloseWindow();
}