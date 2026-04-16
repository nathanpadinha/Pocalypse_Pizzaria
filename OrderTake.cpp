#pragma once
#include "OrderTake.hpp"


#define SAUCE_TYPES 3
#define TOPPING_TYPES 6
#define MAX_TOPPINGS 6
#define MAX_SLICES 8

// Constructor for Ordertake
OrderTake::OrderTake()
{
   this->iterator = 0;
   this->turnInIterator = 0;
   Pizza testPizza2; 
   this->SubmitPizza = &testPizza2;
   pizzasDone[0] = false;
   pizzasDone[1] = false;
   pizzasDone[2] = false;
   pizzasDone[3] = false;
   bool chompMode = false;
   bool chomped = false;
     
}




void OrderTake::Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day, Pizza PizzaList[])
{

   if (PizzaList[0].state == Submitting) {
      SubmitPizza = &PizzaList[0];
   }
   else if (PizzaList[1].state == Submitting) SubmitPizza = &PizzaList[1];
   else if (PizzaList[2].state == Submitting) SubmitPizza = &PizzaList[2];
   else if (PizzaList[3].state == Submitting) SubmitPizza = &PizzaList[3];
   else (*SubmitPizza).setActive(false);

   (*SubmitPizza).setPosition((Vector2){500, 350});
   //if about to be chomped, draw pizza. If no chomping is happening, draw pizza.
   if ((!chomped && chompMode) || !chompMode) (*SubmitPizza).draw();

   //manual customer creation
   if(IsKeyPressed(KEY_PERIOD) && iterator <= 4){
      customers[iterator].isActive = true;
      iterator++;
   }

   //automatic customer
   if((dayTimeFrame % 1800) == 0 && iterator <= 4){
      if(customerScheduleDifficulty[day][iterator] != 0){
         customers[iterator].isActive = true;
         customers[iterator].difficulty = customerScheduleDifficulty[day][iterator];
         iterator++;
      }
   }


   for (int i = 3; i >= 0; i--){
      customers[i].Update(ticketRack, i, dayTimeFrame); 
   }

   //turn in pizza behavior
   if (pizzasDone[0] || pizzasDone[1] || pizzasDone[2] || pizzasDone[3]){
      if (turnInIterator == 0){
         if (rand() % 3 == 0){
            chompMode = true; 
         }
      }
      if(turnInIterator < 180){
         turnInIterator++;
         if (chompMode){
            DrawTextureEx(texturemanager.ChompCounter[(int)floor(turnInIterator/9)], (Vector2){0, 0}, 0, 25.0f, WHITE);
         }
         
      }
      if (turnInIterator == 99){
         chomped = true;
      }
      if (turnInIterator >= 180){
         for (int i = 0; i < 4; i++){
            if(pizzasDone[i]){
               customers[i].isActive = false;
               (*SubmitPizza).state = Done;
               pizzasDone[i] = false;
               turnInIterator = 0;
               chompMode = false;
               chomped = false;
            }
         }
      }
   }




}



//No idea how/where to implement this easily, unfortunately.

void OrderTake::calculatePercentScore(Order order, Customer customer){
   if ((*SubmitPizza).active = true){
      int cookTimeScore = 100;
      int toppingsScore = 100;
      int sliceScore = 100;
      int happyScore = 100;

      cookTimeScore -= (int) (abs(order.cookTime - (*SubmitPizza).cookTime) * 12.5);
      if (cookTimeScore <= 0) cookTimeScore == 0;

      sliceScore -= (int) (abs(order.sliceAmount - (*SubmitPizza).numCuts) * 20);
      if (sliceScore <= 0) sliceScore == 0;

      happyScore -= (int) (abs((6000 + order.cookTime * 60 -  customer.waitTime)/(6000)));
      if (happyScore <= 0) happyScore == 0;
      
      //currently just checks number of toppings, not correct toppings, for now
      toppingsScore -= (int) (abs(order.toppingAmount[0] + order.toppingAmount[1] + order.toppingAmount[2] - (int)(*SubmitPizza).toppingsList.size()));

      (*SubmitPizza).currentScore = (int)((cookTimeScore * 0.3 + sliceScore * 0.1 + happyScore * 0.2 + toppingsScore * 0.4) * 100);
      return;
   }
}


