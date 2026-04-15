#pragma once

#include "Constents.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "TicketRack.hpp"


//somewhat poorly named, this just holds and manages all the customers. 
class OrderTake
{


public:
    OrderTake();
    void Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day);
    Customer customers[4];


private:
    int seed;
    int iterator;


};




