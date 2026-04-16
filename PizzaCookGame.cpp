#include "PizzaCookGame.hpp"



int numPizzas = 1;
int cookTime;
    

CookingStage cookingStage;
 //!THIS IS ALL DEPCRECATED (I think)
 //!THIS IS ALL DEPCRECATED 
 //!THIS IS ALL DEPCRECATED
 //!THIS IS ALL DEPCRECATED


Vector2 findPizzaCenter(int pizzaNum){
    // Rectangle stove = cookingStage.getStoveArea();
    Vector2 pizzaCenter;

    if (pizzaNum == 1){
        pizzaCenter == (Vector2){500, 500};
    }
    else if (pizzaNum == 2){
        pizzaCenter == (Vector2){800, 500};

    }
    else if (pizzaNum == 3){
        pizzaCenter == (Vector2){500, 800};

    }
    else if (pizzaNum > 4){
        pizzaCenter == (Vector2){800, 800};

    }

    // float temp;
    // for( int i = 0; i < numPizzas -1 ; i++ ){
    //     if(numPizzas == 1){break;}
    //     temp = pizzaCenter.x;
    //     pizzaCenter.x = -(pizzaCenter.y);
    //     pizzaCenter.y = temp;
    // }


    return pizzaCenter;
}


void playPizzaCook(Pizza PizzaList[]){
    
    float dt = GetFrameTime();

    bool OVERCHARGE;

    cookingStage.update(dt);//Updates object
    cookTime = (int) cookingStage.getCookTime(); //Casts to int and updates var

    // Do pizza cooking behavior

    cookingStage.draw();

    /**
     * Get stove position and center the pizza on it
     * * This allows the pizza to always appear on the stove
     */
    Rectangle stove = cookingStage.getStoveArea();
    for (int i = 0; i < 4; i++){
        if (PizzaList[i].state == Cooking){
            PizzaList[i].setPosition( findPizzaCenter(i + 1) );//Finds center of pizza based on num Pizza
            PizzaList[i].setCookTime(cookTime);
            PizzaList[i].draw();
            PizzaList[i].checkIfClicked();
        }
    }

}





