#pragma once

#include "Constents.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "TicketRack.hpp"
#include "Pizza.hpp"
#include "Customer.hpp"


class OrderTake
{


public:
    OrderTake();//int calculatePercentScore(Pizza pizza, Order order, Customer customer){
    void Update(TicketRack* ticketRack, int dayTimeFrame, int customerScheduleDifficulty[3][4], int day, vector<Pizza> &PizzaList, vector<Customer> &listOfCustomers, int &points);
    //Pizza getActivePizzaSubmission();
    Pizza *SubmitPizza;
    bool pizzasDone[4];
    bool chompMode;
    void calculatePoints(Order order, Customer customer, Pizza pizza, int &userScore);




private:
    int seed;
    int iterator;
    int turnInIterator;
    bool chomped;
    double happinessMaltiplyer;
    
    int getPointsForCookTime(Order order, Pizza pizza);
    
    int compareToppings(Order order, Pizza pizza);
    int compareSauce(Order order, Pizza pizza);
    
    int getPointsForToppings(Order order, Pizza pizza);

    double getHappyMaltiplyer(Order order, Customer customer);

    bool pizzaSubmited;
    bool pizzaScored[4];
    
    Order currentOrder;
    int coustmerID;
    Customer currentCustomer;


};




