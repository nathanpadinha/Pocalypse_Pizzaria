#pragma once
#include "Constents.hpp"
#include "TicketRack.hpp"
#include "Order.hpp"




class Customer
{


    public:
    bool isActive;
    bool isOrdering;
    
    Customer();
    void Update(TicketRack* ticketRack, int customerNumber);

    private:
    
    float scale;//scale increases each frame to show the customer approaching
    int x;
    int y;
    int delay; //delay when ordering





};