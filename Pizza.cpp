#include "Pizza.hpp"

/**
 * Pizza constructor
 * * Initializes the pizza position, radius, and cook time
 * 
 * TODO: later the pizza position should be set dynamically based on the cooking stage
 */
Pizza::Pizza() {
    position = {400.0f, 400.0f}; // center for now
    radius = 85.0f;

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
    DrawCircleV(position, radius, BEIGE); // pizza base
}

/**
 * Sets the pizza position
 * @param p
 * * New position for the center of the pizza
 */
void Pizza:: setPosition(Vector2 p) {
    position = p;
}

void Pizza::setRadius(float r) {
    radius = r;
}
