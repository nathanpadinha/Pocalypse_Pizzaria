#include "Constents.hpp"

int main()
{
    // Initialize window
    InitWindow(800, 600, "Pocalypse Pizzaria");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Pocalypse Pizzaria", 10, 10, 20, BLACK);
        EndDrawing();
    }
    
    // De-initialization
    CloseWindow();
    
    return 0;
}