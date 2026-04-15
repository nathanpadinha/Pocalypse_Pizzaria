


#include "ScoreManager.hpp"

#ifdef _WIN32
#define POPEN _popen
#define PCLOSE _pclose
#else
#define POPEN popen
#define PCLOSE pclose
#endif

string ScoreManager::get_scores(){

FILE* pipe = POPEN("python3 server/GetScores.py", "r");

char readInArray[100];
string scores;

while(fgets(readInArray, 100, pipe)) {
    scores += readInArray;
}
PCLOSE(pipe);
return scores;

}


void ScoreManager::post_scores(string input){

    system(("python server/PostScores.py " + input).c_str());

return;
}

//speed should be up to 6000
//topping Accuracy should be up to 100%
//cook accuracy should be up to 100%
//sliceAccuracy should be up to 100%
int ScoreManager::calculateScores(Order ticket, OrderTake customerManager, Pizza pizza){

    int speedPercent;

}