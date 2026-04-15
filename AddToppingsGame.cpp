#pragma once
#include "AddToppingsGame.hpp"
#include <math.h>

#define TOPPING_COUNT 6
#define BASE_COUNT 3



vector <Topping> toppings;

//bad practice by me (elliot) but I need this out of the AddTopping() loop

    // Pizza in Center

    float pizzaRadius = 150.0f;

    // DONE BUTTON
    Rectangle doneButton = { 20, 20, 100, 40 };
    bool pizzaFinished = false;

    // ===== BASE TABLE =====
    Vector2 baseTablePos[BASE_COUNT] = {
        { 300, 460 },
        { 400, 460 },
        { 500, 460 }
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
        { 250, 560 }, { 400, 560 }, { 550, 560 },
        { 250, 620 }, { 400, 620 }, { 550, 620 }
    };

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




void playAddToppings(Pizza &PlayerPizza){



        //this variable needs to be done here
        Vector2 pizzaCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - 150 };
        PlayerPizza.setPosition(pizzaCenter);

        Vector2 mouse = GetMousePosition();

        // ===== CLICK LOGIC =====
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !pizzaFinished){
            if (CheckCollisionPointRec(mouse, doneButton)){
                pizzaFinished = true;
            }

            // Bases
            for (int i = 0; i < BASE_COUNT; i++){
                if (CheckCollisionPointCircle(mouse, baseTablePos[i], 18)){
                    currentPizzaColor = baseColors[i];
                    PlayerPizza.setBase(i+1);
                }
            }


            // Toppings
            for (int i = 0; i < TOPPING_COUNT; i++){
                if (CheckCollisionPointCircle(mouse, tablePos[i], 18)){
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
        DrawText("DONE", 40, 30, 20, WHITE);
        //cout<<pizzaCenter.x;
        // Pizza
        DrawCircleV(pizzaCenter, pizzaRadius, currentPizzaColor);
        DrawCircleLines(pizzaCenter.x, pizzaCenter.y, pizzaRadius, BROWN);
        PlayerPizza.draw();

        // ===== BASE TABLE =====
        DrawText("Bases", 370, 420, 22, DARKGRAY);
        DrawRectangle(250, 440, 300, 80, LIGHTGRAY);

        for (int i = 0; i < BASE_COUNT; i++)
        {
            DrawCircleV(baseTablePos[i], 18, baseColors[i]);

            DrawText(baseNames[i],
                baseTablePos[i].x - MeasureText(baseNames[i], 14)/2,
                baseTablePos[i].y + 25,
                14,
                BLACK);
        }

        // ===== TOPPING TABLE =====
        DrawText("Toppings", 360, 510, 22, DARKGRAY);
        DrawRectangle(150, 530, 500, 130, LIGHTGRAY);

        for (int i = 0; i < TOPPING_COUNT; i++)
        {
            DrawCircleV(tablePos[i], 18, toppingColors[i]);

            int fontSize = 11;

            DrawText(toppingNames[i],
                tablePos[i].x - MeasureText(toppingNames[i], fontSize)/2,
                tablePos[i].y + 25,
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
            const char *message = "PIZZA COMPLETE!";
            int fontSize = 30;

            int boxWidth = 420;
            int boxHeight = 150;

            int boxX = (GetScreenWidth() - boxWidth) / 2;
            int boxY = (GetScreenHeight() - boxHeight) / 2;

            DrawRectangle(boxX, boxY, boxWidth, boxHeight, DARKGREEN);
            DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, WHITE);

            int textWidth = MeasureText(message, fontSize);
            int textX = boxX + (boxWidth - textWidth) / 2;
            int textY = boxY + boxHeight / 2 - fontSize / 2;

            DrawText(message, textX, textY, fontSize, WHITE);

            PlayerPizza.setToppings(toppings);
            
        }
    
}