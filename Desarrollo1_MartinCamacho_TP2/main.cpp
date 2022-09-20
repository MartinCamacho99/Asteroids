#include "raylib.h"
#include "cmath"
#include "raymath.h"


using namespace std;

int main()
{
    // Inicialización
    InitWindow(1280, 720, "Asteroid");

   
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
    // Loop

    while (!WindowShouldClose())
    {
        // Chequeo de Input
        //a
        mousePos.x = GetMouseX();
        mousePos.y = GetMouseY();
        shipPos.x = ship.x + origin.x;
        shipPos.y = ship.y + origin.y;
        dir.x = mousePos.x - shipPos.x;
        dir.y = mousePos.y - shipPos.y;
        rotation = atan(dir.y / dir.x)* 180 / PI;

        // Actualización

        // Dibujado

        BeginDrawing();
        ClearBackground(WHITE); 
        DrawRectanglePro(ship,origin, rotation,RED);

        EndDrawing();
    }

    // Cierre
    CloseWindow();
}