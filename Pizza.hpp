#pragma once

#include "Constents.hpp"
#include <vector>


class Pizza{

    public:
        void setBase(int newBase){
            base = newBase;
        }
        void addTopping(Topping newTopping){
            toppings.push_back(newTopping);
        }
        int setCookTime(int time){
            cookTime = time;
            return cookTime;
        }
        setNumCuts(int cuts){
            numCuts = cuts;
        }
        Pizza(){
            base = NULL;
            cookTime = NULL;
            numCuts = NULL;
        }
        

    private:
        int base;
        Texture2D baseTexture;
        
        vector <Topping> toppingsList;
        int cookTime;
        int numCuts;

}