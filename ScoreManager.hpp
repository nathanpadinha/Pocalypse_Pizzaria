#pragma once

#include "Constents.hpp"
#include "Order.hpp"
#include "Pizza.hpp"
#include "OrderTake.hpp"

//#include "curl/curl.h"

class ScoreManager
{

    public:
    static string get_scores(); //get scores from python server
    static void post_scores(string input); //post string to python server
    static int calculateScores(Order ticket, OrderTake customerManager, Pizza pizza); //calculate final grade for pizza

    int updateHighScore(int finalScore, int seed);



};