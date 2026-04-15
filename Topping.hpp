#pragma once
#include "Constents.hpp"
#include <vector>

class Topping{
    public:

        Topping(const char* name, Vector2 pos, Vector2 center,bool act);
        
        const char* getName();
        
        Vector2 getPosition();
        void attachToPizza(Vector2 newCenter);
        void setDragPosition(Vector2 mousePos);

        
        void draw();

        void setActive();
        void setInactive();
        bool isActive();
    
    private:    
        const char* toppingName;
        Vector2 position, relitiveDistance, relitivePosition, center;
        bool active;
        float toppingScale;
        float toppingRotation;
        bool isDragging = false;
        
};