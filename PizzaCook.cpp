#include "PizzaCook.hpp"

/**
 * CookingStage Constructor
 * * Initializes the stove area used for cooking pizzas
 * * Defines where the pizza will appear on the screen
 * TODO: will add spots for 4 pizzas later
 */
CookingStage::CookingStage() {
    stoveArea.x = 100;
    stoveArea.y = 150;
    stoveArea.width = 600;
    stoveArea.height = 400;
}

/**
 * Update function for the cooking stage
 * @parm dt Delta time between frames
 * * Currently unused but kept for future cooking logic
 * TODO: Use dt to track pizza cooking progress
 */
void CookingStage::update(float dt) {
    (void)dt;
}

/**
 * Draws the stove on the screen
 * * The stove is currently a gray rectangle
 * TODO: Make stove look like an actual grill
 */
void CookingStage::draw() {
    DrawRectangleRec(stoveArea, GRAY);
}

/**
 * Returns the stove area
 * * Other classes (Pizza) can use this to position objects
 */
Rectangle CookingStage::getStoveArea() const {
    return stoveArea;
}