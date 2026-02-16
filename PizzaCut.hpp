#include "constents.hpp"

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
int calculatePoints(Vector2 midpoint);

/*Cecks if line is valid given two vectors
Pre:
    2 
Post:
    No issues - 0
    Line to short - 1
    Line start location invalid - 2
    Line end location invalid - 2

     
Author: Nathan Padinha */
int checkLineValid(Vector2 lineStart, Vector2 lineEnd);

void DrawCenteredText(string text, int posX, int posY, int fontSize, Color color);