#include "Topping.hpp"

Topping::Topping(const char* name, Vector2 pos, Vector2 cent,bool act){
    toppingName = name;
    position = pos;
    center = cent;
    active = act;
    toppingScale = 3.0f;
    toppingRotation = 0.0f;
}

const char* Topping::getName(){ return toppingName; }



Vector2 Topping::getPosition(){ return position; }

void Topping::attachToPizza(Vector2 newCenter){
    isDragging = false;     
    relitiveDistance = {position.x - center.x , position.y - center.y};
    relitivePosition = {relitiveDistance.x + newCenter.x, relitiveDistance.y + newCenter.y};

}
void Topping::setDragPosition(Vector2 mousePos){
    isDragging = true;
    position = mousePos; 
    
}

void Topping::setActive(){active = true; }
void Topping::setInactive(){active = false;}
bool Topping::isActive(){return active;}

void Topping::draw(){
    toppingScale = 5;
    toppingRotation = 0;
    Vector2 pos;

    if(isDragging){
        pos = position; 
    }else{
        pos = relitivePosition; 
    }
    
    if (toppingName == "Finger"){
        DrawTextureEx(texturemanager.Finger, pos, toppingRotation, toppingScale, WHITE);
    }
    else if (toppingName == "Glowing Mushroom"){
        DrawTextureEx(texturemanager.GlowingMushroom, pos, toppingRotation, toppingScale, WHITE);
    }
    else if (toppingName == "Human Pepperoni"){
        DrawTextureEx(texturemanager.HumanPepperoni, pos, toppingRotation, toppingScale, WHITE);
    }
    else if (toppingName == "Mouse Brain"){
        DrawTextureEx(texturemanager.MouseBrain, pos, toppingRotation, toppingScale, WHITE);
    }
    else if (toppingName == "Pineapple"){
        DrawTextureEx(texturemanager.Pineapple, pos, toppingRotation, toppingScale, WHITE);
    }
    else if (toppingName == "Tooth Pepper"){
        DrawTextureEx(texturemanager.ToothPepper, pos, toppingRotation, toppingScale, WHITE);
    }
}