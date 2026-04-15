#include "Pizza.hpp"

Pizza::Pizza() {
    base = 0;
    cookTime = 0;
    numCuts = 0;
    position = {400.0f, 400.0f};
    radius = texturemanager.Cheese[0].width * cheeseScale / 2;

}



//Setter Methods
void Pizza::setBase(int newBase){
     base = newBase;
}

void Pizza:: setNumCuts(int cuts){ numCuts = cuts; }

void Pizza:: setCookTime(int time){ cookTime = time; }

void Pizza:: addTopping(Topping newTopping){ toppingsList.push_back(newTopping);}
        
void Pizza::setToppings(vector <Topping> newToppings){ toppingsList = newToppings;}


void Pizza::setPosition(Vector2 p) { position = p; }

Vector2 Pizza::getPosition(){ return position; }

float Pizza::getRadius(){
    return radius;
}



void Pizza::draw() {
    
    if (base == 1){
        Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[0].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[0].height * baseScale / 2};
        DrawTextureEx(texturemanager.SauceRepresentations[0], drawPos, baseRotation, baseScale, WHITE);
    }else if (base == 2){
        Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[1].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[1].height * baseScale / 2};
        DrawTextureEx(texturemanager.SauceRepresentations[1], drawPos, baseRotation, baseScale, WHITE);
    }else if (base == 3){
        Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[2].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[2].height * baseScale / 2};
        DrawTextureEx(texturemanager.SauceRepresentations[2], drawPos, baseRotation, baseScale, WHITE);
    } 
    
    Vector2 cheesePos = {position.x - texturemanager.Cheese[0].width * cheeseScale / 2, position.y - texturemanager.Cheese[0].height * cheeseScale / 2};
    DrawTextureEx(texturemanager.Cheese[0], cheesePos, baseRotation, cheeseScale, WHITE);
    
    for (Topping &topping : toppingsList){
        topping.attachToPizza(position);
        topping.draw();
    }
    
}

