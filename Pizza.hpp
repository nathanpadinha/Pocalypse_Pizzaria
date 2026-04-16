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

        void setActive(bool active);

        void checkIfClicked(); //if clicked while cooking, go to cutting state. If cutting, go to submitting
        pizzaState state;
        int cookTime;
        int numCuts;
        int pizzaScore;
        vector <Topping> toppingsList;
        bool active;   
        int currentScore;



   private:

        int base;
        float baseRotation = 0.0f, baseScale = 20.0f, cheeseScale = 10.0f;
        Vector2 basePosition;
        



        Vector2 position;
        float radius;

};