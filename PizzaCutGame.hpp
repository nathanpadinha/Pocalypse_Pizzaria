#include "Constents.hpp"
#include "Pizza.hpp"

/*Calculates the midpoint of a between 2 vectors
Pre:
    2 fully populated Vector2
Post:
    Returns Vector2
Author: Nathan Padinha
*/
Vector2 calculateMidpoint(Vector2 vector1,  Vector2 vector2);

/*Calculates Points based on distance between midpoint of player line and pizza center
and the furthest possible distance normalized to 100
Pre:
     1 fully populated Vector2
Post:
    Returns int


Author: Nathan Padinha */
int calculatePoints(Vector2 lineStart, Vector2 lineEnd, Pizza &PlayerPizza);

/*Cecks if line is valid given two vectors
Pre:
     
Post:
      
Author: Nathan Padinha */
bool checkLineValid(Vector2 lineStart, Vector2 lineEnd, Pizza &PlayerPizza);

//Minigame function with pizza passed
void playPizzaCut(Pizza &PlayerPizza);

class CutLine{
    private:
        Vector2 start;
        Vector2 end;
        float thickness;
        Color color;
    public:
        CutLine(Vector2 st,Vector2 ed, float thick, Color cl){
            start = st;
            end = ed;
            thickness = thick;
            color = cl;
        }
        void draw(){
            DrawLineEx(start, end, thickness, color);

        }
};