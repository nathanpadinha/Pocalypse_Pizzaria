#pragma once
#include "Constents.hpp"
#include "Topping.hpp"
#include <vector>

class Pizza{

    public:
       Pizza();

        void setBase(int newBase);
        void setNumCuts(int cuts);
        void setCookTime(int time);
        void addTopping(Topping newTopping);
        void setToppings(vector <Topping> newToppings);
        float getRadius();

        void draw();

        void setPosition(Vector2 p);
        Vector2 getPosition();
   private:

        int base;
        float baseRotation = 0.0f, baseScale = 20.0f, cheeseScale = 10.0f;
        Vector2 basePosition;
        
        vector <Topping> toppingsList;
        int cookTime;
        int numCuts;

        Vector2 position;
        float radius;

};