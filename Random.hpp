#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

class RandomClass{
    public:
        RandomClass(int user_seed);
        
        RandomClass();
        
        int generate(int mod = 100);
        
        void seed(int user_seed);
    
    private:
        static int generation_seed;
        static int num_obj;
        static bool isInitialized;
        vector<int> random_numbers;
};