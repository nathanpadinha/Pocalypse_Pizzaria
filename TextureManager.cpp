#pragma once
#include "TextureManager.hpp"


//instantiate in constents with "inline TextureManager texturemanager;" for use in all classes that include constents"
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


}
