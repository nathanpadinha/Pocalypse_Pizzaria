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
      this->SubmitPizza = nullptr;
      pizzasDone[0] = false;
      pizzasDone[1] = false;
      pizzasDone[2] = false;
      pizzasDone[3] = false;
      chompMode = false;
      chomped = false;
      pizzaSubmited = false;
      for (int i = 0; i < 4; i++) {
         pizzaScored[i] = false;
      }
      
   }


   void OrderTake::Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day, vector<Pizza> &PizzaList, vector<Customer> &listOfCustomers, int &points, gameState currentState){
      pizzaSubmited = false;
      SubmitPizza = nullptr;
      for(int i = 0; i < PizzaList.size(); i++){
         if (PizzaList[i].getState() != Submitting) {
            pizzaScored[i] = false;
         }
         if (PizzaList[i].getState() == Submitting){
            SubmitPizza = &PizzaList[i];//*Gets copy of Pizza object
            currentOrder = ticketRack->GetOrder(i);//*Gets coppy of Order onject
            coustmerID = currentOrder.GetCustomerID();//* Uses order to get coustmerID
            currentCustomer = Customer::getCustomerByID(listOfCustomers, coustmerID);//*Get copy of Coustmer Object by ID
            if (!pizzaScored[i]) {
               calculatePoints(currentOrder, currentCustomer, *SubmitPizza, points);
               pizzaScored[i] = true;
            }
            pizzaSubmited = true;
            break;
         }
      }
      if( SubmitPizza != nullptr){
         (*SubmitPizza).setPosition((Vector2){500, 350});
         //if about to be chomped, draw pizza. If no chomping is happening, draw pizza.
         if (currentState == OrderTaking) if ((!chomped && chompMode) || !chompMode) (*SubmitPizza).draw();
      }
         //manual customer creation
         if(IsKeyPressed(KEY_PERIOD) && iterator <= 3){
            listOfCustomers[iterator].setActive();
            iterator++;
         }

         //automatic customer
         if((dayTimeFrame % 1800) == 0 && iterator <= 3){
            if(customerScheduleDifficulty[day][iterator] != 0){
               listOfCustomers[iterator].setActive();
               listOfCustomers[iterator].setDifficulty( customerScheduleDifficulty[day][iterator] ) ;
               iterator++;
            }
         }


   for (int i = 3; i >= 0; i--){
      listOfCustomers[i].Update(ticketRack, i, dayTimeFrame, currentState); 
   }

   //turn in pizza behavior
   if (pizzasDone[0] || pizzasDone[1] || pizzasDone[2] || pizzasDone[3]){
      if (turnInIterator == 0){
        scoreTexture = texturemanager.Letter[calculatePoints(currentOrder, currentCustomer, *SubmitPizza) > 70 ? 0 : calculatePoints(currentOrder, currentCustomer, *SubmitPizza) > 62 ? 1 : calculatePoints(currentOrder, currentCustomer, *SubmitPizza) > 52 ? 2 : calculatePoints(currentOrder, currentCustomer, *SubmitPizza) > 40 ? 3 : calculatePoints(currentOrder, currentCustomer, *SubmitPizza) > 32 ? 4 : 5];
         if (rand() % 3 == 0){
            chompMode = true; 
         }
      }
      if(turnInIterator < 180){
         turnInIterator++;
         DrawTextureEx(scoreTexture, (Vector2){300.0f, 150.0f}, 0.0f, 30.0f, WHITE);
         if (chompMode){
            if (currentState == OrderTaking) {
               DrawTextureEx(texturemanager.ChompCounter[(int)floor(turnInIterator/9)], (Vector2){0, 0}, 0, 25.0f, WHITE);
            }
         }
         
      }
      if (turnInIterator == 99){
         chomped = true;
      }
      if (turnInIterator >= 180){
         for (int i = 0; i < 4; i++){
            if(pizzasDone[i]){
               listOfCustomers[i].setInactive();
               (*SubmitPizza).setState(Done);
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
      if (pizza.isActive()){
         int cookTimeScore, toppingsScore, sliceScore = 100;
         double happinessMaltiplyer;
         int score;

         cookTimeScore = ( getPointsForCookTime(order, pizza) * 0.3 ) ;

         toppingsScore = ( getPointsForToppings(order, pizza) * 0.4 ) ;

         sliceScore -= (int) (abs(order.GetSliceAmount() - pizza.getNumCuts()) * 20);
         sliceScore = sliceScore * 0.2 + 0.05;
         if (sliceScore <= 0) sliceScore = 0;

         happinessMaltiplyer = getHappyMaltiplyer(order, customer) + 0.08;
         score = (int)round((toppingsScore + cookTimeScore + sliceScore) * happinessMaltiplyer);

      //Uses pointer to calculate and update score in main
         userScore += score;

      } else {
      }
      
   }

//Points for cook time, 100 points for perfect, lose points for burnt or raw, less points for slight over / under cook 
   int OrderTake::getPointsForCookTime(Order order, Pizza pizza){
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
      return points;
   }
//Logic is complex, so split into 2 functions
   int OrderTake::compareToppings(Order order, Pizza pizza){
      int points = 0;
      vector <Topping> pizzaToppings = pizza.toppingsList;;

      int pineapple = 0, finger = 0, mbrains = 0, pepper = 0, peroni = 0, mushroom = 0;
      int pineappleDiff = 0, fingerDiff = 0, mbrainsDiff = 0, pepperDiff = 0, peroniDiff = 0, mushroomDiff = 0, totalDiff = 0;
      string name;

    for (auto& t : pizzaToppings) {  // not const
        if (t.getName() == "Pineapple") {
            ++pineapple;
        }
        if (t.getName() == "Fingers") {
            ++finger;
        }
         if (t.getName() == "Glowing Mushrooms") {
               ++mushroom;
         }
         if (t.getName() == "Mouse Brain") {
               ++mbrains;
         }
         if (t.getName() == "Human Pepperoni") {
               ++peroni;
         }
         if (t.getName() == "Tooth Pepper") {
               ++pepper;
         }
    }
   //order has an array of toppingID[3]
   //ord has an array of amounts of each toppingAmount[3]
           



   for (int i = 0; i < 3; i++){
      name = order.TranslateTopping(order.GetToppingID(i));
      
      if (name == "Pineapple"){
         pineappleDiff = abs(order.toppingAmount[i] - pineapple);
      }
      else if (name == "Fingers"){
         fingerDiff = abs(order.toppingAmount[i] - finger);
      }
      else if (name == "Glowing Mushrooms"){
         mushroomDiff = abs(order.toppingAmount[i] - mushroom);
      }
      else if (name == "Mouse Brain"){
         mbrainsDiff = abs(order.toppingAmount[i] - mbrains);
      }
      else if (name == "Human Pepperoni"){
         peroniDiff = abs(order.toppingAmount[i] - peroni);
      }
      else if (name == "Tooth Pepper"){
         pepperDiff = abs(order.toppingAmount[i] - pepper);
      }


      totalDiff = pineappleDiff + fingerDiff + mushroomDiff + mbrainsDiff + peroniDiff + pepperDiff;
      
   }
   if (totalDiff == 0){
      points += 100;
   }else if (totalDiff <= 2){
      points +=75;
   }else if (totalDiff <= 4){
      points += 50;
   }else if (totalDiff <= 6){
      points += 25;
   }else{
      points += 0;
   }
   return points;
   }


   int OrderTake::compareSauce(Order order, Pizza pizza){
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
   int OrderTake::getPointsForToppings(Order order, Pizza pizza){
      int points = 0;
      //60% of points for toppings, 40% for sauce 100 points max
      points += ( compareToppings(order, pizza) * .6) ;
      points += ( compareSauce(order, pizza) * .4) ;
      return points;
   }
//Get happieness maltiplyer
   double OrderTake::getHappyMaltiplyer(Order order, Customer customer){
      double maltiplyer = 1.00;
      maltiplyer -= (float)customer.getWaitTime() / (6000.00 + (float)(order.GetCookTime() * 60));
      if (maltiplyer < 0.1) maltiplyer = 0.1; // preserve some score even after a long wait
      return maltiplyer; 
   }

//overloading this for internal use
   int OrderTake::calculatePoints(Order order, Customer customer, Pizza pizza){
      if (pizza.isActive()){
         int cookTimeScore, toppingsScore, sliceScore = 100;
         double happinessMaltiplyer;
         int score;

         cookTimeScore = ( getPointsForCookTime(order, pizza) * 0.3 ) ;

         toppingsScore = ( getPointsForToppings(order, pizza) * 0.4 ) ;

         sliceScore -= (int) (abs(order.GetSliceAmount() - pizza.getNumCuts()) * 20);
         sliceScore = sliceScore * 0.2;
         if (sliceScore <= 0) sliceScore = 0;
         
         happinessMaltiplyer = getHappyMaltiplyer(order, customer);

         return score = (int)round((toppingsScore + cookTimeScore + sliceScore) * happinessMaltiplyer);

      } else {
      }
      
   }