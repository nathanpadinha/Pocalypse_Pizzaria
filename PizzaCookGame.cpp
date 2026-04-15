#include "PizzaCookGame.hpp"



int numPizzas = 1;
int cookTime;
    

CookingStage cookingStage;



Vector2 findPizzaCenter(int numPizzas){
    Rectangle stove = cookingStage.getStoveArea();
    Vector2 pizzaCenter = {stove.x + stove.width/4, stove.y + stove.height/4};
    float temp;
    for( int i = 0; i < numPizzas -1 ; i++ ){
        if(numPizzas == 1){break;}
        temp = pizzaCenter.x;
        pizzaCenter.x = -(pizzaCenter.y);
        pizzaCenter.y = temp;
    }
    return pizzaCenter;
}


void playPizzaCook(Pizza &PlayerPizza){
    
    float dt = GetFrameTime();

    cookingStage.update(dt);//Updates object
    cookTime = (int) cookingStage.getCookTime(); //Casts to int and updates var

    // Do pizza cooking behavior

    cookingStage.draw();

    /**
     * Get stove position and center the pizza on it
     * * This allows the pizza to always appear on the stove
     */
    Rectangle stove = cookingStage.getStoveArea();
    
    PlayerPizza.setPosition( findPizzaCenter(numPizzas) );//Finds center of pizza based on num Pizza
    PlayerPizza.setCookTime(cookTime);
    PlayerPizza.draw();


}





