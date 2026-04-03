#include "Pizza.hpp"

/*
 */
Pizza::Pizza() {
    position = {400.0f, 400.0f}; // center for now
    radius = 80.0f;

    cookTime = 0.0f;
}

/**
 * Updates pizza cooking logic
 * @param dt
 * * Time elapsed since the previous frame
 * TODO: track how long the pizza has been cooking
 */
void Pizza::update(float dt) {
    (void)dt;
}

/**
 * Draws the pizza on the screen
 * TODO: toppings need to be addded
 */
void Pizza::draw() const {
    DrawTextureEx()
}

/**
 * Sets the pizza position
 * @param p
 * * New position for the center of the pizza
 */
void Pizza:: setPosition(Vector2 p) {
    position = p;
}