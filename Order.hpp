#pragma once

#include "Constents.hpp"



class Order
{
    public:
        Order(); //Default Constructor
        Order(int difficulty, int ticketQuantity, int customerId); //basically just a default constructor, but maybe will have more stuff later? idk
        
        void DisplayOrderAsTicket(); //Displays order as a ticket, basically just some text on a white box
        void TicketDraggingBehavior(); //drags the ticket around by the mouse
        void Update(); //Updates order, does dragging and display. 
        
        string TranslateTopping(int ToppingID);
        string TranslateSauce(int SauceID);
        Texture2D ToppingIDtoTexture(int ToppingID);


        string GetSause();
        string GetTopping(int index);
        
        int GetToppingAmount(int index);
        int GetCookTime();
        int GetSliceAmount();

        bool CheckCompletionBehavior(bool turnIn);

    private:
        //Varibles

        bool isActive; //if false Ticket won't be displayed
        int offsetX, offsetY;
        int x, y;
        double scale;
        
        bool doingstuff;

        int customerId;
        
        //Variables that define the order
        int sauceID;
        string topping[3];
        int toppingID[3], toppingAmount[3];
        int cookTime, sliceAmount;//Num cuts
       



    void GetScaleFromDistanceToStagingArea();


};