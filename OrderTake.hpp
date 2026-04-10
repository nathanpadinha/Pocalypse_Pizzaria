#pragma once

#include "Constents.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "TicketRack.hpp"



class OrderTake
{


public:
    OrderTake();
    void Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day);

private:
    int seed;
    Customer customers[4];
    int iterator;


};




