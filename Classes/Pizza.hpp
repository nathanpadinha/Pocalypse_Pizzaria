#include "Constents.hpp"

class Pizza{
    private:
        vector <Topping> toppings;
        int cookTime;
        int numCuts;
        string pizzaBase;
    public:
        /*Creates a pizza object with all values set to null
        Pre: N/a
        Post: N/a
        Author: Nathan
        IDE: VScode */
        Pizza();
        
        //Class Getters
        getCookTime();
        getNumCuts();
        getPizzaBase();
        getToppings();
        //Class Setters
        setCookTime(int time);
        setNumCuts(int cuts);
        setPizzaBase(string base);
        setToppings(vector <string> topping2);


};
