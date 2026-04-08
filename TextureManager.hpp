#pragma once
#include "raylib.h"
#include <array>

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


    Texture2D ZombieGuy;

    //Title Screen stuff
    Texture2D TitleScreen;
    Texture2D DisplayPizza0;
    Texture2D DisplayPizza1;
        

    //Ticket Rack
    Texture2D TicketRack;

    Texture2D FrontCounter;
    Texture2D SlicingTable;

    //Pizza Cook
    Texture2D PizzaGrill;
    std::array<Texture2D, 5> PizzaGrillStates;
    std::array<Texture2D, 8> TimerDigits;
    Texture2D TomatoBase;
    std::array<Texture2D, 9> CheeseStages;

    //Constructor
    //Instantiate in constents.hpp with "inline TextureManager texturemanager;" for use in all classes that include constents
    //don't forget to include TextureManager.hpp in constents.hpp
    TextureManager(); 

    //Call in main to load all textures at startup
    //!MUST BE LOADED AFTER WINDOW IS INITIALIZED
    void LoadAllTextures(); 



};
