


#include "ScoreManager.hpp"

#ifdef _WIN32
#define POPEN _popen
#define PCLOSE _pclose
#else
#define POPEN popen
#define PCLOSE pclose
#endif

string ScoreManager::get_scores(){

    //opens file pipe to read in scores from python server
FILE* pipe = POPEN("python3 server/GetScores.py", "r");

char readInArray[100];
string scores;

while(fgets(readInArray, 100, pipe)) {
    scores += readInArray;
}
PCLOSE(pipe);
return scores;

}


// (1234:9999)(98769826:1786)(82:7862)(927:1234)

void ScoreManager::post_scores(string input){
    //just runs the python script to post input to scores (overwrite)
    system(("python server/PostScores.py " + input).c_str());

return;
}

int ScoreManager::updateHighScore(int finalScore, int seed) {
    string scores = get_scores();

    string result = "";
    int highScore = finalScore;
    bool found = false; 

    size_t pos = 0;
    while ((pos = scores.find('(', pos)) != string::npos) {
        size_t colon = scores.find(':', pos);
        size_t end = scores.find(')', pos);

        if(colon == string::npos || end == string::npos) {
            break;
        }

        int currentSeed = stoi(scores.substr(pos + 1, colon - pos - 1));
        int currentScore = stoi(scores.substr(colon + 1, end - colon - 1));

        if(currentSeed == seed) {
            found = true;
            currentScore = max(currentScore, finalScore);
            highScore = currentScore;
        }

        result += "(" + to_string(currentSeed) + ":" + to_string(currentScore) + ")";
        pos = end + 1;
    }

    // if seed isn't found, add it to the result string
    if(!found) {
        result += "(" + to_string(seed) + ":" + to_string(finalScore) + ")";
        highScore = finalScore;
    }

    post_scores(result);

    return highScore;
    
}