#pragma once

#include "Order.hpp"

//Base ticket height/width, scaled with scale
#define TICKET_WIDTH 190
#define TICKET_HEIGHT 250

#define SAUCE_TYPES 3
#define TOPPING_TYPES 6
#define MAX_TOPPINGS 6
#define MAX_SLICES 8

/*
Variables for Order: 
int sauceID - Any integer from 1-3. Not doing 0 because 0 is used in ToppingID to indicate no topping.
int toppingID[3] - Any integer from 1-6, 0 is no topping
int toppingAmount[3] - Randomized amount from 1-6
int cookTime - Randomized time from 5-20 seconds
int sliceAmount - Even number of slices, 2, 4, 6, or 8
*/


/*
sauceID -
1 - Blood
2 - Tomato Sauce
3 - Radioactive Sludge
*/


/*
ToppingID - 
1 - Mouse Brain
2 - Human Pepperoni
3 - Fingers
4 - Glowing Mushrooms
5 - Tooth Pepper
6 - Pineapple

Adding more to this list is simple, just increment TOPPING_TYPES at the top of OrderTake.cpp, and change Order::TranslateTopping to show the new topping. 
*/

//default constructor for inactive order that isn't displayed in the rack. 
Order::Order()
{
    isActive = false;
}



//does not currently use difficulty
Order::Order(int difficulty, int ticketQuantity)
{
    //Was on my this-> phase for a bit here, no idea why. Looks nice though. 
    this->x = 150 + (ticketQuantity * (200));
    this->y = GetScreenHeight() / 13;   
    doingstuff = false;
    isActive = true;

    //See sauce and topping IDs in Order.cpp for more info
    //sauce
    this->sauceID = rand() % SAUCE_TYPES + 1; //Random sauce ID from 1-SAUCE_TYPES

    //toppings
    this->toppingID[0] = rand() % TOPPING_TYPES + 1; //Fills first topping with random topping ID from 1-TOPPING_TYPES
    if (rand() % 2 == 0) { //50% chance to have only 1 topping
        this->toppingID[1] = 0; //0 is null topping
        this->toppingID[2] = 0;
    } 
    else {
        this->toppingID[1] = rand() % TOPPING_TYPES + 1;
        if (rand() % 2 == 0) { //Another 50% chance to not move on to having 3 toppings
            this->toppingID[2] = 0;
        } 
        else {//3 toppings
            this->toppingID[2] = rand() % TOPPING_TYPES + 1; 
        }
    }

    //Duplicate topping protection
    if (this->toppingID[1] == this->toppingID[0]) { 
        this->toppingID[1] = 0;
    }
    if (this->toppingID[2] == this->toppingID[0] || this->toppingID[2] == this->toppingID[1]) { 
        this->toppingID[2] = 0;
    }


    //Random amount of each topping, 1-6. Technically 50% of the time it will be unnecessary to generate
    //the toppings for toppings 2 and 3, but just generating them regardless is lazier
    this->toppingAmount[0] = rand() % MAX_TOPPINGS + 1;
    this->toppingAmount[1] = rand() % MAX_TOPPINGS + 1;
    this->toppingAmount[2] = rand() % MAX_TOPPINGS + 1;
    
    //cooking
    int cookTimeOptions[4] = {10, 15, 20, 30}; //cook times in seconds
    this->cookTime = cookTimeOptions[rand() % 4]; 


    //Slice Options
    this->sliceAmount = (rand() % (MAX_SLICES / 2) + 1) * 2; //even number of slices, up to MAX_SLICES



    this->scale = 0.8;


}


void Order::Update()
{
    //1.49, and 0.8 look alright for the tickets
    Order::GetScaleFromDistanceToStagingArea();
    Order::TicketDraggingBehavior();
    Order::DisplayOrderAsTicket();

}

void Order::GetScaleFromDistanceToStagingArea()
{
    if (Vector2Distance(Vector2{(float)(x + (TICKET_WIDTH / 2)), (float)(y + (TICKET_HEIGHT / 2))}, Vector2{(float)(GetScreenWidth() * 6 / 7), (float)GetScreenHeight()/2}) > 220){
    scale =  0.8;
    }
    else scale = 1.49;
}




