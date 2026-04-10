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

    FrontCounter[0] = LoadTexture("textures/Backgrounds/FrontCounter-1.png");
    FrontCounter[1] = LoadTexture("textures/Backgrounds/FrontCounter-2.png");

    SlicingTable = LoadTexture("textures/Backgrounds/SlicingTable.png");
    ToppingTable = LoadTexture("textures/Backgrounds/ToppingTable.png");
    PizzaGrill = LoadTexture("textures/Backgrounds/PizzaGrill.png");

    PizzaGrillz[0] = LoadTexture("textures/Backgrounds/PizzaGrill-1.png");
    PizzaGrillz[1] = LoadTexture("textures/Backgrounds/PizzaGrill-2.png");
    PizzaGrillz[2] = LoadTexture("textures/Backgrounds/PizzaGrill-3.png");
    PizzaGrillz[3] = LoadTexture("textures/Backgrounds/PizzaGrill-4.png");

    SauceRepresentations[0] = LoadTexture("textures/Sauce-1.png");
    SauceRepresentations[1] = LoadTexture("textures/Sauce-2.png");
    SauceRepresentations[2] = LoadTexture("textures/Sauce-3.png");
    
    SliceRepresentations[3] = LoadTexture("textures/Slices-1.png");
    SliceRepresentations[2] = LoadTexture("textures/Slices-2.png");
    SliceRepresentations[1] = LoadTexture("textures/Slices-3.png");
    SliceRepresentations[0] = LoadTexture("textures/Slices-4.png");

    Timer[0] = LoadTexture("textures/Timer/Timer-0.png");
    Timer[1] = LoadTexture("textures/Timer/Timer-1.png");
    Timer[2] = LoadTexture("textures/Timer/Timer-2.png");
    Timer[3] = LoadTexture("textures/Timer/Timer-3.png");
    Timer[4] = LoadTexture("textures/Timer/Timer-4.png");
    Timer[5] = LoadTexture("textures/Timer/Timer-5.png");
    Timer[6] = LoadTexture("textures/Timer/Timer-6.png");
    Timer[7] = LoadTexture("textures/Timer/Timer-7.png");



    DisplayPizza0 = LoadTexture("textures/DisplayPizza0.png");
    DisplayPizza1 = LoadTexture("textures/DisplayPizza1.png");

    ZombieGuy[0] = LoadTexture("textures/ZombieGuy_0.png");
    ZombieGuy[1] = LoadTexture("textures/ZombieGuy_1.png");

    Snowman[0] = LoadTexture("textures/Snowman_0.png");
    Snowman[1] = LoadTexture("textures/Snowman_1.png");
    Snowman[2] = LoadTexture("textures/Snowman_2.png");
    Snowman[3] = LoadTexture("textures/Snowman_3.png");

    Mantis[0] = LoadTexture("textures/Mantis_0.png");
    Mantis[1] = LoadTexture("textures/Mantis_1.png");

    SpeechBubble = LoadTexture("textures/SpeechBubble.png");


}
