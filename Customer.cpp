#pragma once
#include "Customer.hpp"

#define CUSTOMER_COLOR_OFFSET 7



Customer::Customer(){

    this->isActive = false;
    this->scale = 1;
    this->isOrdering = true;
    this->x = 800;
    this->y = 490; 
    this->delay = 0;
    this->difficulty = 1;
    this->customerId = 0;
    this->type = Unassigned;

}



void Customer::Update(TicketRack* ticketRack, int customerNumber, int dayTimeFrame){
    //update Y based on customer number

    if (type == Unassigned){
        type = customerType(rand() % 3 + 1); //random customer type
    }

    y = 490 - customerNumber * 10;
    customerId = customerNumber + 1;

    //only if customer is active, update is called regardless unfortunately
    if (isActive){
        //ordering behavior
        if (isOrdering){

            Rectangle srcRec = Rectangle{0.0f, 0.0f, static_cast<float>(texturemanager.ZombieGuy[0].width), static_cast<float>(texturemanager.ZombieGuy[0].height)};
            Rectangle destRec = Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(texturemanager.ZombieGuy[0].width) * scale, static_cast<float>(texturemanager.ZombieGuy[0].height) * scale};
            Vector2 origin = Vector2{static_cast<float>(texturemanager.ZombieGuy[0].width) * scale / 2.0f, static_cast<float>(texturemanager.ZombieGuy[0].height) * scale / 2.0f};
            // Temporarily changing color based on customerNumber, to diffrentiate the customers a tad. 
            //DrawTexturePro(texturemanager.ZombieGuy[dayTimeFrame % 60 <= 30 ? 0 : 1], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerNumber * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerNumber * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerNumber * CUSTOMER_COLOR_OFFSET), 255 });

            //Grows in size and wiggles to simualate walking up to the counter, then stops and does order, then goes to left with more wiggles
            if (scale < 25){
                scale += 0.4f;
                Customer::drawCustomer(dayTimeFrame, true);
            } 
            else if (scale >= 25){
                Customer::drawCustomer(dayTimeFrame, false);

                if (delay == 0){
                    delay++;
                    //add order
                    //(*ticketRack).AddOrder(Order(difficulty, (*ticketRack).GetOrderQuantity(), customerId));
                    this->banana = Order(difficulty, customerNumber, customerId);
                    //(*ticketRack).setTicketAsBoolActive(customerId, false);
                    
                }
                else if (delay == 240) {
                    isOrdering = false;
                    //Order banana = Order(difficulty, customerNumber, customerNumber);
                    (*ticketRack).AddOrder(banana);
                   // (*ticketRack).setTicketAsBoolActive(customerId, true);
                   //(*ticketRack).AddOrderDirect(banana, customerId);
                    
                }
                //speech bubble stuff
                else{
                    
                    
                    doSpeechBubble(delay);
                    
                    
                    delay++;


                } 

                
            }
        }
        //when done ordering, go to the left and wait
        else{
            if (!(x <= 250 - customerNumber * 20)){ //offset based on customer number so that customers don't line up perfectly
                x -= 2;
            }
            Customer::drawCustomer(dayTimeFrame, true);
            
            DrawText(("CustomerID: " + to_string(customerId)).c_str(), x-100, y-100, 20, BLACK);

        }
        
        return;

    }


}


/* DELETE THIS LATER
string TranslateTopping(int ToppingID);
string TranslateSauce(int SauceID);
Texture2D ToppingIDtoTexture(int ToppingID);



*/

