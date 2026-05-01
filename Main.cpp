#pragma once

//#include "TextureManager.hpp" is included in constents.hpp
#include "Constents.hpp"
#include "TicketRack.hpp"


//INCLUDE MINIGAMES
#include "OrderTake.hpp"
//#include "PizzaCookGame.hpp"
#include "AddToppingsGame.hpp"
#include "PizzaCutGame.hpp"
#include "PizzaCook.hpp"



#include "Pizza.hpp"
#include "OrderTake.hpp"
#include "Customer.hpp"


#define MAX_SEED_SIZE 9

int seedEntry();



extern RandomClass RNG;

int main(){
    vector <Customer> customers(4);
    vector <Pizza> PizzaList(4);

    //*Variable Decleration
    int day = 0, dayTimeFrame = 0, seed = 1234, points = 0;
    string pointsText = "";

    
    int customerScheduleDifficulty[3][4] = {//2d array for order difficulty
        {1, 2, 1, 2}, //day 0
        {2, 3, 1, 3}, //day 1
        {4, 3, 2, 4}  //day 2
    };
    
    gameState currentState = Default;//Used to figure out what mini game should be displayed
    OrderTake customerManager;
    TicketRack ticketRack(&currentState);//Create a ticket rack


//*Set window and framerate
    InitWindow(1600, 900, "'Pocalypse Pizzaria"); SetTargetFPS(60);
//*Load Textures    
    texturemanager.LoadAllTextures();    

    CookingManager cookingManager;


//*Main game loop
    
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
            currentState = ToppingsAdd;
        }
        else if (IsKeyPressed(KEY_FOUR)) {
            currentState = PizzaCook;
        }
        else if (IsKeyPressed(KEY_FIVE)) {
            currentState = PizzaCut;
        }
        else if (IsKeyPressed(KEY_SIX)){
            currentState = EverythingComplete;
        }



        BeginDrawing();
        
        switch (currentState) {
            case Default:
                // Do default behavior

                //Update rand() to RandomClass
                seed = seedEntry();
                RNG.seed(seed);
                dayTimeFrame = -1;

                //switch to next state when seed is seeded
                currentState = OrderTaking;
                break;

            case OrderTaking:
                // Do order taking behavior
                //Draw background
                DrawTextureEx(texturemanager.FrontCounterBackground, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);
                //ClearBackground(GREEN);
                
                ticketRack.DisplayRack();
                ticketRack.Update();

                for (int i = 0; i < 4; i++){
                    bool pizzaReadyToSubmit = (PizzaList[i].getState() == Submitting) || (PizzaList[i].getState() == Cutting);
                    if (ticketRack.GetOrder(i).CheckCompletionBehavior(pizzaReadyToSubmit)){
                            if (PizzaList[i].getState() == Cutting){
                            PizzaList[i].setState(Submitting);
                        }
                        customerManager.pizzasDone[i] = true;
                    }
                }
                
            
                customerManager.Update(&ticketRack, dayTimeFrame, customerScheduleDifficulty, day, PizzaList, customers, points);
                //! TERNARY OPERATOR used to animate, avert your eyes N
                if (!customerManager.chompMode) DrawTextureEx(texturemanager.FrontCounter[dayTimeFrame % 60 <= 30 ? 0 : 1], (Vector2){0, 0}, 0.0f, 25.0f, WHITE);

                //! Okay it's safe now

                //Draw Ticket Rack


                //ClearBackground(GREEN);

                //! DEPRECATED generate an order 
                // if (IsKeyPressed(KEY_COMMA)){
                //     ticketRack.AddOrder(Order(1, ticketRack.GetOrderQuantity()));
                // }




                break;

            case ToppingsAdd:
                // Do topping-adding behavior
                DrawTextureEx(texturemanager.ToppingTable, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);

                ticketRack.DisplayRack();
                ticketRack.Update();
     
                ClearBackground(YELLOW);
                playAddToppings(PizzaList.data(), currentState);


               
                break;
            case PizzaCook: {
                
                // /**
                //  * Update cooking stage logic
                //  * * dt represents the time between frames
                //  */              
                ClearBackground(ORANGE);
                DrawTextureEx(cookingManager.overcharge ? texturemanager.OVERCHARGE[dayTimeFrame % 60 < 30 ? 1 : 0] : texturemanager.PizzaGrillz[dayTimeFrame % 120 <= 30 ? 0 : (dayTimeFrame % 120 <= 60 ? 1 : (dayTimeFrame % 120 <= 90 ? 2 : 3))], (Vector2){0, 0}, 0.0f, 25.0f, WHITE);
                
                //playPizzaCook(PizzaList);
                cookingManager.update(dayTimeFrame, PizzaList.data());
                ticketRack.DisplayRack();
                ticketRack.Update();


                /**
                 * Draw the pizza
                 * * Currently draws the pizza base in the center of the stove
                 */
                //pizza.draw();
                DrawText("Cookin da pizza", 10, 10, 20, BLACK);
                break;
            } 
            
            case PizzaCut:
                // do pizza cutting behavior
                DrawTextureEx(texturemanager.SlicingTable, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);

                ticketRack.DisplayRack();
                ticketRack.Update();
                
                ClearBackground(BLUE);

                playPizzaCut(PizzaList.data());
                
                DrawText("Chop Chop Chop", 10, 10, 20, BLACK);
                break;

                //TODO Colin, here's the end state to write some code into. You can access it in-game with (6)
            case EverythingComplete:
                //do some stuff here

                break;
        }
        pointsText = "Points: " + to_string(points);
        DrawText(pointsText.c_str() , 100, 100, 20, LIGHTGRAY);
        EndDrawing();



        dayTimeFrame++;

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
        // DrawTexturePro(texturemanager.DisplayPizza0, (Rectangle){0, 0, (float)texturemanager.DisplayPizza0.width, (float)texturemanager.DisplayPizza0.height}, (Rectangle){200, 450, (float)texturemanager.DisplayPizza0.width * 12.5f, (float)texturemanager.DisplayPizza0.height* 12.5f}, (Vector2){texturemanager.DisplayPizza0.width * 12.5f /2.0f, texturemanager.DisplayPizza0.height * 12.5f/2.0f}, pizzaRotation, WHITE);
        // DrawTexturePro(texturemanager.DisplayPizza1, (Rectangle){0, 0, (float)texturemanager.DisplayPizza1.width, (float)texturemanager.DisplayPizza1.height}, (Rectangle){1400, 450, (float)texturemanager.DisplayPizza1.width * 12.5f, (float)texturemanager.DisplayPizza1.height* 12.5f}, (Vector2){texturemanager.DisplayPizza1.width * 12.5f /2.0f, texturemanager.DisplayPizza1.height * 12.5f/2.0f}, pizzaRotation, WHITE);


        //DrawTextureEx(texturemanager.DisplayPizza1, (Vector2){1140, 290}, pizzaRotation, 12.5f, WHITE);
        pizzaRotation += 1.2f;


        DrawText("Hover over input box to enter seed", GetScreenWidth()/2.0f - 200, GetScreenHeight()/2.0f - 50, 20, DARKGRAY);

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