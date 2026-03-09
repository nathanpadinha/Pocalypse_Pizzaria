#pragma once

#include "TextureManager.hpp"
#include "Constents.hpp"
#include "OrderTake.hpp"
#include "TicketRack.hpp"
#include "PizzaCook.hpp"
#include "Pizza.hpp"
#define MAX_SEED_SIZE 9

int seedEntry();


int main()
{

    int frameNumber = 0;

    // Initialize window
    InitWindow(1600, 900, "Pocalypse Pizzaria");

    SetTargetFPS(60);

    OrderTake customerManager;

    texturemanager.LoadAllTextures();

    // Using Switch Case to determine which screen is running
    gameState currentState;
    currentState = Default;
    //Default is maybe the intro screen? idk

    int seed = 1234;

    //Create a ticket rack
    TicketRack ticketRack(&currentState);


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
        //currentState = Default;
        // Just switching through the windows with number keys
        if (IsKeyPressed(KEY_ONE)) {
            currentState = Default;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            currentState = OrderTaking;
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


        
        BeginDrawing();
        
        switch (currentState) {
            case Default:
                // Do default behavior

                //get seed, use it to seed rand();
                seed = seedEntry();
                srand(seed);

                //switch to next state when seed is seeded
                currentState = OrderTaking;
                break;
            case OrderTaking:
                // Do order taking behavior
                //Draw background
                ClearBackground(GREEN);
                customerManager.Update(&ticketRack);
                DrawTextureEx(texturemanager.FrontCounter, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);

                //Draw Ticket Rack

                ticketRack.DisplayRack();
                ticketRack.Update();
                ClearBackground(GREEN);
                DrawText("Taking in the orders", 200, 400, 30, BLACK);

                //generate an order
                if (IsKeyPressed(KEY_COMMA)){
                    ticketRack.AddOrder(Order(1, ticketRack.GetOrderQuantity()));
                }




                break;

            case AddToppings:
                // Do topping-adding behavior

                ticketRack.DisplayRack();
                ticketRack.Update();

                ClearBackground(YELLOW);
                DrawText("Topping the toppings!", 200, 400, 30, BLACK);
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
                break;
            } 
            
            case PizzaCut:
                // do pizza cutting behavior
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Chop Chop Chop", 10, 10, 20, BLACK);
                EndDrawing();
                break;
        }
        EndDrawing();





    }
    
    // De-initialization
    CloseWindow();
    
    return 0;
}



//This is mostly stolen from https://www.raylib.com/examples/text/loader.html?name=text_input_box
// I (Elliot) can improve upon this a ton later, this is suuuper sloppy. 
int seedEntry(){

    char seedArray[MAX_SEED_SIZE];
    int letterCount = 0;
    bool seedEntryDone = false;
    int seed;


    Rectangle textBox = { GetScreenWidth()/2.0f - 250, GetScreenHeight()/2.0f - 25, 500, 50 };

    bool mouseOnText = false;

    float pizzaRotation = 0;

    while(!WindowShouldClose() && !seedEntryDone){
        int key = GetCharPressed();
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;
        if (mouseOnText){
            while (key > 0)
            {
                // keys 48-57 are number keys, to make sure seed doesn't have any chars in it
                if ((key >= 48) && (key <= 57) && (letterCount < MAX_SEED_SIZE))
                {
                    seedArray[letterCount] = (char)key;
                    seedArray[letterCount+1] = '\0'; // Add null terminator at the end of the string
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }       
            if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    seedArray[letterCount] = '\0';
                }
            if (IsKeyPressed(KEY_ENTER))
            {
                seed = atoi(seedArray);
                seedEntryDone = true;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);

        //draw things
        DrawTextureEx(texturemanager.TitleScreen, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);
        DrawTexturePro(texturemanager.DisplayPizza0, (Rectangle){0, 0, (float)texturemanager.DisplayPizza0.width, (float)texturemanager.DisplayPizza0.height}, (Rectangle){200, 450, (float)texturemanager.DisplayPizza0.width * 12.5f, (float)texturemanager.DisplayPizza0.height* 12.5f}, (Vector2){texturemanager.DisplayPizza0.width * 12.5f /2.0f, texturemanager.DisplayPizza0.height * 12.5f/2.0f}, pizzaRotation, WHITE);
        DrawTexturePro(texturemanager.DisplayPizza1, (Rectangle){0, 0, (float)texturemanager.DisplayPizza1.width, (float)texturemanager.DisplayPizza1.height}, (Rectangle){1400, 450, (float)texturemanager.DisplayPizza1.width * 12.5f, (float)texturemanager.DisplayPizza1.height* 12.5f}, (Vector2){texturemanager.DisplayPizza1.width * 12.5f /2.0f, texturemanager.DisplayPizza1.height * 12.5f/2.0f}, pizzaRotation, WHITE);


        //DrawTextureEx(texturemanager.DisplayPizza1, (Vector2){1140, 290}, pizzaRotation, 12.5f, WHITE);
        pizzaRotation += 1.2f;


        DrawText("Hover over input box to enter seed", GetScreenWidth()/2.0f - 200, GetScreenHeight()/2.0f - 50, 20, GRAY);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

        DrawText(seedArray, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        DrawText(TextFormat("Seed length: %i/%i", letterCount, MAX_SEED_SIZE), GetScreenWidth()/2.0f - 100, GetScreenHeight()/2.0f + 30, 20, DARKGRAY);

        if (mouseOnText)
        {
            if (letterCount < MAX_SEED_SIZE)
            {
                // Draw blinking underscore char
                if (((60/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(seedArray, 40), (int)textBox.y + 12, 40, MAROON);
            }
            else DrawText("Press BACKSPACE to delete chars...", GetScreenWidth()/2.0f - 175, GetScreenHeight()/2.0f + 50, 20, GRAY);
        }

        EndDrawing();
    }
    cout<<seed;
    return seed;
}