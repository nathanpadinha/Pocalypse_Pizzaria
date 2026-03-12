#pragma once
#include "Customer.hpp"





Customer::Customer(){

    this->isActive = false;
    this->scale = 1;
    this->isOrdering = true;
    this->x = 800;
    this->y = 500;
    this->delay = 0;

}



void Customer::Update(TicketRack* ticketRack, int customerNumber){
    //update Y based on customer number
    y = 500 + customerNumber * 10;

    //only if customer is active, update is called regardless unfortunately
    if (isActive){
        //ordering behavior
        if (isOrdering){
            Rectangle srcRec = Rectangle{0.0f, 0.0f, static_cast<float>(texturemanager.ZombieGuy.width), static_cast<float>(texturemanager.ZombieGuy.height)};
            Rectangle destRec = Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(texturemanager.ZombieGuy.width) * scale, static_cast<float>(texturemanager.ZombieGuy.height) * scale};
            Vector2 origin = Vector2{static_cast<float>(texturemanager.ZombieGuy.width) * scale / 2.0f, static_cast<float>(texturemanager.ZombieGuy.height) * scale / 2.0f};
            DrawTexturePro(texturemanager.ZombieGuy, srcRec, destRec, origin, 0.0f, WHITE);
            if (scale < 25) scale += 0.4f;
            else if (scale >= 25){
                if (delay == 120) {
                    isOrdering = false;
                    (*ticketRack).AddOrder(Order(1, (*ticketRack).GetOrderQuantity()));
                }
                else delay++;

                return;
            }
        }
        //when done ordering, go to the left and wait
        else{
            if (!(x <= 250 - customerNumber * 10)){ //offset based on customer number so that customers don't line up perfectly
                x -= 2;
            }
            Rectangle srcRec = Rectangle{0.0f, 0.0f, static_cast<float>(texturemanager.ZombieGuy.width), static_cast<float>(texturemanager.ZombieGuy.height)};
            Rectangle destRec = Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(texturemanager.ZombieGuy.width) * scale, static_cast<float>(texturemanager.ZombieGuy.height) * scale};
            Vector2 origin = Vector2{static_cast<float>(texturemanager.ZombieGuy.width) * scale / 2.0f, static_cast<float>(texturemanager.ZombieGuy.height) * scale / 2.0f};
            DrawTexturePro(texturemanager.ZombieGuy, srcRec, destRec, origin, 0.0f, WHITE);
            return;
        }
    }


}