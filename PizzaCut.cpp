#include "constents.hpp"
#include "PizzaCut.hpp"


const int screenWidth = 800, screenHeight = 800;

Vector2 PizzaCenter = { 400.0f, 400.0f };
float PizzaRadius = 250.0;

Vector2 calculateMidpoint(Vector2 vector1,  Vector2 vector2){
    Vector2 midpointOfLine;
    midpointOfLine.x = ( vector1.x + vector2.x ) / 2;
    midpointOfLine.x = ( vector1.x + vector2.x ) / 2;
    midpointOfLine.y = ( vector1.y + vector2.y ) / 2;
    midpointOfLine.y = ( vector1.y + vector2.y ) / 2;
    
    return midpointOfLine;
}

int calculatePoints(Vector2 midpoint){
    double distance = Vector2Distance(midpoint, PizzaCenter); //Get distance between midpoint and center 
    double points = 100 - ( (distance / screenWidth) * 100);
    
    points = ceil(points);
    int newPoints = points;
    
    return newPoints;
}

int checkLineValid(Vector2 lineStart, Vector2 lineEnd){
    if(Vector2Distance(lineStart, lineEnd) < (PizzaRadius * 2) ){ //Line to short
        return 1;
    }else if( CheckCollisionPointCircle(lineStart, PizzaCenter, PizzaRadius) ){//Line starts in pizza
        return 2;
    }else if( CheckCollisionPointCircle(lineEnd, PizzaCenter, PizzaRadius) ){//Line ends in pizza
        return 2;
    }
    else{
        return 0;
    }



}

void DrawCenteredText(string text, int posX, int posY, int fontSize, Color color){
    int textSize = MeasureText( text.c_str(), fontSize); 
    DrawText(text.c_str(), posX - (textSize/2), posY, fontSize, color);

}
