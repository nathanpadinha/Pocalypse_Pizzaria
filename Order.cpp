#pragma once

#include "Order.hpp"

//Base ticket height/width, scaled with scale
#define TICKET_WIDTH 190
#define TICKET_HEIGHT 250

#define SAUCE_TYPES 3
#define TOPPING_TYPES 6
#define MAX_TOPPINGS 4 //further modified by order difficulty
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



/*difficulty supported goes up to 4

1: 1-2 toppings, 1-4 of each, 2-8 slices
2: 1-3 toppings, 2-5 of each, 4-8 slices
3: 2-3 toppings, 3-6 of each, 6-8 slices
4: 3 toppings, 4-7 of each, 8 slices



*/

Order::Order(int difficulty, int ticketQuantity, int customerId)
{
    //Was on my this-> phase for a bit here, no idea why. Looks nice though. 
    this->x = 150 + (ticketQuantity * (200));
    this->y = GetScreenHeight() / 13;   
    this->customerId = customerId;
    doingstuff = false;
    isActive = true;

    //See sauce and topping IDs in Order.cpp for more info
    //sauce
    this->sauceID = rand() % SAUCE_TYPES + 1; //Random sauce ID from 1-SAUCE_TYPES

    //toppings
    this->toppingID[0] = rand() % TOPPING_TYPES + 1; //Fills first topping with random topping ID from 1-TOPPING_TYPES
    if (rand() % 2 == 0 && difficulty <=2) { //50% chance to have only 1 topping, if difficulty is 1-2. Difficulties of 3-4 always have 2-3 toppings
        this->toppingID[1] = 0; //0 is null topping
        this->toppingID[2] = 0; 
    } 
    else {
        this->toppingID[1] = rand() % TOPPING_TYPES + 1;
        if ((rand() % 2 == 0 && difficulty <= 3) || difficulty == 1) { 
            //Another 50% chance to not move on to having 3 toppings. difficulty 4 always has 3 toppings, difficulty 1 can't have more than 2
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


    //Random amount of each topping, 1-6+difficulty. Technically 50% of the time it will be unnecessary to generate
    //the toppings for toppings 2 and 3, but just generating them regardless is lazier
    this->toppingAmount[0] = rand() % MAX_TOPPINGS + difficulty;
    this->toppingAmount[1] = rand() % MAX_TOPPINGS + difficulty;
    this->toppingAmount[2] = rand() % MAX_TOPPINGS + difficulty;
    
    //cooking, based on timer stage
    int cookTimeOptions[5] = {1, 2, 3, 6, 7}; //cook time based on timer stage
    this->cookTime = cookTimeOptions[rand() % 5]; 


    //Slice Options
    this->sliceAmount = (rand() % (MAX_SLICES / 2) + 1) * 2; //even number of slices, up to MAX_SLICES
    
    //adds more slices if too amount is too easy
    if (sliceAmount < difficulty * 2){
        sliceAmount = difficulty * 2;
    }

    

    this->scale = 0.8;


}


void Order::Update()
{
    //only do stuff if the ticket is active
    if(isActive){
        //1.49, and 0.8 look alright for the tickets
        Order::GetScaleFromDistanceToStagingArea();
        Order::TicketDraggingBehavior();
        Order::DisplayOrderAsTicket();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Rectangle{(float)(x + TICKET_WIDTH * scale - (30 * scale)), (float)(y + TICKET_HEIGHT * scale - (30 * scale)), (float)(25 * scale), (float)(25 * scale)})) {
            DoCompletionBehavior();
        }
    }

}

void Order::DoCompletionBehavior(){
    this->isActive = false;
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
    


        //Draw outline (outline doesn't scale totally with scale)
    DrawRectangle((int)(x)-2, (int)(y)-2, (int)(TICKET_WIDTH * scale)+4, (int)(TICKET_HEIGHT * scale)+4, DARKGRAY);

    DrawRectangle((int)(x), (int)(y), (int)(TICKET_WIDTH * scale), (int)(TICKET_HEIGHT * scale), WHITE); //ticket rectangle
    
    //Ticket Complete button. Temporary?
    DrawRectangle((int)(x + TICKET_WIDTH * scale - (30 * scale)), (int)(y + TICKET_HEIGHT * scale - (30 * scale)), (int)(25 * scale), (int)(25 * scale), GREEN);


    DrawText(("Sauce: " + Order::TranslateSauce(sauceID)).c_str(), (int)((x + (10 * scale))), (int)((y + (10 * scale))), (int)(14 * scale), BLACK);

    int toppingIteration = 0;
    while(toppingID[toppingIteration] != 0 && toppingIteration < 3){
        //! TERNARY OPERATOR HERE, AVERT YOUR EYES
        DrawText((to_string(toppingAmount[toppingIteration]) + " " + Order::TranslateTopping(toppingID[toppingIteration]) + ((toppingAmount[toppingIteration] > 1) ? "s" : "")).c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)))), (int)(14 * scale), BLACK);
        //! It's safe now
        DrawTextureEx(Order::ToppingIDtoTexture(toppingID[toppingIteration]), (Vector2){(float)((x + (150 * scale))), (float)((y + (35 * scale) + (toppingIteration * (28 * scale))))}, 0.0f, (float)(3.0 * scale), WHITE);
        toppingIteration++;
    }
    //cooktime draws timer icon
    DrawText("Cook Time: ", (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)))), (int)(14 * scale), BLACK);
    DrawTextureEx(texturemanager.Timer[cookTime], (Vector2){(float)((x + (145 * scale))), (float)((y + (35 * scale) + (toppingIteration * (28 * scale))))}, 0.0f, (float)(3.0 * scale), WHITE);
    toppingIteration++;

    DrawText(("Slices: " + to_string(sliceAmount)).c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)))), (int)(14 * scale), BLACK);
    toppingIteration++;

    DrawText(("CustomerID: " + to_string(customerId)).c_str(), (int)((x + (10 * scale))), (int)((y + (40 * scale) + (toppingIteration * (30 * scale)) + (20 * scale))), (int)(14 * scale), BLACK);

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
            return "Finger";
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
