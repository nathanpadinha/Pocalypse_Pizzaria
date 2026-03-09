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

    DisplayPizza0 = LoadTexture("textures/DisplayPizza0.png");
    DisplayPizza1 = LoadTexture("textures/DisplayPizza1.png");

    ZombieGuy = LoadTexture("textures/ZombieGuy.png");


}