//Clean this up later with iterative spacing, rather than triple if statements
//Ticket resizes depending on near side-part or near rack
void Order::DisplayOrderAsTicket()
{



        //Draw outline (outline doesn't scale totally with scale, yet)
    DrawRectangle((int)(x)-2, (int)(y)-2, (int)(TICKET_WIDTH * scale)+4, (int)(TICKET_HEIGHT * scale)+4, DARKGRAY);

    DrawRectangle((int)(x), (int)(y), (int)(TICKET_WIDTH * scale), (int)(TICKET_HEIGHT * scale), WHITE); //ticket rectangle
    


    DrawText(("Sauce: " + Order::TranslateSauce(sauceID)).c_str(), (int)((x + (10 * scale))), (int)((y + (10 * scale))), (int)(14 * scale), BLACK);

    int toppingIteration = 0;
    while(toppingID[toppingIteration] != 0 && toppingIteration < 3){
        //! TERNARY OPERATOR HERE, AVERT YOUR EYES
        DrawText((to_string(toppingAmount[toppingIteration]) + " " + Order::TranslateTopping(toppingID[toppingIteration]) + ((toppingAmount[toppingIteration] > 1) ? "s" : "")).c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)))), (int)(14 * scale), BLACK);
        //! It's safe now
        DrawTextureEx(Order::ToppingIDtoTexture(toppingID[toppingIteration]), (Vector2){(float)((x + (150 * scale))), (float)((y + (35 * scale) + (toppingIteration * (28 * scale))))}, 0.0f, (float)(3.0 * scale), WHITE);
        toppingIteration++;
    }

    DrawText(("Cook Time: " + to_string(cookTime) + "s").c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)))), (int)(14 * scale), BLACK);
    toppingIteration++;
    DrawText(("Slices: " + to_string(sliceAmount)).c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)) + (20 * scale))), (int)(14 * scale), BLACK);
    //                                                                                                                                               Why tf is ^^ this here? idk. 
}




//Drags the ticket around by the mouse. Kind of a bad name because it also displays the ticket, but idk if there's an easy way
//to separate the dragging behavior and the display behavior without it being a bit confusing. 
void Order::TicketDraggingBehavior()
{

int mouseX = GetMouseX();
int mouseY = GetMouseY();

if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
{
    if (CheckCollisionPointRec(Vector2{(float)mouseX, (float)mouseY}, Rectangle{(float)x, (float)y, (float)(TICKET_WIDTH * scale), (float)(TICKET_HEIGHT * scale)})){ //if mouse is in the ticket
        doingstuff = true;
        offsetX = x - mouseX;
        offsetY = y - mouseY;
    }
}
//stops dragging if mouse is released
if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
{
    doingstuff = false;

}
//if dragging (I'll change this variable name later)
if(doingstuff)
{
    x = mouseX + offsetX;
    y = mouseY + offsetY;
}


}






//Translates topping ID to topping name
string Order::TranslateTopping(int ToppingID)
{
    switch (ToppingID) {
        case 1:
            return "Mouse Brain";
        case 2:
            return "Human Pepperoni";
        case 3:
            return "Fingers";
        case 4:
            return "Glowing Mushroom";
        case 5:
            return "Tooth Pepper";
        case 6:
            return "Pineapple";
    }
    return "";
}

//Translates sauce ID to sauce name
string Order::TranslateSauce(int SauceID)
{
    switch (SauceID) {
        case 1:
            return "Blood";
        case 2:
            return "Tomato Sauce";
        case 3:
            return "Radioactive Sludge";
    }
    return "";
}



Texture2D Order::ToppingIDtoTexture(int ToppingID){
    switch (ToppingID) {
        case 1:
            return texturemanager.MouseBrain;
        case 2:
            return texturemanager.HumanPepperoni;
        case 3:
            return texturemanager.Finger;
        case 4:
            return texturemanager.GlowingMushroom;
        case 5:
            return texturemanager.ToothPepper;
        case 6:
            return texturemanager.Pineapple;
    }


}
