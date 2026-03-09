#include "Constants.hpp"

int main()
{
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pocalypse Pizzaria");
    
    SetTargetFPS(60);

    // Using Switch Case to determine which screen is running
    enum gameState {Default, OrderTake, AddToppings, PizzaCook, PizzaCut};
    gameState currentState = Default;
    //Default is maybe the intro screen? idk

    // Main game loop
    while (!WindowShouldClose())
    {
        currentState = Default;
        // Just switching through the windows with number keys
        if (IsKeyPressed(KEY_ONE)) {
            currentState = Default;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            currentState = OrderTake;
        }
        else if (IsKeyPressed(KEY_THREE)) {
            currentState = AddToppings;
        }
        else if (IsKeyPressed(KEY_FOUR)) {
            currentState = PizzaCook;
        }
        else if (IsKeyPressed(KEY_FIVE)) {
            currentState = PizzaCut;
        }


        
        switch (currentState) {
            case Default:
                //TODO default behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Default state (intro maybe?)", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case OrderTake:
                //TODO order taking behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Taking in the orders", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case AddToppings:
                //TODO topping-adding behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Topping the toppings!", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case PizzaCook:
                //TODO pizza cooking behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Cookin da pizza", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case PizzaCut://Pizza Cutting Mini Game
                PizzaCutGM();
                break;
        }

        //





    }
    
    // De-initialization
    CloseWindow();
    
    return 0;
}