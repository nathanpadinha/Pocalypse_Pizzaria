#include "Constents.hpp"

class Ticket{
    private:
        vector <string> toppings;
        int cookTime;
        int numCuts;
        string pizzaBase;
    public:
        /*To do use order generation code to make ticket*/
        Ticket();
        
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
