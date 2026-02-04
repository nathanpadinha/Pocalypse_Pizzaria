#include "toppings.h"

void DrawToppingsOnSquare() {
    static bool initialized = false;
    static Vector2 toppings[15];

    const int radius = 15;

    // Random position for toppings
    if(!initialized) {
        for(int i = 0; i < 15; i++) {
            toppings[i].x = GetRandomValue(200 + radius, 500 - radius);
            toppings[i].y = GetRandomValue(200 + radius, 500 - radius);
        }
        initialized = true;
    }

    // Pizza base
    DrawRectangle(200, 200, 300, 300, BEIGE);    

    // Toppings
    for(int i = 0; i < 15; i++) {
        DrawCircle(toppings[i].x, toppings[i].y, radius, RED);
    }
}