#include "Ticket.hpp"

Ticket::Ticket(){/*TO DO USE ORDER Generation code to make ticket*/
  
}
Ticket::getCookTime(){
    return cookTime;
}
Ticket::getNumCuts(){
    return numCuts;
}
Ticket::getPizzaBase(){
    return pizzaBase;
}
Ticket::getToppings(){
    return toppings;
}


Ticket::setCookTime(int time){
    cookTime = time

}
Ticket::setNumCuts(int cuts){
    numCuts = cuts;

}
Ticket::setPizzaBase(string base){
    pizzaBase = base;

}
Ticket::setToppings(vector <string> topping2){
    topping = topping2

}