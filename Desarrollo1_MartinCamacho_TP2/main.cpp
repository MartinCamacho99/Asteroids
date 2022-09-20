#include "raylib.h"
#include "cmath"


using namespace std;

int main()
{
    // Inicialización
    InitWindow(640, 480, "Asteroid");

   
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
        rotation = atan(dir.y / dir.x)* 180 / 3.14159265358979323846;

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