#include "Topping.hpp"

Topping::Topping(string name, Vector2 pos){
    toppingName = name;
    position = pos;
}

string Topping::getName(){ return toppingName; }

Vector2 Topping::getPosition(){ return position; }

void Topping::draw(){
    if (toppingName == "Finger"){
        DrawTextureV(texturemanager.Finger, position, WHITE);
    }
    else if (toppingName == "Glowing Mushroom"){
        DrawTextureV(texturemanager.GlowingMushroom, position, WHITE);
    }
    else if (toppingName == "Human Pepperoni"){
        DrawTextureV(texturemanager.HumanPepperoni, position, WHITE);
    }
    else if (toppingName == "Mouse Brain"){
        DrawTextureV(texturemanager.MouseBrain, position, WHITE);
    }
    else if (toppingName == "Pineapple"){
        DrawTextureV(texturemanager.Pineapple, position, WHITE);
    }
    else if (toppingName == "Tooth Pepper"){
        DrawTextureV(texturemanager.ToothPepper, position, WHITE);
    }
}