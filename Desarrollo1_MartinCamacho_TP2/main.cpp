#include "raylib.h"
#include "cmath"
#include "raymath.h"
#include "iostream"
// 
using namespace std;

int main()
{
    InitWindow(1080, 720, "Asteroid");

    Texture2D texture= LoadTexture("../res/ship1.png");

    enum CurrentScreen
    {
        menu,
        creditos,
        juego
    };


    struct Bullet
    {
        Vector2 position;
        float radius;
        int timeLife;
        Vector2 vectorNormalizedbul;
        Color color;
        bool bulletActive;
    };

    const int MAXSHOOTS = 100;
    const int RADIUSBULLET = 3;
    Bullet bullet[MAXSHOOTS];
 
    for (int i = 0; i < MAXSHOOTS; i++)
    {
        bullet[i].position.x = 0;
        bullet[i].position.y = 0;
        bullet[i].radius = RADIUSBULLET;
        bullet[i].bulletActive = false;
        bullet[i].timeLife = 0;
        bullet[i].color = WHITE;
    }
    Vector2 bulletPosition = {0};
    Vector2 meteorPosition = { 0 };
  
    struct Meteor
    {
        Vector2 position;
        float radius;
        int timeLife;
        Vector2 vectorDir;
        Color color;
        bool meteorActive;
    };

    Meteor bigMeteor = { 0 };
    Meteor mediumMeteor[2] = { 0 };
    Meteor smallMeteor[4] = { 0 };

    bigMeteor.position.x = 80;
    bigMeteor.position.y = 80;
    bigMeteor.radius = 50;
    bigMeteor.timeLife = 0;
    bigMeteor.meteorActive = true;
    bigMeteor.color = BLUE;
    bigMeteor.vectorDir.x = 10;
    bigMeteor.vectorDir.y= 0;

    for (int i = 0; i < 2; i++)
    {
        mediumMeteor[i].position.x = 0;
        mediumMeteor[i].position.y = 0;
        mediumMeteor[i].radius = 20;
        mediumMeteor[i].meteorActive = false;
        mediumMeteor[i].color = BLUE;
    }

    int medMeteorCount = 0;

    Vector2 origin;
    Vector2 mousePos;
    Vector2 shipPos;
    Vector2 dir;
    Vector2 dirNormalized;
    Vector2 shipAce;
    Rectangle ship;
    ship.x = 520;
    ship.y = 540;
    ship.width = 50;
    ship.height = 50;
    origin.x = ship.width / 2;
    origin.y = ship.height /2;
    float rotation=0;    
    shipAce.x = 1;
    shipAce.y = 1;
  
 
    while (!WindowShouldClose())
    {
   
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
                    bullet[i].position.x = shipPos.x;
                    bullet[i].position.y = shipPos.y;
                    bullet[i].vectorNormalizedbul = Vector2Normalize(dir);
                    bullet[i].bulletActive = true;
                    break;
                }
                
            }

        }
     
        ship.x = ship.x + shipAce.x * GetFrameTime();
        ship.y = ship.y + shipAce.y * GetFrameTime();
        if (ship.x < 0)
        {
            ship.x = 1070;
        }
        else if (ship.x > 1070)
        {
            ship.x = 0;
        } if (ship.y < 0)
        {
            ship.y= 710;
        }
        else if (ship.y > 710)
        {
            ship.y = 0;
        }
        
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive)
            {
           
                    bullet[i].position.x += bullet[i].vectorNormalizedbul.x * GetFrameTime()*350;
                    bullet[i].position.y += bullet[i].vectorNormalizedbul.y * GetFrameTime()*350;
        
             
            }
        }
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive) bullet[i].timeLife++;
        }
        
        if(bigMeteor.meteorActive)
        {
            bigMeteor.position.x += bigMeteor.vectorDir.x * GetFrameTime() * 10;

            if (bigMeteor.position.x > 1080 - bigMeteor.radius + 10)
            {
                bigMeteor.position.x = bigMeteor.radius;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            if (mediumMeteor[i].meteorActive)
            {
                mediumMeteor[i].position.x += mediumMeteor[i].vectorDir.x * GetFrameTime() * 10;

                if (mediumMeteor[i].position.x > 1080 - mediumMeteor[i].radius + 10)
                {
                    mediumMeteor[i].position.x = mediumMeteor[i].radius;
                }
            }
        }

    

        for  (int i = 0; i < MAXSHOOTS ; i++)
        {
            if (bullet[i].bulletActive)
            {
                if (bigMeteor.meteorActive && CheckCollisionCircles(bullet[i].position, bullet[i].radius, bigMeteor.position, bigMeteor.radius))
                {
                    bigMeteor.meteorActive = false;
                    cout << "sos un peda";

                }
                for (int j = 0; j < 2; j++)
                {
                    if (medMeteorCount % 2 == 0)
                    {
                        mediumMeteor[j].position.x = bigMeteor.position.x;
                        mediumMeteor[j].position.y = mediumMeteor[j].position.y;
                        mediumMeteor[j].vectorDir.x = 10;
                    }
                    else
                    {
                        mediumMeteor[j].position.x = bigMeteor.position.x;
                        mediumMeteor[j].position.y = mediumMeteor[j].position.y;
                        mediumMeteor[j].vectorDir.x = -10;
                    }
                    mediumMeteor[j].meteorActive = true;
                    medMeteorCount++;

                }
            }
        }
        
        // Dibujado

        BeginDrawing();
        ClearBackground(BLACK); 
        DrawRectanglePro(ship,origin, rotation,RED);    
        DrawTexture(texture, 200, 200, WHITE);
        for (int i = 0; i < MAXSHOOTS; i++)
        {
            if (bullet[i].bulletActive) DrawCircle(static_cast<int>(bullet[i].position.x) , static_cast<int>( bullet[i].position.y), bullet[i].radius, bullet[i].color);
        }
        if (bigMeteor.meteorActive)
        {
            DrawCircle(static_cast<int>(bigMeteor.position.x), static_cast<int>(bigMeteor.position.y), bigMeteor.radius, bigMeteor.color);

        }
        for (int i = 0; i < 2; i++)
        {
            if (mediumMeteor[i].meteorActive)
            {
                DrawCircle(static_cast<int>(mediumMeteor[i].position.x), static_cast<int>(mediumMeteor[i].position.y), mediumMeteor[i].radius, mediumMeteor[i].color);

            }
        }
       
        EndDrawing();
        UnloadTexture(texture);
    }

    // Cierre
    CloseWindow();
}