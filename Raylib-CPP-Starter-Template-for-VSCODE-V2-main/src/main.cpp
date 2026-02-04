#include <raylib.h>
#include "toppings.h"
#include <ctime>
#include <cstdlib>

int main() {
    InitWindow(800, 800, "Papa's Pizza Clone");

    srand(time(nullptr));

    while(!WindowShouldClose()) {
        // closes window on mouse click
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            break; // exit game loop
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawToppingsOnSquare();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}