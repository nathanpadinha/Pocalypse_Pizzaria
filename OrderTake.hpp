#pragma once

#include "Constents.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "TicketRack.hpp"
#include "Pizza.hpp"


class OrderTake
{


public:
    OrderTake();//int calculatePercentScore(Pizza pizza, Order order, Customer customer){
    void Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day, Pizza PizzaList[]);
    //Pizza getActivePizzaSubmission();
    Pizza *SubmitPizza;
    bool pizzasDone[4];
    bool chompMode;
    Customer customers[4];
    void calculatePercentScore(Order order, Customer customer);




private:
    int seed;
    int iterator;
    int turnInIterator;
    bool chomped;


};




