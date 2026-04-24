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

    Cheese[0] = LoadTexture("textures/PizzaStuff/Cheese-00.png");
    Cheese[1] = LoadTexture("textures/PizzaStuff/Cheese-01.png");
    Cheese[2] = LoadTexture("textures/PizzaStuff/Cheese-02.png");
    Cheese[3] = LoadTexture("textures/PizzaStuff/Cheese-03.png");
    Cheese[4] = LoadTexture("textures/PizzaStuff/Cheese-04.png");
    Cheese[5] = LoadTexture("textures/PizzaStuff/Cheese-05.png");
    Cheese[6] = LoadTexture("textures/PizzaStuff/Cheese-06.png");
    Cheese[7] = LoadTexture("textures/PizzaStuff/Cheese-07.png");
    Cheese[8] = LoadTexture("textures/PizzaStuff/Cheese-08.png");

    PizzaBase[0] = LoadTexture("textures/PizzaStuff/TomatoBase.png");
    PizzaBase[1] = LoadTexture("textures/PizzaStuff/BloodBase.png");
    PizzaBase[2] = LoadTexture("textures/PizzaStuff/RadioactiveBase.png");
    PizzaBase[3] = LoadTexture("textures/PizzaStuff/NoBase.png");

    TimerDigits[0] = LoadTexture("textures/Timer/Timer-0.png");
    TimerDigits[1] = LoadTexture("textures/Timer/Timer-1.png");
    TimerDigits[2] = LoadTexture("textures/Timer/Timer-2.png");
    TimerDigits[3] = LoadTexture("textures/Timer/Timer-3.png");
    TimerDigits[4] = LoadTexture("textures/Timer/Timer-4.png");
    TimerDigits[5] = LoadTexture("textures/Timer/Timer-5.png");
    TimerDigits[6] = LoadTexture("textures/Timer/Timer-6.png");
    TimerDigits[7] = LoadTexture("textures/Timer/Timer-7.png");

    OVERCHARGE[0] = LoadTexture("textures/Backgrounds/PizzaGrillOVERCHARGE-1.png");
    OVERCHARGE[1] = LoadTexture("textures/Backgrounds/PizzaGrillOVERCHARGE-2.png");

    ChompCounter[0] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_02.png");
    ChompCounter[1] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_03.png");
    ChompCounter[2] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_04.png");
    ChompCounter[3] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_05.png");
    ChompCounter[4] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_06.png");
    ChompCounter[5] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_07.png");
    ChompCounter[6] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_08.png");
    ChompCounter[7] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_09.png");
    ChompCounter[8] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_10.png");
    ChompCounter[9] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_11.png");
    ChompCounter[10] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_12.png");
    ChompCounter[11] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_13.png");
    ChompCounter[12] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_14.png");
    ChompCounter[13] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_15.png");
    ChompCounter[14] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_16.png");
    ChompCounter[15] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_17.png");
    ChompCounter[16] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_18.png");
    ChompCounter[17] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_19.png");
    ChompCounter[18] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_20.png");
    ChompCounter[19] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_21.png");
    ChompCounter[20] = LoadTexture("textures/Backgrounds/ChompCounter/ChompCounter_22.png");

    FrontCounterBackground = LoadTexture("textures/Backgrounds/FrontCounterBackground.png");

}
