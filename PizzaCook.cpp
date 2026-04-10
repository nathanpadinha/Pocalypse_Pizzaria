#include "PizzaCook.hpp"
#include <string>

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

    /**
     * Initialize cooking time values
     */
    cookTime = 0.0f;
    targetCookTime = 10.0f;
    cooking = true;
}

/**
 * Update function for the cooking stage
 * @parm dt Delta time between frames
 * * Currently unused but kept for future cooking logic
 */
void CookingStage::update(float dt) {
    /**
     * Increase the cooking timer while pizza is cooking
     */
    if(cooking && cookTime < targetCookTime) {
        cookTime += dt;
    }

    /**
     * Stop the timer once the pizza is done
     */
    if(cookTime >= targetCookTime) {
        cookTime = targetCookTime;
        cooking = false;
    }
}

/**
 * Draws the stove on the screen
 * * The stove is currently a gray rectangle
 * TODO: Make stove look like an actual grill
 */
void CookingStage::draw() {
    //DrawRectangleRec(stoveArea, GRAY);

    /**
     * Calculate time remaining
     */
    int timeLeft = (int)(targetCookTime - cookTime);
    if(timeLeft < 0) timeLeft = 0;

    /**
     * Convert timer to string
     */
    std::string timerText = "Time Left: " + std::to_string(timeLeft) + "s";

    /**
     * Draw time above stove
     */
    DrawText(timerText.c_str(), 110, 120, 20, BLACK);

    /**
     * Display cooking status
     */
    if(cooking) {
        DrawText("Status: Cooking", 350, 120, 20, ORANGE);
    } else {
        DrawText("Status: Done!", 350, 120, 20, GREEN);
    }
}

/**
 * Returns the stove area
 * * Other classes (Pizza) can use this to position objects
 */
Rectangle CookingStage::getStoveArea() const {
    return stoveArea;
}

/**
 * Returns the amount time the pizza has been cooking
 */
float CookingStage::getCookTime() const {
    return cookTime;
}

/**
 * Returns whether the pizza has finished cooking
 */
bool CookingStage::isFinished() const {
    return cookTime >= targetCookTime;
}