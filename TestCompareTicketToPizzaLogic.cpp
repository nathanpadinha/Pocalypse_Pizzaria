#pragma once

//#include "TextureManager.hpp" is included in constents.hpp
#include "Constents.hpp"
#include "TicketRack.hpp"


//INCLUDE MINIGAMES
#include "OrderTake.hpp"
//#include "PizzaCookGame.hpp"
#include "AddToppingsGame.hpp"
#include "PizzaCutGame.hpp"
#include "PizzaCook.hpp"


#include "Pizza.hpp"


#define MAX_SEED_SIZE 9




int compareToppings(Order order, Pizza pizza){
    int points = 0;
    vector <string> pizzaToppingNames = pizza.getToppingNames();
    vector <int> pizzaToppingAmounts = pizza.getToppingAmounts();

    for (int i = 0; i < 3; i++){
        if (order.GetTopping(i) != ""){//Catches null case
            int index = distance(pizzaToppingNames.begin(), find(pizzaToppingNames.begin(), pizzaToppingNames.end(), order.GetTopping(i)));
            if(index < pizzaToppingNames.size()){
                if (pizzaToppingAmounts[index] >= order.GetToppingAmount(i)){
                    points += 100; //full points for having enough of the right toppings
                }
                else{
                    points += 50;//half points for having the right toppings but not enough
                }
            }
            else{
                points += 0;//no points for not having the right toppings
            }
        }
        return points;
    }
}

int compareSause(Order order, Pizza pizza){
    int points = 0;
    if (order.GetSauseID() == pizza.getSauceID()){
        points += 100; //full points for having the right sauce
    }
    else{
        points += 0;//no points for not having the right sauce
    }
    return points;
}

int pointsForToppings(Order order, Pizza pizza){
    int points = 0;
    //60% of points for toppings, 40% for sauce 100 points max
    points += ( compareToppings(order, pizza) * .6) ;
    points += ( compareSause(order, pizza) * .4) ;
    return points;
}

int pointsCookTime(Order order, Pizza pizza){
    int points = 0;
    int cookTimeDifference = order.GetCookTime() - pizza.getCookTime();
    if (cookTimeDifference == 0){
        points += 100; //full points for perfect cook time
    }
    
    else if (cookTimeDifference > 5){
        points -= 50; //Burnt
    }else if (cookTimeDifference > 3){
        points -= 25; //Sightly burnt
    }else if (cookTimeDifference > 1){
        points += 50; //tosty
    }

    else if (cookTimeDifference <= 1){
        points += 75; //Little undercooked
    }else if (cookTimeDifference <= 3){
        points += 30; //undercooked
    }else if (cookTimeDifference <= 5){
        points += 10; //forgot to unfreze the DiGiorno
    }
    else{
        points += 0; //Ether so raw its basicly dough, or so burnt it would have been easer to cremate it
    }

}

int pointsForCuts(Order order, Pizza pizza){
    
}

int finalPoints(Order order, Pizza pizza){
    int points = 0;
    points += ( pointsForToppings(order, pizza) * 0.35) ;
    points += ( pointsCookTime(order, pizza) * 0.6 );
    points += ( pointsForCuts(order, pizza) * 0.05 );
    
    //potentily use time since order to maltiply final score to insentivice faster orders
    //points *= (1 - npc happiness / 100)
    //NPC happiness based on time?
    
    return points;
}