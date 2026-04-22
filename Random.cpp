#include "Random.hpp"

  
bool RandomClass::isInitialized = false;
int RandomClass::num_obj = 0;
int RandomClass::generation_seed = 1234;

/*Sets seed for whole class intended for use at begining of main
*NOTE Calling this constructor again will not reseed random number generator
*/
RandomClass::RandomClass(int user_seed){
    num_obj++;
    if(!isInitialized){
        generation_seed = user_seed;
        random_numbers.push_back(((1664525 * user_seed) + 1013904223));
        isInitialized = true;
    }else{
        random_numbers.push_back(((1664525 * generation_seed) + 1013904223 + num_obj ));
    }
}


/*Allows for random objects without seed entry
*NOTE: Making an object with this constructor still uses the seed from main
*NOTE: Useing this to create an object if no seed has been set will set the seed to 1234
*/
RandomClass::RandomClass(){
    if(isInitialized){
        num_obj++;
        random_numbers.push_back(((1664525 * generation_seed) + 1013904223 + num_obj ));
    }
}

/*Generates a random number
* MOD will set a max value for your generation
* to generate a number 0 - 9  obj.generate(10)


*/ 
int RandomClass:: generate(int mod){
    int temp = ((1664525 * random_numbers.back()) + 1013904223);
    random_numbers.push_back(temp);
    return(abs(temp % mod));
}

void RandomClass:: seed(int user_seed){
    generation_seed = user_seed;
    random_numbers.push_back(((1664525 * user_seed) + 1013904223 + num_obj ));

}