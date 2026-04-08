#pragma once
#include "TextureManager.hpp"


TextureManager::TextureManager()
{

}

void TextureManager::LoadAllTextures()
{
    Finger = LoadTexture("textures/Finger.png");
    GlowingMushroom = LoadTexture("textures/GlowingMushroom.png");
    HumanPepperoni = LoadTexture("textures/HumanPepperoni.png");
    MouseBrain = LoadTexture("textures/MouseBrain.png");
    Pineapple = LoadTexture("textures/Pineapple.png");
    ToothPepper = LoadTexture("textures/ToothPepper.png");

    TicketRack = LoadTexture("textures/Backgrounds/TicketRack.png");

    TitleScreen = LoadTexture("textures/Backgrounds/TitleScreen.png");

    FrontCounter = LoadTexture("textures/Backgrounds/FrontCounter.png");
    SlicingTable = LoadTexture("textures/Backgrounds/SlicingTable.png");
    PizzaGrill = LoadTexture("textures/Backgrounds/PizzaGrill.png");
    PizzaGrillStates[0] = PizzaGrill;
    PizzaGrillStates[1] = LoadTexture("textures/Backgrounds/PizzaGrill-1.png");
    PizzaGrillStates[2] = LoadTexture("textures/Backgrounds/PizzaGrill-2.png");
    PizzaGrillStates[3] = LoadTexture("textures/Backgrounds/PizzaGrill-3.png");
    PizzaGrillStates[4] = LoadTexture("textures/Backgrounds/PizzaGrill-4.png");

    TimerDigits[0] = LoadTexture("textures/Timer/Timer-0.png");
    TimerDigits[1] = LoadTexture("textures/Timer/Timer-1.png");
    TimerDigits[2] = LoadTexture("textures/Timer/Timer-2.png");
    TimerDigits[3] = LoadTexture("textures/Timer/Timer-3.png");
    TimerDigits[4] = LoadTexture("textures/Timer/Timer-4.png");
    TimerDigits[5] = LoadTexture("textures/Timer/Timer-5.png");
    TimerDigits[6] = LoadTexture("textures/Timer/Timer-6.png");
    TimerDigits[7] = LoadTexture("textures/Timer/Timer-7.png");

    TomatoBase = LoadTexture("textures/PizzaStuff/TomatoBase.png");
    CheeseStages[0] = LoadTexture("textures/PizzaStuff/Cheese-00.png");
    CheeseStages[1] = LoadTexture("textures/PizzaStuff/Cheese-01.png");
    CheeseStages[2] = LoadTexture("textures/PizzaStuff/Cheese-02.png");
    CheeseStages[3] = LoadTexture("textures/PizzaStuff/Cheese-03.png");
    CheeseStages[4] = LoadTexture("textures/PizzaStuff/Cheese-04.png");
    CheeseStages[5] = LoadTexture("textures/PizzaStuff/Cheese-05.png");
    CheeseStages[6] = LoadTexture("textures/PizzaStuff/Cheese-06.png");
    CheeseStages[7] = LoadTexture("textures/PizzaStuff/Cheese-07.png");
    CheeseStages[8] = LoadTexture("textures/PizzaStuff/Cheese-08.png");


    DisplayPizza0 = LoadTexture("textures/DisplayPizza0.png");
    DisplayPizza1 = LoadTexture("textures/DisplayPizza1.png");

    ZombieGuy = LoadTexture("textures/ZombieGuy.png");


}
