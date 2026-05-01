#pragma once

#include "Constents.hpp"



class Order{
    public:
//Methods
    //Constructors 
        Order();//*Default constructor, sets isAvtive to false
        Order(int difficulty, int ticketQuantity, int customerId); //*Overloaded constructor, sets values and includes randomization
    
    //User Interaction Methods
        void DisplayOrderAsTicket();//*Draws ticket and relevent information
        void TicketDraggingBehavior(); //*Allows player to drag ticket with mouse

    //From ID to Name 
        string TranslateTopping(int ToppingID);
        string TranslateSauce(int SauceID);
      
    //Accessors
        int GetSauseID();
        int GetToppingID(int index);
        int GetToppingAmount(int index);
        string GetToppingName(int index);
        int GetCookTime();
        int GetSliceAmount();
        int GetCustomerID();
        int GetX();
        int GetY();
        bool GetActiveStatus();
        void SetActive();
        void SetInactive();
        void SetX(int newX);
        void SetY(int newY);
    //Misc
        Texture2D ToppingIDtoTexture(int ToppingID); //*Gets topping texture from ID
        bool CheckCompletionBehavior();       
        void Update();//*Updates order, does dragging and display
        int toppingID[3], toppingAmount[3];
    private:
//Varibles
    //Order Data
        int sauceID;
        string topping[3];
  
        int cookTime;
        int sliceAmount;
        int customerId;

    //Drawing Data
        bool isActive; //*Ticket only displayed if true
        int offsetX, offsetY;
        int x, y;
        double scale;
        bool doingstuff;
    
//Methods
    //Misc
        void GetScaleFromDistanceToStagingArea();
};