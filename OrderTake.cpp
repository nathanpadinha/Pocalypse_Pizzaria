#pragma once
#include "OrderTake.hpp"


#define SAUCE_TYPES 3
#define TOPPING_TYPES 6
#define MAX_TOPPINGS 6
#define MAX_SLICES 8

//Default constructor, sets all values
   OrderTake::OrderTake(){
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

   void OrderTake::Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day, int &userScore, Pizza PizzaList[]){
      if (PizzaList[0].state == Submitting) SubmitPizza = &PizzaList[0];
      else if (PizzaList[1].state == Submitting) SubmitPizza = &PizzaList[1];
      else if (PizzaList[2].state == Submitting) SubmitPizza = &PizzaList[2];
      else if (PizzaList[3].state == Submitting) SubmitPizza = &PizzaList[3];
      else (*SubmitPizza).setActive(false);
//Need to bring in an order and coustmer to calculate points
      calculatePoints(,  customer, *SubmitPizza, userScore)
      
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
   void OrderTake::calculatePoints(Order order, Customer customer, Pizza pizza, int &userScore){
      if ((*SubmitPizza).active = true){
         int cookTimeScore, toppingsScore, sliceScore = 100, happinessMaltiplyer;


         cookTimeScore = ( getPointsForCookTime(order, pizza) * 0.3 ) ;

         toppingsScore = ( getPointsForToppings(order, pizza) * 0.4 ) ;
         
         sliceScore -= (int) (abs(order.sliceAmount - (*SubmitPizza).numCuts) * 20);
         if (sliceScore <= 0) sliceScore == 0;
         
         happinessMaltiplyer = getHappyMaltiplyer(order, customer);
         
         score = (toppingsScore + cookTimeScore + sliceScore) * happinessMaltiplyer;

      //Uses pointer to calculate and update score in main
         userScore += score;

      }
      
   }



//Points for cook time, 100 points for perfect, lose points for burnt or raw, less points for slight over / under cook 
   int getPointsForCookTime(Order order, Pizza pizza){
      int points = 0;
      int cookTimeDifference = order.GetCookTime() - pizza.getCookTime();
      if (cookTimeDifference == 0){
         points += 100; //full points for perfect cook time
      }
      
      else if (cookTimeDifference > 5){
         points -= 50; //Burnt
      }else if (cookTimeDifference > 3){
         points -= 25; //Sightly burnt
      }else if (cookTimeDifference > 1){
         points += 50; //tosty
      }

      else if (cookTimeDifference <= 1){
         points += 75; //Little undercooked
      }else if (cookTimeDifference <= 3){
         points += 30; //undercooked
      }else if (cookTimeDifference <= 5){
         points += 10; //forgot to unfreze the DiGiorno
      }
      else{
         points += 0; //Ether so raw its basicly dough, or so burnt it would have been easer to cremate it
      }

   }
//Logic is complex, so split into 2 functions
   int compareToppings(Order order, Pizza pizza){
      int points = 0;
      vector <string> pizzaToppingNames = pizza.getToppingNames();
      vector <int> pizzaToppingAmounts = pizza.getToppingAmounts();

      for (int i = 0; i < 3; i++){
         if (order.GetTopping(i) != ""){//Catches null case
               int index = distance(pizzaToppingNames.begin(), find(pizzaToppingNames.begin(), pizzaToppingNames.end(), order.GetTopping(i)));
               if(index < pizzaToppingNames.size()){
                  if (pizzaToppingAmounts[index] >= order.GetToppingAmount(i)){
                     points += 100; //full points for having enough of the right toppings
                  }
                  else{
                     points += 50;//half points for having the right toppings but not enough
                  }
               }
               else{
                  points += 0;//no points for not having the right toppings
               }
         }
         return points;
      }
   }
   int compareSauce(Order order, Pizza pizza){
      int points = 0;
      if (order.GetSauseID() == pizza.getSauceID()){
         points += 100; //full points for having the right sauce
      }
      else{
         points += 0;//no points for not having the right sauce
      }
      return points;
   }
//Total points for toppings and sauce with weights applied
   int getPointsForToppings(Order order, Pizza pizza){
      int points = 0;
      //60% of points for toppings, 40% for sauce 100 points max
      points += ( compareToppings(order, pizza) * .6) ;
      points += ( compareSause(order, pizza) * .4) ;
      return points;
   }
//Total points for slices
//Get happieness maltiplyer
   double getHappyMaltiplyer(Order order, Customer customer){
      double maltiplyer = 1.00;
      maltiplyer -= (float)customer.waitTime / 6000.00;
      if (maltiplyer < 0) maltiplyer = 0; //if wait time is over 6000, customer is so mad they give no points
      return maltiplyer;
   }