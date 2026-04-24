#pragma once
#include "raylib.h"

class TextureManager
{  

public:

    //These are public, you can call each to get the relevant texture.
    Texture2D Finger;
    Texture2D GlowingMushroom;
    Texture2D HumanPepperoni;
    Texture2D MouseBrain;
    Texture2D Pineapple;
    Texture2D ToothPepper;


    Texture2D SpeechBubble;

    //Title Screen stuff
    Texture2D TitleScreen;
    Texture2D DisplayPizza0;
    Texture2D DisplayPizza1;
    

    //Ticket Rack
    Texture2D TicketRack;

    //multiple animation states stored in array
    Texture2D FrontCounter[2];


    Texture2D SlicingTable;
    Texture2D ToppingTable;
    Texture2D PizzaGrill;

    Texture2D PizzaGrillz[4];
    
    Texture2D SauceRepresentations[3];

    Texture2D SliceRepresentations[4];

    Texture2D Timer[8];
    
    Texture2D ZombieGuy[2];
    Texture2D Snowman[4];
    Texture2D Mantis[2];

    Texture2D Cheese[9];

    Texture2D PizzaBase[4];

    Texture2D TimerDigits[8];

    Texture2D OVERCHARGE[2];

    Texture2D ChompCounter[20];
    Texture2D FrontCounterBackground;

    //Constructor
    //Instantiate in constents.hpp with "inline TextureManager texturemanager;" for use in all classes that include constents
    //don't forget to include TextureManager.hpp in constents.hpp
    TextureManager(); 

    //Call in main to load all textures at startup
    //!MUST BE LOADED AFTER WINDOW IS INITIALIZED
    void LoadAllTextures(); 



};