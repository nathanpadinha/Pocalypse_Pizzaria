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

        //void draw();

        void setPosition(Vector2 p);
      
   private:

        int base;
        vector <Topping> toppingsList;
        int cookTime;
        int numCuts;

        Vector2 position;
        float radius;

};