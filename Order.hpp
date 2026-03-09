#pragma once

#include "Constents.hpp"



class Order
{
public:
Order(); //Default Constructor
Order(int difficulty, int ticketQuantity); //basically just a default constructor, but maybe will have more stuff later? idk
void DisplayOrderAsTicket(); //Displays order as a ticket, basically just some text on a white box
void TicketDraggingBehavior(); //drags the ticket around by the mouse
void Update(); //Updates order, does dragging and display. 

//Making these public because that's way easier for accessing them. Also abstraction isn't 
//really that necessary, I don't think? If it is, we can change it in a later cycle
bool isActive; //If order isn't active, then won't display in ticket rack.
int sauceID;
int toppingID[3];
int toppingAmount[3];
int cookTime;
int sliceAmount;

int x;
int y;

private:
string TranslateTopping(int ToppingID);
string TranslateSauce(int SauceID);
Texture2D ToppingIDtoTexture(int ToppingID);
void GetScaleFromDistanceToStagingArea();

double scale;
bool doingstuff;
int offsetX;
int offsetY;
//change this later, 6 should not be a constant

};