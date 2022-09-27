#include "raylib.h"
#include "cmath"
#include "raymath.h"


using namespace std;

int main()
{
    // Inicialización
    InitWindow(1920, 0, "Asteroid");

    struct Bullet
    {
        float centerX;
        float centerY;
        float radius;
        Color color;
        bool bulletActive;
    };
  

    Rectangle ship;
    ship.x = 320;
    ship.y = 240;
    ship.width = 50;
    ship.height = 50;

    Vector2 origin;
    origin.x = ship.width / 2;
    origin.y = ship.height /2;
    float rotation=0;

    Vector2 mousePos;
    Vector2 shipPos;
    Vector2 dir;
    Vector2 dirNormalized;
    Vector2 dirNormalizedbul;
    Vector2 shipAce;
    shipAce.x = 1;
    shipAce.y = 1;

    Bullet bullet[100];
    bullet[1].centerX = 100;
    bullet[1].centerY = 100;
    bullet[1].radius = 1;
    bullet[1].color = YELLOW;
    bullet[1].bulletActive = false;

    // Loop

    while (!WindowShouldClose())
    {
        // Chequeo de Input
        mousePos.x = GetMouseX();
        mousePos.y = GetMouseY();
        shipPos.x = ship.x + origin.x;
        shipPos.y = ship.y + origin.y;
        dir.x = mousePos.x - shipPos.x;
        dir.y = mousePos.y - shipPos.y;
        rotation = atan(dir.y / dir.x)* 180 / PI;

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            dirNormalized = Vector2Normalize(dir);
            shipAce.x += dirNormalized.x*0.1;
            shipAce.y += dirNormalized.y * 0.1;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            bullet[1].bulletActive = true;
            dirNormalizedbul = Vector2Normalize(dir);

            bullet[1].centerX += dirNormalizedbul.x*0.01;
            bullet[1].centerY += dirNormalizedbul.y * 0.01;

        }
     

        ship.x = ship.x + shipAce.x * GetFrameTime();
        ship.y = ship.y + shipAce.y * GetFrameTime();
        

        // Actualización

        // Dibujado

        BeginDrawing();
        ClearBackground(BLACK); 
        DrawRectanglePro(ship,origin, rotation,RED);       
        DrawCircle(bullet[1].centerX, bullet[1].centerY, bullet[1].radius, bullet[1].color);


        EndDrawing();
    }

    // Cierre
    CloseWindow();
}