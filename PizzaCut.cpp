#include "PizzaCut.hpp"


Vector2 PizzaCenter = {500.0f, 500.0f};
double PizzaRadius = 200.00;

Vector2 calculateMidpoint(Vector2 vector1,  Vector2 vector2){
    Vector2 midpoint;
    midpoint.x = (vector1.x + vector2.x) / 2;
    midpoint.y = (vector1.y + vector2.y) / 2;
    return midpoint;
}

bool checkLineValid(Vector2 lineStart, Vector2 lineEnd){
    bool lineValid = true;
    
    //Check for starting inside the pizza
    if ( CheckCollisionPointCircle(lineStart, PizzaCenter, PizzaRadius) ){ 
        lineValid = false;
    }else if (CheckCollisionPointCircle(lineEnd, PizzaCenter, PizzaRadius) ){
        lineValid = false;
    } else if( Vector2Distance(lineStart,lineEnd) < (PizzaRadius)/4 ){ 
        lineValid = false;
    }
    return lineValid;
    
}

int calculatePoints(Vector2 lineStart, Vector2 lineEnd){
    if( !(checkLineValid(lineStart, lineEnd)) ){//Catch invalid entry 
        return 0 ;
    } 
    
    double points;
    Vector2 midpoint = calculateMidpoint(lineStart, lineEnd);
    
    double distance = Vector2Distance(midpoint, PizzaCenter);
    
    //Closer to center is more points
    points = SCREEN_WIDTH - distance;

    //Normalize between 0 and 100

    points = ((points) / 8);
    

    return trunc(points);
}


//!FIX THESE LATER
    Vector2 mousePosition1, mousePosition2;
    int numCuts = 0, totalPoints= 0;
    //int goalCuts = 3; //Not necessary anymore

void PizzaCutGM(){
    //Initilize variables before gameloop

    //while(!WindowShouldClose()){
    //if(! (numCuts < goalCuts)){ return; } //Exit Minigame when goal reached
    
    //Core Game Logic
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Set line start point (Vector2: mousePosition1)
        mousePosition1 = GetMousePosition();
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ //Set line end point (Vector2: mousePosition2)
        mousePosition2 = GetMousePosition();
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        totalPoints += calculatePoints(mousePosition1, mousePosition2);
        if ( (checkLineValid(mousePosition1, mousePosition2))){//Fix later line valid checked inside calculate points do it need to be reused?
            numCuts++;
        }

    }
//Start Drawing 
        //BeginDrawing();
        
        //ClearBackground(RAYWHITE);//Clear Background
        
        DrawText(to_string(totalPoints).c_str(), 120 , 120, 20, GRAY);//Points
        
        DrawCircleV(PizzaCenter, PizzaRadius, BROWN);//Draw Pizza 
        DrawLineEx(mousePosition1, mousePosition2, 3.0, BLUE);//Draw Line

        //EndDrawing();


    //}

    return ;
};