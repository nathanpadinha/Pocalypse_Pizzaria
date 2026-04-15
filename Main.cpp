#include "raylib.h"
#include "Pizza.hpp"
#include "AddToppings.hpp"

Pizza currentPizza;

int main()
{
    InitWindow(800, 700, "Pizza Game Hub");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Run your minigame
        AddToppings();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}