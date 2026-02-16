#include "constents.hpp"
#include "PizzaCut.hpp"



Vector2 PPizzaCenter = { 400.0f, 400.0f };
float PPizzaRadius = 250.0;


//Drawing Pizza ***TEMP UNTIL ASSETS***
Vector2 PizzaLineHZStart = { PPizzaCenter.x - PPizzaRadius, PPizzaCenter.y  };
Vector2 PizzaLineHZEnd = { PPizzaCenter.x + PPizzaRadius, PPizzaCenter.y  };
Vector2 PizzaLineVTStart = { PPizzaCenter.x, PPizzaCenter.y - PPizzaRadius };
Vector2 PizzaLineVTEnd = { PPizzaCenter.x, PPizzaCenter.y + PPizzaRadius };

//Player line 
Vector2 mousePosition1;
Vector2 mousePosition2;
Vector2 midpointOfLine;
    
float distanceFromCenter;

string text;

double totalPoints = 0.00 , points;

const int screenWidth = 800, screenHeight = 800;
const Color backgroundColor = RAYWHITE;



int main(void){ InitWindow(screenWidth, screenHeight, "Pizza Cut"); SetTargetFPS(60); //Set on same line as main method to clear up room & because its constent

    while (!WindowShouldClose()){
        //Reset Variables
        points = 0;
        
        
        // Update variables   
        
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Set line start point (Vector2: mousePosition1)
            mousePosition1 = GetMousePosition();
        }if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ //Set line end point (Vector2: mousePosition2
                mousePosition2 = GetMousePosition();
                midpointOfLine = calculateMidpoint(mousePosition1, mousePosition2);
            }if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                switch (checkLineValid(mousePosition1, mousePosition2)) {
                case 1:
                text = "Your line is to short";
                break;
                case 2:
                text = "You cut can't start or stop inside the pizza";
                break;
                default:
                    points = calculatePoints(midpointOfLine);
                    text = "Thats a good cut! You get " + to_string(points) + " points!";
            }
            totalPoints += points; // Update points

            }
       


        // Draw
        BeginDrawing();

            ClearBackground(backgroundColor);
            DrawCenteredText(to_string(totalPoints), 100 , 100, 20, GRAY);
            DrawCircleV(PPizzaCenter, PPizzaRadius, DARKBLUE);
            DrawLineEx(PizzaLineHZStart, PizzaLineHZEnd, 3.0 , RED);
            DrawLineEx(PizzaLineVTStart, PizzaLineVTEnd, 3.0 , RED);


            DrawCenteredText(text, PizzaLineVTEnd.x, PizzaLineVTEnd.y, 20, GRAY);
            DrawLineEx(mousePosition1, mousePosition2, 3.0, BLACK);











            
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }


    
    CloseWindow();
    

    return 0;
}
