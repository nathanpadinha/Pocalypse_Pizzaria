#pragma once
#include "Constents.hpp"
#include <vector>

class Topping{
    public:

        Topping(string name, Vector2 pos);
        string getName();
        Vector2 getPosition();
        void draw();

    private:    
        string toppingName;
        Vector2 position;
};