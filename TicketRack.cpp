#pragma once

#include "TicketRack.hpp"


//Public Mathods
    //Constructor
        TicketRack::TicketRack(gameState* state){
                this->currentState = state; 
            }

    //Accsessors
        int TicketRack::GetOrderQuantity(){
            return orders[0].GetActiveStatus() + orders[1].GetActiveStatus() + orders[2].GetActiveStatus() + orders[3].GetActiveStatus();
        }

        Order TicketRack::GetOrder(int index){
            return orders[index];
        }
        
    //Mutators
        void TicketRack::AddOrder(Order newOrder){
            if (!orders[0].GetActiveStatus()) {
                orders[0] = newOrder;
                return;
            } else if (!orders[1].GetActiveStatus()) {
                orders[1] = newOrder;
                return;
            }
            else if (!orders[2].GetActiveStatus()) {
                orders[2] = newOrder;
                return;
            }
            else if (!orders[3].GetActiveStatus()) {
                orders[3] = newOrder;
                return;
            }
            else return;
        }
    
    //Drawing
        void TicketRack::DisplayRack(){
            //DrawRectangle(0, 0, GetScreenWidth(), (GetScreenHeight()/12), GRAY); 
            DrawTextureEx(texturemanager.TicketRack, (Vector2){0, 0}, 0.0f, 25.0f, WHITE);
            
            //*Uncomment this vvv to see the buttons more clearly
            /*
            DrawRectangle(75, 50, 25, 25, RED); 
            ///This ^^^ is where the reset button is

            ///stage changebutton locations
            DrawCircle(1500, 100, 50, BLUE);
            DrawCircle(1375, 125, 50, ORANGE);
            DrawCircle(1250, 100, 50, YELLOW);
            DrawCircle(1125, 125, 50, GREEN);
            */
        }

    //Misc
        void TicketRack::Update(){
            for (int i = 0; i < 4; i++) {
                orders[i].Update();
            }
            //Reset ticket locations
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Rectangle{75, 50, 25, 25})) {
                TicketRack::ResetTicketLocations();
            }
            //Switch to order place
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Vector2{1125, 125}, 50.0f)){
                *currentState = OrderTaking;
            }
            //Switch to topping
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Vector2{1250, 100}, 50.0f)){
                *currentState = ToppingsAdd;
            }
            //Switch to cook
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Vector2{1375, 125}, 50.0f)){
                *currentState = PizzaCook;
            }
            //Switch to slice
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(Vector2{(float)GetMouseX(), (float)GetMouseY()}, Vector2{1500, 100}, 50.0f)){
                *currentState = PizzaCut;
            }




        }

//Private Methods
    //Misc
        void TicketRack::ResetTicketLocations(){
            for (int i = 0; i < 4; i++) {
                if (orders[i].GetActiveStatus()) {
                    orders[i].SetX( (150 + (i * (200)) ) );
                    orders[i].SetY( ( GetScreenHeight() / 13 ) );
                }
            }
        }

        // gets order quantity by adding up active orders. 

        //puts order in the first open slot in the TicketRack.