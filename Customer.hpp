#pragma once
#include "Constents.hpp"
#include "TicketRack.hpp"
#include "Order.hpp"

enum customerType {Unassigned, Zombie, Snowman, Mantis};


class Customer
{

 


    public:
    bool isActive;
    bool isOrdering;
    int difficulty;
    int customerId;
    int waitTime;

    Customer();
    void Update(TicketRack* ticketRack, int customerNumber, int dayTimeFrame);

    private:
    
    void drawCustomer(int dayTimeFrame, bool animated);
    void doSpeechBubble(int delay);

    float scale;//scale increases each frame to show the customer approaching
    int x;
    int y;
    int delay; //delay when ordering
    Order banana;

    customerType type;


};