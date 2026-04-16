#pragma once
#include "PizzaCutGame.hpp"


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
    int numCuts = 0, totalPoints= 0;
    vector <CutLine> lines;
    Pizza cookTestPizza; 
    Pizza* CookPlayerPizza = &cookTestPizza;



void playPizzaCut(Pizza PizzaList[0]){


        if (PizzaList[0].state == Cutting) CookPlayerPizza = &PizzaList[0];
        else if (PizzaList[1].state == Cutting) CookPlayerPizza = &PizzaList[1];
        else if (PizzaList[2].state == Cutting) CookPlayerPizza = &PizzaList[2];
        else if (PizzaList[3].state == Cutting) CookPlayerPizza = &PizzaList[3];
        else {
            CookPlayerPizza = &cookTestPizza;
            (*CookPlayerPizza).setActive(false);
            lines.clear();
        }
    
    (*CookPlayerPizza).setPosition(pizzaCenter);
    //Core Game Logic
    (*CookPlayerPizza).draw();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Set line start point (Vector2: mousePosition1)
        mousePosition1 = GetMousePosition();
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ //Set line end point (Vector2: mousePosition2)
        mousePosition2 = GetMousePosition();
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        totalPoints += calculatePoints(mousePosition1, mousePosition2, (*CookPlayerPizza));
        if ( (checkLineValid(mousePosition1, mousePosition2, (*CookPlayerPizza)))){//Fix later line valid checked inside calculate points do it need to be reused?
            numCuts += 1;
            (*CookPlayerPizza).setNumCuts(numCuts);
            lines.emplace_back(mousePosition1, mousePosition2, 4.0, BLACK);
        }
    }
//Start Drawing 
        
        for(CutLine line: lines){
            line.draw();
        }
        if ( Vector2Distance(mousePosition1, pizzaCenter) < ((*CookPlayerPizza).getRadius() * 2) ){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                DrawLineEx(mousePosition1, mousePosition2, 3.0, BLUE);//Draw Line
            }
        }


    //}
        (*CookPlayerPizza).checkIfClicked();
    return ;
};