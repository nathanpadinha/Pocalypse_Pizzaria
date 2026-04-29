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
    void calculatePoints(Order order, Customer customer, Pizza pizza);




private:
    int seed;
    int iterator;
    int turnInIterator;
    bool chomped;
    
    int getPointsForCookTime(Order order, Pizza pizza);
    
    int compareToppings(Order order, Pizza pizza);
    int compareSauce(Order order, Pizza pizza);
    
    int getPointsForToppings(Order order, Pizza pizza);
    


};




