#include "Pizza.hpp"

Pizza::Pizza()
{
    baseColor = BEIGE;
}

void Pizza::AddTopping(string name, Vector2 pos, Color color)
{
    toppings.push_back({ name, pos, color });
}