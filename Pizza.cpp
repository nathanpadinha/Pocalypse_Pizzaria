#include "Pizza.hpp"
#include "Constents.hpp"

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
    cookProgress = 0.0f;
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
    Rectangle source = {0.0f, 0.0f, (float)texturemanager.TomatoBase.width, (float)texturemanager.TomatoBase.height};
    Rectangle destination = {position.x, position.y, radius * 2.0f, radius * 2.0f};
    Vector2 origin = {radius, radius};

    int cheeseIndex = (int)roundf(cookProgress * 8.0f);
    if (cheeseIndex < 0) {
        cheeseIndex = 0;
    }
    if (cheeseIndex > 8) {
        cheeseIndex = 8;
    }

    DrawTexturePro(texturemanager.TomatoBase, source, destination, origin, 0.0f, WHITE);
    DrawTexturePro(texturemanager.CheeseStages[cheeseIndex], source, destination, origin, 0.0f, WHITE);
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

void Pizza::setCookProgress(float progress) {
    cookProgress = progress;
    if (cookProgress < 0.0f) {
        cookProgress = 0.0f;
    }
    if (cookProgress > 1.0f) {
        cookProgress = 1.0f;
    }
}
