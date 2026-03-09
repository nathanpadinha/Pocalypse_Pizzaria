//header file for the ticket rack class, which holds and displays orders as tickets.
//I'm thinking that this class will be displayed at the top of every screen, as it's basically always useful.
#pragma once
#include "Constents.hpp"

#include "Order.hpp"




class TicketRack
{

    public:
    TicketRack(gameState* state);

    void Update();
    void DisplayRack(); //displays ticket rack. 
    int GetOrderQuantity(); //returns num of orders in rack, for spacing purposes. Called by OrderTake when generating orders, and by DisplayRack
    void AddOrder(Order newOrder); 

    //Change Screen Buttons
    

    private:
    void ResetTicketLocations(); //Brings all the tickets back to the rack, in case they get dragged around too much.
    gameState* currentState;

    Order orders[4]; //vector of orders, this is the essential functionality of the ticket rack
    



};