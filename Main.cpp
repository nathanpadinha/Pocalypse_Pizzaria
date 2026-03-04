#include "Constents.hpp"
#include "PizzaCook.hpp"
#include "Pizza.hpp"

int main()
{
    // Initialize window
    InitWindow(800, 600, "Pocalypse Pizzaria");
    
    SetTargetFPS(60);

    // Using Switch Case to determine which screen is running
    enum gameState {Default, OrderTake, AddToppings, PizzaCook, PizzaCut};
    gameState currentState = Default;
    //Default is maybe the intro screen? idk

    /**
     * Create the cooking stage and pizza objects
     * * CookingStage handles the stove area
     * * Pizza represents the pizza being cooked
     */
    CookingStage cookingStage;
    Pizza pizza;

    // Main game loop
    while (!WindowShouldClose())
    {
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
                // Do default behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Default state (intro maybe?)", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case OrderTake:
                // Do order taking behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Taking in the orders", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case AddToppings:
                // Do topping-adding behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Topping the toppings!", 10, 10, 20, BLACK);
                EndDrawing();
                break;
            case PizzaCook: {
                /**
                 * Update cooking stage logic
                 * * dt represents the time between frames
                 */
                float dt = GetFrameTime();
                cookingStage.update(dt);

                // Do pizza cooking behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);

                cookingStage.draw();

                /**
                 * Get stove position and center the pizza on it
                 * * This allows the pizza to always appear on the stove
                 */
                Rectangle stove = cookingStage.getStoveArea();
                Vector2 center = {stove.x + stove.width/2, stove.y + stove.height/2};
                pizza.setPosition(center);

                /**
                 * Draw the pizza
                 * * Currently draws the pizza base in the center of the stove
                 */
                pizza.draw();

                DrawText("Cookin da pizza", 10, 10, 20, BLACK);
                EndDrawing();
            } break;
            case PizzaCut:
                // do pizza cutting behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Chop Chop Chop", 10, 10, 20, BLACK);
                EndDrawing();
                break;
        }





    }
    
    // De-initialization
    CloseWindow();
    
    return 0;
}