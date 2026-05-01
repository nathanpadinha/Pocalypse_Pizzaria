#pragma once
#include "AddToppingsGame.hpp"
#include <math.h>

#define TOPPING_COUNT 6
#define BASE_COUNT 3



vector <Topping> toppings;


    // Pizza in Center

    float pizzaRadius = 150.0f;

    // DONE BUTTON
    Rectangle doneButton = { 120, 170, 100, 40 };
    bool pizzaFinished = false;

    // ===== BASE TABLE =====
    Vector2 baseTablePos[BASE_COUNT] = {
        { 1012, 590 }, //blood
        { 1012, 390 }, //tomato
        { 1012, 790 } //green
    };

    Color baseColors[BASE_COUNT] = {
        (Color){120, 0, 0, 255},      // Blood
        (Color){255, 60, 60, 255},    // Tomato
        (Color){57, 255, 20, 255}     // Radioactive Sludge
    };

    const char* baseNames[BASE_COUNT] = {
        "Blood",
        "Tomato",
        "Radioactive Sludge"
    };

    Color currentPizzaColor = WHITE;

    // ===== TOPPING TABLE =====
    Vector2 tablePos[TOPPING_COUNT] = {
        { 60, 660 }, { 160, 540 }, { 260, 690 },
        { 160, 815 }, { 335, 835 }, { 485, 790 }
    };

    //*deprecated mostly
    Color toppingColors[TOPPING_COUNT] = {
        (Color){255,224,189,255}, // Finger
        GREEN,                    // Glowing Mushroom
        ORANGE,                   // Human Pepperoni
        PINK,                     // Mouse Brain
        YELLOW,                   // Pineapple
        RED                       // Tooth Pepper
    };

    const char* toppingNames[TOPPING_COUNT] = {
        "Finger",
        "Glowing Mushroom",
        "Human Pepperoni",
        "Mouse Brain",
        "Pineapple",
        "Tooth Pepper"
    };

    int draggingIndex = -1;

    Pizza testPizza; 
    Pizza* PlayerPizza = &testPizza;

