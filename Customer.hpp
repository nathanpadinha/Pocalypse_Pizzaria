#pragma once
#include "Constents.hpp"
#include "TicketRack.hpp"
#include "Order.hpp"

enum customerType {Unassigned, Zombie, Snowman, Mantis};


class Customer{
    public:
//Methods
    //Constructor
        Customer();
    //Accsessors
        //Customer Data
            int getID();
            int getDifficulty();
            int getWaitTime();
            void setActive();
            void setInactive();
            void setDifficulty(int newDiff);
        //Art Data
            float getScale();
            int getX();
            int getY();
    //Misc
        void Update(TicketRack* ticketRack, int customerNumber, int dayTimeFrame);
        static Customer getCustomerByID(vector <Customer> listOfCustomers, int targetCustomerID);

    private:
//Variables
    //Customer Data
        bool isActive;
        bool isOrdering;
        int difficulty;
        int customerId;
        int waitTime;
    //Art Data
        float scale;//scale increases each frame to show the customer approaching
        int x;
        int y;
    //Misc     
        int delay; //delay when ordering
        Order banana;
        customerType type;
//Methods
    //Art Methods
        void drawCustomer(int dayTimeFrame, bool animated);
        void doSpeechBubble(int delay);
    


};