#include "Pizza.hpp"

Pizza::Pizza() {
    sauceID = 0;
    cookTime = 0;
    numCuts = 0;
    position = {400.0f, 400.0f};
    radius = texturemanager.Cheese[0].width * cheeseScale / 2;
    active = true;
    state = Toppling;

}

//Sause Accsesors
    void Pizza::setSauceID(int newSauceID){
        sauceID = newSauceID;
    }
    int Pizza::getSauceID(){
        return sauceID;
    }
//Cut Accsesors
    void Pizza::setNumCuts(int cuts){
        numCuts = cuts;
    }
    int Pizza::getNumCuts(){
        return numCuts;
    }
//Cook Time Accsesors
    void Pizza::setCookTime(int time){
        cookTime = time;
    }
    int Pizza::getCookTime(){
        return cookTime;
    }
//Toppings Accsesors
    void Pizza::setToppings(vector <Topping> newToppings){
        toppingsList = newToppings;
    }
    void Pizza::getToppings(vector <Topping> &toppings){
        toppings = toppingsList;
    }
//Radius Accsesors
    void Pizza::setRadius(float r){
        radius = r;
    }
    float Pizza::getRadius(){
        return radius;
    }
//Position Accsesors
    void Pizza::setPosition(Vector2 p){
        position = p;
    }
    Vector2 Pizza::getPosition(){
        return position;
    }
//Active Accsesors
    void Pizza::setActive(bool active){
        this->active = active;
    }
    bool Pizza::isActive(){
        return active;
    }
//Pizza State Accsesors
    void Pizza::setState(pizzaState newState){
        state = newState;
    }
    pizzaState Pizza::getState(){
        return state;
    }
    vector<int> Pizza::getToppingAmounts(){
        return toppingAmounts;
    }
    vector<string> Pizza::getToppingNames(){
        return toppingNames;
    }








void Pizza::addTopping(Topping newTopping){
    toppingsList.push_back(newTopping);
    auto i = find(toppingNames.begin(), toppingNames.end(), newTopping.getName());
    if (i != toppingNames.end()) {
        int index = distance(toppingNames.begin(), i);
        toppingAmounts[index]++;
    }
    else {
        toppingNames.push_back(newTopping.getName());
        toppingAmounts.push_back(1);
    }
}

void Pizza::draw() {
    
    if(active){ //only draw if pizza is active
        Vector2 cheesePos = {position.x - texturemanager.Cheese[0].width * cheeseScale / 2, position.y - texturemanager.Cheese[0].height * cheeseScale / 2};

        //draw state and cooktime for debug
        // DrawText(to_string(state).c_str(), cheesePos.x, cheesePos.y, 20, BLACK);
        // DrawText(to_string(cookTime).c_str(), cheesePos.x, cheesePos.y+60, 20, BLACK);

        if (sauceID == 1){
            DrawTextureEx(texturemanager.PizzaBase[1], cheesePos, baseRotation, cheeseScale, WHITE); // Blood
        }else if (sauceID == 2){
            DrawTextureEx(texturemanager.PizzaBase[0], cheesePos, baseRotation, cheeseScale, WHITE); // Tomato Sauce
        }else if (sauceID == 3){
            DrawTextureEx(texturemanager.PizzaBase[2], cheesePos, baseRotation, cheeseScale, WHITE); // Radioactive Sludge
        }
        else{
            DrawTextureEx(texturemanager.PizzaBase[3], cheesePos, baseRotation, cheeseScale, WHITE); // No sauce
        }
        
        //Vector2 cheesePos = {position.x - texturemanager.Cheese[0].width * cheeseScale / 2, position.y - texturemanager.Cheese[0].height * cheeseScale / 2};
        DrawTextureEx(texturemanager.Cheese[cookTime], cheesePos, baseRotation, cheeseScale, WHITE);
        
        for (Topping &topping : toppingsList){
            topping.attachToPizza(position);
            topping.draw();
        }
    }
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