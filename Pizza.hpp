#pragma once
#include "Constents.hpp"
#include "Topping.hpp"
#include <vector>
#include <algorithm>


struct sliceLine{
     Vector2 start;
     Vector2 end;
};


class Pizza{
    public:
          //Constructor
               Pizza();
          //Sause Accsesors
               void setSauceID(int newSauceID);
               int getSauceID();
          //Cut Accsesors
               void setNumCuts(int cuts);
               int getNumCuts();
          //Cook Time Accsesors
               void setCookTime(int time);
               int getCookTime();
          //Toppings Accsesors
               void setToppings(vector <Topping> newToppings);
               void getToppings(vector <Topping> &toppings);
          //Radius Accsesors
               void setRadius(float r);
               float getRadius();
          //Position Accsesors
               void setPosition(Vector2 p);
               Vector2 getPosition();
          //Active Accsesors
               void setActive(bool active);
               bool isActive();
          //Pizza State Accsesors
               void setState(pizzaState newState);
               pizzaState getState();
          //Adds a topping to toppings vector.
               void addTopping(Topping newTopping);
          //Draws Pizza
               void draw();
          //If clicked while cooking, go to cutting state. If cutting, go to submitting
               void checkIfClicked(); 
          //Getters for Topping Names and Amounts
               Color getBaseColor();    
               vector<int> getToppingAmounts();
               vector<string> getToppingNames();
               

               
               vector <Topping> toppingsList;
               vector <sliceLine> sliceLines;


     private:
          float baseRotation = 0.0f, baseScale = 20.0f, cheeseScale = 10.0f, radius;
          
          int sauceID, cookTime, numCuts, pizzaScore, currentScore;
          
          
          vector <int> toppingAmounts;
          vector <string> toppingNames;
          
          
          Vector2 basePosition, position;
          
          pizzaState state;
          
          bool active;
  
          
          

};