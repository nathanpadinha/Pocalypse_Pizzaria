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

    int updateHighScore(int finalScore, int seed); //get current high score, and update it if necessary



};