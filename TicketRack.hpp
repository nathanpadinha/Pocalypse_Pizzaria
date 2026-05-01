//header file for the ticket rack class, which holds and displays orders as tickets.
//I'm thinking that this class will be displayed at the top of every screen, as it's basically always useful.
#pragma once
#include "Constents.hpp"

#include "Order.hpp"
//#include "OrderTake.hpp"



class TicketRack{
    public:
//Methods
    //Constructor
        TicketRack(gameState* state);
    
    //Accsessors
        int GetOrderQuantity();//*Gets amount of tickets currently in vector
        Order GetOrder(int index);
        Order* GetOrderPtr(int index); // New method to get pointer for modification
    
    //Mutators
        void AddOrder(Order order);
    
    //Drawing
        void DisplayRack(); //*displays ticket rack 
    
    //Misc
        void Update();
        bool CheckCompletionForOrder(int index, bool turnIn); // New method to check completion on the actual order
        
    private:
        
    void ResetTicketLocations(); //Brings all the tickets back to the rack, in case they get dragged around too much.
        
        gameState* currentState;
        
        vector <Order> orders{4}; 
};