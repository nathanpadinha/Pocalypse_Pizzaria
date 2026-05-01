#pragma once
#include "Customer.hpp"

#define CUSTOMER_COLOR_OFFSET 7

//Public Methods
    //Constructor
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
        this->waitTime = 0;
    }
    //Accsessors
        //Customer Data
            int Customer::getID(){
                return customerId;
            }
            int Customer::getDifficulty(){
                return difficulty;
            }
            int Customer::getWaitTime(){
                return waitTime;
            }
            void Customer::setActive(){
                isActive = true;
            }
            void Customer::setInactive(){
                isActive = false;
            }
            void Customer::setDifficulty(int newDiff){
                difficulty = newDiff;
            }
            //Art Data
            float Customer::getScale(){
                return scale;
            }
            int Customer::getX(){
                return x;
            }
            int Customer::getY(){
                return y;
            }
    //Misc

        void Customer::Update(TicketRack* ticketRack, int customerNumber, int dayTimeFrame){
    //update Y based on customer number

    if (type == Unassigned){
        type = customerType(RNG.generate() % 3 + 1); //random customer type
    }

    if(isActive) waitTime++;

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
 
        //*Takes vector of coustmers and targetID and returns the coustmer with that ID
        Customer Customer::getCustomerByID(vector <Customer> listOfCustomers, int targetCustomerID){
            for(Customer currentCustomer : listOfCustomers){
                if ( currentCustomer.getID() == targetCustomerID ){
                    return currentCustomer;
                }
            }
            return Customer();
        }

//Private Methods
        //Drawing
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

int toppingID0 = banana.GetToppingID(0);
                int toppingID1 = banana.GetToppingID(1);
                int toppingID2 = banana.GetToppingID(2);
                int toppingAmount0 = banana.GetToppingAmount(0);
                int toppingAmount1 = banana.GetToppingAmount(1);
                int toppingAmount2 = banana.GetToppingAmount(2);
                int sauceID = banana.GetSauseID();
                int cookTime = banana.GetCookTime();
                int sliceAmount = banana.GetSliceAmount();

                if ((toppingID1 == 0)){
                    // do 1-topping behavior

                    if(delay >= 0 && delay <= 60){
                        // topping 1
                        for (int i = 0; i < toppingAmount0; i++){

                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID0), (Vector2){(float)x-140+(i*40)-(toppingAmount0*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >60 && delay <= 120){
                        // Sauce
                        DrawTextureEx(texturemanager.SauceRepresentations[sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >120 && delay <= 180){
                        DrawTextureEx(texturemanager.Timer[cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >180 && delay <=240){
                        DrawTextureEx(texturemanager.SliceRepresentations[(sliceAmount/2)-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                }

                else if (toppingID2 == 0){
                    //do 2-topping behavior

                    if(delay >= 0 && delay <= 48){
                        for (int i = 0; i < toppingAmount0; i++){
                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID0), (Vector2){(float)x-140+(i*40)-(toppingAmount0*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >48 && delay <= 96){
                        // topping 2
                        for (int i = 0; i < toppingAmount1; i++){
                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID1), (Vector2){(float)x-140+(i*40)-(toppingAmount1*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >96 && delay <= 144){
                        // Sauce
                        DrawTextureEx(texturemanager.SauceRepresentations[sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >144 && delay <= 192){
                        //cook time
                        DrawTextureEx(texturemanager.Timer[cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >192 && delay <=240){
                        //slices
                        DrawTextureEx(texturemanager.SliceRepresentations[(sliceAmount/2)-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                }

                else {
                    //do 3-topping behavior
                    if(delay >= 0 && delay <= 40){
                        // topping 1
                        for (int i = 0; i < toppingAmount0; i++){
                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID0), (Vector2){(float)x-140+(i*40)-(toppingAmount0*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >40 && delay <= 80){
                        // topping 2
                        for (int i = 0; i < toppingAmount1; i++){
                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID1), (Vector2){(float)x-140+(i*40)-(toppingAmount1*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >80 && delay <= 120){
                        // topping 3
                        for (int i = 0; i < toppingAmount2; i++){
                            DrawTextureEx(banana.ToppingIDtoTexture(toppingID2), (Vector2){(float)x-140+(i*40)-(toppingAmount2*20), (float)y-265}, 0.0f, 5.0f, WHITE);
                        }
                    }
                    else if(delay >120 && delay <= 160){
                        // Sauce
                        DrawTextureEx(texturemanager.SauceRepresentations[sauceID-1], (Vector2){(float)x-175, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >160 && delay <= 200){
                        DrawTextureEx(texturemanager.Timer[cookTime], (Vector2){(float)x-165, (float)y-280}, 0.0f, 5.0f, WHITE);
                    }
                    else if(delay >200 && delay <=240){
                        // slices
                        DrawTextureEx(texturemanager.SliceRepresentations[(sliceAmount/2)-1], (Vector2){(float)x-170, (float)y-285}, 0.0f, 5.0f, WHITE);
                    }
                }
            }

