#pragma once

#include "raylib.h"
#include <vector>

/**
 * Pizza
 * * Represents a pizza object in the game
 * * Stores position, size, and cooking state
 */
class Pizza {
public:
    /**
     * Pizza Constructor
     * * Initializes default pizza properties
     */
    Pizza();

    /**
     * Draws the pizza to the screen
     * * Currently only renders the pizza base
     */
    void draw() const;

    /**
     * Updates pizza cooking logic
     * @param dt Time passed since the last frame
     * TODO: Increase cookTime while pizza is on the stove
     */
    void update(float dt);

    /**
     * Sets the position of the pizza
     * @param p New center position of the pizza
     */
    void setPosition(Vector2 p);

    /**
     * Sets the radius of the pizza
     * @param r New pizza radius
     */
    void setRadius(float r);

    /**
     * Sets the normalized cook progress used for choosing pizza textures.
     * @param progress A value from 0.0 to 1.0
     */
    void setCookProgress(float progress);

private:
    /**
     * Position of the pizza center
     */
    Vector2 position;

    /**
     * Radius of the pizza base
     */
    float radius;

    /**
     * Tracks how long the pizza has been cooking
     * TODO: Use this value to determine undercooked / burnt stages
     */
    float cookTime;

    /**
     * Normalized cooking progress used to select texture stages.
     */
    float cookProgress;
    
};
