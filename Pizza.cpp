#include "Pizza.hpp"

Pizza::Pizza() {
    base = 0;
    cookTime = 0;
    numCuts = 0;
    position = {400.0f, 400.0f};
    radius = texturemanager.Cheese[0].width * cheeseScale / 2;
    active = true;
    state = Toppling;

}



//Setter Methods
void Pizza::setBase(int newBase){
     base = newBase;
}

void Pizza:: setNumCuts(int cuts){ numCuts = cuts; }

void Pizza:: setCookTime(int time){ cookTime = time; }

void Pizza:: addTopping(Topping newTopping){ 
    toppingsList.push_back(newTopping);
}
        
void Pizza::setToppings(vector <Topping> newToppings){ 
    toppingsList = newToppings;
    state = Cooking;
}

void Pizza::checkIfClicked(){
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), position, 120)) {
        if (state == Cutting){
            state = Submitting;
        }
        if (state == Cooking){
            state = Cutting;
        }

    }
}



void Pizza::setPosition(Vector2 p) { 
    position = p; 
    radius = texturemanager.Cheese[0].width * cheeseScale / 2;

}

Vector2 Pizza::getPosition(){ return position; }

float Pizza::getRadius(){
    return radius;
}

void Pizza::setActive(bool active){

    this->active = active;

}

void Pizza::draw() {
    
    if(active){ //only draw if pizza is active
        Vector2 cheesePos = {position.x - texturemanager.Cheese[0].width * cheeseScale / 2, position.y - texturemanager.Cheese[0].height * cheeseScale / 2};

        //draw state and cooktime for debug
        // DrawText(to_string(state).c_str(), cheesePos.x, cheesePos.y, 20, BLACK);
        // DrawText(to_string(cookTime).c_str(), cheesePos.x, cheesePos.y+60, 20, BLACK);

        if (base == 1){
            Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[0].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[0].height * baseScale / 2};
            DrawTextureEx(texturemanager.PizzaBase[0], cheesePos, baseRotation, cheeseScale, WHITE);
        }else if (base == 2){
            Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[1].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[1].height * baseScale / 2};
            DrawTextureEx(texturemanager.PizzaBase[1], cheesePos, baseRotation, cheeseScale, WHITE);
        }else if (base == 3){
            Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[2].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[2].height * baseScale / 2};
            DrawTextureEx(texturemanager.PizzaBase[2], cheesePos, baseRotation, cheeseScale, WHITE);
        }
        else{
            Vector2 drawPos = {position.x - texturemanager.SauceRepresentations[3].width * baseScale / 2, position.y - texturemanager.SauceRepresentations[2].height * baseScale / 2};
            DrawTextureEx(texturemanager.PizzaBase[3], cheesePos, baseRotation, cheeseScale, WHITE);
        }
        
        //Vector2 cheesePos = {position.x - texturemanager.Cheese[0].width * cheeseScale / 2, position.y - texturemanager.Cheese[0].height * cheeseScale / 2};
        DrawTextureEx(texturemanager.Cheese[cookTime], cheesePos, baseRotation, cheeseScale, WHITE);
        
        for (Topping &topping : toppingsList){
            topping.attachToPizza(position);
            topping.draw();
        }
        for(sliceLine slice: sliceLines){
            DrawLineEx((Vector2){slice.start.x + getPosition().x, slice.start.y + getPosition().y}, (Vector2){slice.end.x + getPosition().x, slice.end.y + getPosition().y}, 12, getBaseColor());

        }
        //draw crust bits
        for(sliceLine slice: sliceLines){
            DrawLineEx((Vector2){slice.start.x + getPosition().x, slice.start.y + getPosition().y}, (Vector2){slice.end.x + getPosition().x, slice.end.y + getPosition().y}, 5, (Color){168, 137, 83, 255});

        }

    }
}


Color Pizza::getBaseColor(){
    if (base == 1) return (Color){163, 22, 23, 255};
    if (base == 2) return (Color){114, 5, 6, 255};
    if (base == 3) return (Color){28, 209, 0, 255};
    else return (Color){168, 137, 83, 255};
}





