/*This file is for implimentation in any and every file no variables or functions not writen or defined in this file may be 
included if you have any conserns about adding anything to this file just doubble check with someone first :)*/
#pragma once

//Raylib imports
#include "raylib.h"
#include "raymath.h"
//Standard Imports
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

//Texture Manager Import
#include "TextureManager.hpp"
enum gameState {Default, OrderTaking, AddToppings, PizzaCook, PizzaCut};

//include namespace
using namespace std;

inline TextureManager texturemanager;