void playAddToppings(Pizza PizzaList[], gameState &currentState){

        //set active pizza   "PlayerPizza" to point to the newest pizza that should be topped with toppings 
        if (PizzaList[0].getState() == Toppling) PlayerPizza = &PizzaList[0];
        else if (PizzaList[1].getState() == Toppling) PlayerPizza = &PizzaList[1];
        else if (PizzaList[2].getState() == Toppling) PlayerPizza = &PizzaList[2];
        else if (PizzaList[3].getState() == Toppling) PlayerPizza = &PizzaList[3];
        else {
            PlayerPizza = &testPizza;
            (*PlayerPizza).setActive(false);
        }






        //this variable needs to be done here
        //Vector2 pizzaCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - 150 };

        Vector2 pizzaCenter = {540, 430}; //hardcoding this because I'm pretty sure we gave up on resizing the window
        (*PlayerPizza).setPosition(pizzaCenter);

        Vector2 mouse = GetMousePosition();

        // ===== CLICK LOGIC =====
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !pizzaFinished){
            if (CheckCollisionPointRec(mouse, doneButton)){
                pizzaFinished = true;
            }

            // Bases
            for (int i = 0; i < BASE_COUNT; i++){
                if (CheckCollisionPointCircle(mouse, baseTablePos[i], 60)){
                    currentPizzaColor = baseColors[i];
                    (*PlayerPizza).setSauceID(i+1);
                }
            }


            //! Toppings
            for (int i = 0; i < TOPPING_COUNT; i++){
                if (CheckCollisionPointCircle(mouse, tablePos[i], 40)){
                    toppings.emplace_back(toppingNames[i], mouse, pizzaCenter ,true);
                    draggingIndex = toppings.size() - 1;
                }
            }
        }

        // Drag
        if (draggingIndex != -1 && !pizzaFinished){
            toppings[draggingIndex].setDragPosition(mouse);
        }

        // Drop
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && draggingIndex != -1 && !pizzaFinished)
        {
            float dx = mouse.x - pizzaCenter.x;
            float dy = mouse.y - pizzaCenter.y;
            float distance = sqrtf(dx*dx + dy*dy);
            float toppingRadius = 12.0f;

            if (distance <= pizzaRadius - toppingRadius){
                toppings[draggingIndex].attachToPizza(pizzaCenter);
            }else if (distance <= pizzaRadius){
                float angle = atan2f(dy, dx);
                toppings[draggingIndex].attachToPizza( {pizzaCenter.x + cosf(angle)*(pizzaRadius - toppingRadius), pizzaCenter.y + sinf(angle)*(pizzaRadius - toppingRadius)});
            }else{
                toppings[draggingIndex].setInactive();
            }

            draggingIndex = -1;
        }

        // ===== DRAWING =====


        // DONE Button
        DrawRectangleRec(doneButton, pizzaFinished ? DARKGREEN : GREEN);
        DrawText("DONE", 140, 180, 20, WHITE);
        //cout<<pizzaCenter.x;
        // Pizza
        DrawCircleV(pizzaCenter, pizzaRadius, currentPizzaColor);
        DrawCircleLines(pizzaCenter.x, pizzaCenter.y, pizzaRadius, BROWN);
        (*PlayerPizza).draw();

        // ===== BASE TABLE =====
        //DrawText("Bases", 370, 420, 22, DARKGRAY);
        //DrawRectangle(250, 440, 300, 80, LIGHTGRAY);

        for (int i = 0; i < BASE_COUNT; i++)
        {
            //DrawCircleV(baseTablePos[i], 60, baseColors[i]);
            //Visual indication of clickable area ^

            DrawText(baseNames[i],
                baseTablePos[i].x - MeasureText(baseNames[i], 14)/2,
                baseTablePos[i].y + 25,
                14,
                BLACK);
        }

        //! ===== TOPPING TABLE =====
        //DrawText(("x is " + to_string(GetMouseX())).c_str(), 360, 400, 22, DARKGRAY);
        //DrawText(("y is " + to_string(GetMouseY())).c_str(), 360, 435, 22, DARKGRAY);

        //DrawRectangle(150, 530, 500, 130, LIGHTGRAY);



        for (int i = 0; i < TOPPING_COUNT; i++)
        {
            //DrawCircleV(tablePos[i], 40, toppingColors[i]);
            //^visual indicator of clickable space for toppings

            populateToppingBowls();

            int fontSize = 11;

            DrawText(toppingNames[i],
                tablePos[i].x - MeasureText(toppingNames[i], fontSize)/2,
                tablePos[i].y + 35,
                fontSize,
                BLACK);
        }




        // Active toppings
        for (int i = 0; i < toppings.size(); i++)
{
            if (toppings[i].isActive()){
                toppings[i].draw();
            }
        }

        // Remove inactive toppings
        for (int i = static_cast<int>(toppings.size()) - 1; i >= 0; --i) {
            if (!toppings[i].isActive()) {
                toppings.erase(toppings.begin() + i);
            }
        }




        // ===== COMPLETION BOX =====
        if (pizzaFinished)
        {
            if (PlayerPizza != &testPizza) {
                (*PlayerPizza).setToppings(toppings);
                (*PlayerPizza).setState(Cooking);
                currentState = PizzaCook;
            }
            pizzaFinished = false;
            toppings.clear();
            
        }
    
}
        // "Finger",
        // "Glowing Mushroom",
        // "Human Pepperoni",
        // "Mouse Brain",
        // "Pineapple",
        // "Tooth Pepper"
#define bowlOffset 15
#define centerCorrection -23

void populateToppingBowls(){

    Texture2D toppingsTextures[6] = {texturemanager.Finger, texturemanager.GlowingMushroom, texturemanager.HumanPepperoni, texturemanager.MouseBrain, texturemanager.Pineapple, texturemanager.ToothPepper};

    for (int z = 0; z < 6; z++){
        for (int i = 0; i < 5; i++){
            if (i == 1) DrawTextureEx(toppingsTextures[z], (Vector2){tablePos[z].x + centerCorrection + bowlOffset, tablePos[z].y + bowlOffset + centerCorrection}, 0, 5.0f, (Color){static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),(255)});
            if (i == 2) DrawTextureEx(toppingsTextures[z], (Vector2){tablePos[z].x + centerCorrection + bowlOffset, tablePos[z].y - bowlOffset + centerCorrection}, 0, 5.0f, (Color){static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),(255)});
            if (i == 3) DrawTextureEx(toppingsTextures[z], (Vector2){tablePos[z].x + centerCorrection- bowlOffset, tablePos[z].y - bowlOffset + centerCorrection}, 0, 5.0f, (Color){static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),(255)});
            if (i == 4) DrawTextureEx(toppingsTextures[z], (Vector2){tablePos[z].x + centerCorrection- bowlOffset, tablePos[z].y + bowlOffset + centerCorrection}, 0, 5.0f, (Color){static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),(255)});
            if (i == 0) DrawTextureEx(toppingsTextures[z], (Vector2){tablePos[z].x + centerCorrection, tablePos[z].y + centerCorrection}, 0, 5.0f, (Color){static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),static_cast<unsigned char>(255-i * 3),(255)});

        }
    }

    
}