void Customer::drawCustomer(int dayTimeFrame, bool animated){

    Rectangle srcRec = Rectangle{0.0f, 0.0f, static_cast<float>(texturemanager.ZombieGuy[0].width), static_cast<float>(texturemanager.ZombieGuy[0].height)};
    Rectangle destRec = Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(texturemanager.ZombieGuy[0].width) * scale, static_cast<float>(texturemanager.ZombieGuy[0].height) * scale};
    Vector2 origin = Vector2{static_cast<float>(texturemanager.ZombieGuy[0].width) * scale / 2.0f, static_cast<float>(texturemanager.ZombieGuy[0].height) * scale / 2.0f};

    switch (type)
    {
    case Zombie:
        if(animated){
            DrawTexturePro(texturemanager.ZombieGuy[dayTimeFrame % 60 <= 30 ? 0 : 1], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });

        }
        else{
            DrawTexturePro(texturemanager.ZombieGuy[0], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });
        }
        break;
    case Snowman:
        if(animated){
            DrawTexturePro(texturemanager.Snowman[dayTimeFrame % 120 <= 30 ? 0 : (dayTimeFrame % 120 <= 60 ? 1 : (dayTimeFrame % 120 <= 90 ? 2 : 3))], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });
        }
        else{
            DrawTexturePro(texturemanager.Snowman[0], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });
        }
        break;
    case Mantis:
        if(animated){
            DrawTexturePro(texturemanager.Mantis[dayTimeFrame % 60 <= 30 ? 0 : 1], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });
        }
        else{
            DrawTexturePro(texturemanager.Mantis[0], srcRec, destRec, origin, 0.0f, (Color){ (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), (unsigned char)(255 - customerId * CUSTOMER_COLOR_OFFSET), 255 });
        }
         break;
    
    default:
        break;
    }



}


void Customer::doSpeechBubble(int delay){

DrawTextureEx(texturemanager.SpeechBubble, (Vector2){ (float)(x - 340), (float)(y - 455) }, 0.0f, 12.5f, WHITE);

if ((banana.toppingID[1] == 0)){
    // do 1-topping behavior

    if(delay >= 0 && delay <= 60){
        // topping 1
        for (int i = 0; i < banana.toppingAmount[0]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[0]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[0]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
        
        
        }
    }
    else if(delay >60 && delay <= 120){
        // Sauce
        //DrawText(("Sauce: " + banana.TranslateSauce(banana.sauceID)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SauceRepresentations[banana.sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
    }
    else if(delay >120 && delay <= 180){
        DrawTextureEx(texturemanager.Timer[banana.cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
    }
    else if(delay >180 && delay <=240){
        //DrawText(("Slices: " + to_string(banana.sliceAmount)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SliceRepresentations[(banana.sliceAmount/2)-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
    }
}


else if (banana.toppingID[2] == 0){
    //do 2-topping behavior

    if(delay >= 0 && delay <= 48){


        for (int i = 0; i < banana.toppingAmount[0]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[0]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[0]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
        
        
        }
    }
    else if(delay >48 && delay <= 96){
        // topping 2
        for (int i = 0; i < banana.toppingAmount[1]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[1]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[1]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
            
            
        }
    }
    else if(delay >96 && delay <= 144){
        // Sauce
        //DrawText(("Sauce: " + banana.TranslateSauce(banana.sauceID)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SauceRepresentations[banana.sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);

    }
    else if(delay >144 && delay <= 192){
        //cook time
        DrawTextureEx(texturemanager.Timer[banana.cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
    }
    else if(delay >192 && delay <=240){
        //slices
        //DrawText(("Slices: " + to_string(banana.sliceAmount)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SliceRepresentations[(banana.sliceAmount/2)-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);

    }

}

else {
    //do 3-topping behavior
    if(delay >= 0 && delay <= 40){
        // topping 1
        for (int i = 0; i < banana.toppingAmount[0]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[0]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[0]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
        
        
        }
    }
    else if(delay >40 && delay <= 80){
        // topping 2
        for (int i = 0; i < banana.toppingAmount[1]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[1]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[1]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
        
        
        }
    }
    else if(delay >80 && delay <= 120){
        // topping 3
        for (int i = 0; i < banana.toppingAmount[2]; i++){

            DrawTextureEx(banana.ToppingIDtoTexture(banana.toppingID[2]), (Vector2){(float)x-140+(i*40)-(banana.toppingAmount[2]*20), (float)y-265}, 0.0f, 5.0f, WHITE);
            
        
        }
    }
    else if(delay >120 && delay <= 160){
        // Sauce
        //DrawText(("Sauce: " + banana.TranslateSauce(banana.sauceID)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SauceRepresentations[banana.sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);

    }
    else if(delay >160 && delay <= 200){
        //DrawText(("Cook Time: " + to_string(banana.cookTime) + "s").c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.Timer[banana.cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
    }
    else if(delay >200 && delay <=240){
        // slices
        //DrawText(("Slices: " + to_string(banana.sliceAmount)).c_str(), x-275, y-265, 20, BLACK);
        DrawTextureEx(texturemanager.SliceRepresentations[(banana.sliceAmount/2)-1], (Vector2){(float)x-170, (float)y-285}, 0.0f, 5.0f, WHITE);


    }

}



}

