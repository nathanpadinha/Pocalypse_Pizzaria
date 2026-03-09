#pragma once
#include "OrderTake.hpp"


#define SAUCE_TYPES 3
#define TOPPING_TYPES 6
#define MAX_TOPPINGS 6
#define MAX_SLICES 8

// Constructor for Ordertake? Do we need this? Maybe not. 
OrderTake::OrderTake()
{
    this->iterator = 0;
}



void OrderTake::Update(TicketRack* ticketRack)
{
   if(IsKeyPressed(KEY_PERIOD)){
      customers[iterator].isActive = true;
      iterator++;
   }
   for (int i = 3; i >= 0; i--){
      customers[i].Update(ticketRack, i); 
   }
}
