#pragma once
#include "PizzaCutGame.hpp"

sliceLine calculateCutLine(CutLine line, Vector2 pizzaCenter, float pizzaRadius);


Vector2 pizzaCenter = {500.0f, 500.0f};

Vector2 calculateMidpoint(Vector2 vector1,  Vector2 vector2){
    Vector2 midpoint;
    midpoint.x = (vector1.x + vector2.x) / 2;
    midpoint.y = (vector1.y + vector2.y) / 2;
    return midpoint;
}

bool checkLineValid(Vector2 lineStart, Vector2 lineEnd, Pizza &CookPlayerPizza){
    bool lineValid = true;
    Vector2 midpoint = calculateMidpoint(lineStart, lineEnd);
    //Check for starting inside the pizza
    if ( CheckCollisionPointCircle(lineStart, pizzaCenter, CookPlayerPizza.getRadius()) ){ 
        lineValid = false;
    }else if (CheckCollisionPointCircle(lineEnd, pizzaCenter, CookPlayerPizza.getRadius()) ){
        lineValid = false;
    } else if( Vector2Distance(lineStart,lineEnd) < (CookPlayerPizza.getRadius())/4 ){ 
        lineValid = false;
    }else if (!(CheckCollisionPointCircle(midpoint, pizzaCenter, CookPlayerPizza.getRadius()) ) ){//If line dosnt go throgh pizza
        lineValid = false;
    }
    return lineValid;
    
}

int calculatePoints(Vector2 lineStart, Vector2 lineEnd, Pizza &CookPlayerPizza){
    if( !(checkLineValid(lineStart, lineEnd, CookPlayerPizza)) ){//Catch invalid entry 
        return 0 ;
    } 
    
    double points;
    Vector2 midpoint = calculateMidpoint(lineStart, lineEnd);
    
    double distance = Vector2Distance(midpoint, pizzaCenter);
    
    //Closer to center is more points
    points = SCREEN_WIDTH - distance;

    //Normalize between 0 and 100

    points = ((points) / 8);
    

    return trunc(points);
}


//!FIX THESE LATER
    Vector2 mousePosition1, mousePosition2;
    bool isDragging = false;
    int numCuts = 0, totalPoints= 0;
    vector <CutLine> lines;
    Pizza cookTestPizza; 
    Pizza* CookPlayerPizza = &cookTestPizza;



void playPizzaCut(Pizza PizzaList[0]){

        if (PizzaList[0].getState() == Cutting) CookPlayerPizza = &PizzaList[0];
        else if (PizzaList[1].getState() == Cutting) CookPlayerPizza = &PizzaList[1];
        else if (PizzaList[2].getState() == Cutting) CookPlayerPizza = &PizzaList[2];
        else if (PizzaList[3].getState() == Cutting) CookPlayerPizza = &PizzaList[3];
        else {
            CookPlayerPizza = &cookTestPizza;
            (*CookPlayerPizza).setActive(false);
            lines.clear();
            isDragging = false;
        }
    
    (*CookPlayerPizza).setPosition(pizzaCenter);
    //Core Game Logic
    (*CookPlayerPizza).draw();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        mousePosition1 = GetMousePosition();
        isDragging = true;
    }
    if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        mousePosition2 = GetMousePosition();
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isDragging){
        totalPoints += calculatePoints(mousePosition1, mousePosition2, (*CookPlayerPizza));
        if (checkLineValid(mousePosition1, mousePosition2, (*CookPlayerPizza))){
            numCuts += 1;
            (*CookPlayerPizza).setNumCuts(numCuts);
            lines.emplace_back(mousePosition1, mousePosition2, 3.0, BLACK);
        }
        isDragging = false;
    }
//Start Drawing 
        (*CookPlayerPizza).sliceLines.clear();
        for(CutLine line: lines){
            //add cuts to pizza
            sliceLine slice = calculateCutLine(line, (*CookPlayerPizza).getPosition(), (*CookPlayerPizza).getRadius());
            (*CookPlayerPizza).sliceLines.push_back(slice);

            //draw cut line, just for cutting minigame (disabled for now, maybe permanently)
            //line.draw();

        }
        if (isDragging){
            DrawLineEx(mousePosition1, mousePosition2, 3.0, BLUE);//Draw Line
        }


    //}
        (*CookPlayerPizza).checkIfClicked();
    return ;
};

//adapted from https://cp-algorithms.com/geometry/circle-line-intersection.html
//calculates the points in which a line intersects with a circle
sliceLine calculateCutLine(CutLine line, Vector2 pizzaCenter, float r)
{
    sliceLine result;

    float a = line.getEnd().y - line.getStart().y;
    float b = line.getStart().x - line.getEnd().x;
    float c = -(a*(line.getStart().x-pizzaCenter.x) + b*(line.getStart().y-pizzaCenter.y));

    float x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);

    float d = r*r - c*c/(a*a+b*b);
    float mult = sqrt (d / (a*a+b*b));
    float ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    
    result.end = (Vector2){ax, ay};
    result.start = (Vector2){bx, by};

    return result;
}