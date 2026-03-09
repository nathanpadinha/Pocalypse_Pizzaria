#include "Pizza.hpp"

Pizza::Pizza(){
    cookTime = NULL;
    numCuts = NULL;
    pizzaBase = NULL;
    //!toppings is a vector and cant be set to null
}
Pizza::getCookTime(){
    return cookTime;
}
Pizza::getNumCuts(){
    return numCuts;
}
Pizza::getPizzaBase(){
    return pizzaBase;
}
Pizza::getToppings(){
    return toppings;
}
Pizza::setCookTime(int time){
    cookTime = time

}
Pizza::setNumCuts(int cuts){
    numCuts = cuts;

}
Pizza::setPizzaBase(string base){
    pizzaBase = base;

}
Pizza::setToppings(vector <Topping> topping2){
    topping = topping2

}