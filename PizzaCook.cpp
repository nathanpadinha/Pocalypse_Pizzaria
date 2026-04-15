#include "PizzaCook.hpp"
#include "Constents.hpp"
#include <cmath>
#include <string>
#include <cstdlib>

/**
 * CookingStage Constructor
 * * Initializes the stove area used for cooking pizzas
 * * Defines where the pizza slots and timers appear on the screen
 */
CookingStage::CookingStage() {
    stoveArea = {0.0f, 0.0f, 1600.0f, 900.0f};

    pizzaSlots = {
        Rectangle{90.0f, 180.0f, 455.0f, 340.0f}, // top left
        Rectangle{545.0f, 180.0f, 420.0f, 340.0f}, // top right
        Rectangle{90.0f, 518.0f, 455.0f, 315.0f}, // bottom left
        Rectangle{545.0f, 518.0f, 420.0f, 315.0f} // bottom right
    };

    timerBoxes = {
        Rectangle{26.0f, 243.0f, 81.0f, 84.0f}, // top left
        Rectangle{951.0f, 243.0f, 81.0f, 84.0f}, // top right
        Rectangle{26.0f, 691.0f, 81.0f, 84.0f}, // bottom left
        Rectangle{951.0f, 691.0f, 81.0f, 84.0f} // bottom right
    };

    cookTimes.assign(PIZZA_SLOT_COUNT, 0.0f);
    targetCookTimes.assign(PIZZA_SLOT_COUNT, 7.0f);
    cookingStates.assign(PIZZA_SLOT_COUNT, false);
    pizzaPresent.assign(PIZZA_SLOT_COUNT, false);
}

/**
 * Update function for the cooking stage
 * @param dt
 * * Delta time between frames
 */
void CookingStage::update(float dt) {
    if(!overcharge) {
        if(rand() % OVERCHARGE_CHANCE == 0) {
            overcharge = true;
            overchargeFrameCount = 0;
        }
    } else {
        overchargeFrameCount++;
        if(overchargeFrameCount >= OVERCHARGE_DURATION_FRAMES) {
            overcharge = false;
            overchargeFrameCount = 0;
        }
    }

    float cookMultiplier = overcharge ? OVERCHARGE_COOK_MULTIPLIER : 1.0f;

    for(int i = 0; i < PIZZA_SLOT_COUNT; ++i) {
        if(!pizzaPresent[i] || !cookingStates[i]) {
            continue;
        }
        cookTimes[i] += dt * cookMultiplier;
        if(cookTimes[i] >= targetCookTimes[i]) {
            cookTimes[i] = targetCookTimes[i];
            cookingStates[i] = false;
        }
    }
}

/**
 * Draws the stove on the screen
 * * Draws the grill texture and timer indicators
 * * Timer indicators show how much time is left for each pizza slot
 * * Uses the TextureManager to get the correct textures for the grill and timers
 * * OVERCHARGE MODE: If the stove is overcharged, the cooking speed increases and a visual indicator can be added (not implemented here)
 */
void CookingStage::draw() {
    int occupiedSlots = 0;
    for (bool present : pizzaPresent) {
        if (present) {
            ++occupiedSlots;
        }
    }

    DrawTextureEx(texturemanager.PizzaGrillStates[occupiedSlots], {0.0f, 0.0f}, 0.0f, 25.0f, WHITE);

    for (int i = 0; i < PIZZA_SLOT_COUNT && i < (int)timerBoxes.size(); ++i) {
        int timeLeft = 0;
        if (pizzaPresent[i]) {
            timeLeft = (int)ceilf(targetCookTimes[i] - cookTimes[i]);
            if (timeLeft < 0) {
                timeLeft = 0;
            }
            if (timeLeft > 7) {
                timeLeft = 7;
            }
        }

        Rectangle destination = timerBoxes[i];
        DrawTexturePro(
            texturemanager.TimerDigits[timeLeft],
            Rectangle{0.0f, 0.0f, (float)texturemanager.TimerDigits[timeLeft].width, (float)texturemanager.TimerDigits[timeLeft].height},
            destination,
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE
        );

    }

}

/**
 * Handles mouse clicks on the grill slots
 * * Clicking an empty slot places a pizza
 * * Clicking a cooking pizza stops the timer
 * * Clicking a stopped pizza clears the slot
 */
void CookingStage::handleClick(Vector2 mousePosition) {
    for (int i = 0; i < PIZZA_SLOT_COUNT && i < (int)pizzaSlots.size(); ++i) {
        if (!CheckCollisionPointRec(mousePosition, pizzaSlots[i])) {
            continue;
        }

        if (!pizzaPresent[i]) {
            pizzaPresent[i] = true;
            cookingStates[i] = true;
            cookTimes[i] = 0.0f;
            return;
        }

        if (cookingStates[i]) {
            cookingStates[i] = false;
            return;
        }

        if (!cookingStates[i]) {
            pizzaPresent[i] = false;
            cookTimes[i] = 0.0f;
            return;
        }
    }
}

/**
 * Returns the selected stove slot area
 * * Other classes (Pizza) can use this to position objects
 */
Rectangle CookingStage::getStoveArea(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= (int)pizzaSlots.size()) {
        return stoveArea;
    }
    return pizzaSlots[slotIndex];
}

/**
 * Returns all pizza slot rectangles
 * * Used when drawing pizzas on the grill
 */
const std::vector<Rectangle>& CookingStage::getPizzaSlots() const {
    return pizzaSlots;
}

/**
 * Returns the amount of time the pizza has been cooking
 */
float CookingStage::getCookTime(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= (int)cookTimes.size()) {
        return 0.0f;
    }
    return cookTimes[slotIndex];
}

/**
 * Returns whether the pizza has finished cooking
 * * Uses the timer value for the selected grill slot
 */
bool CookingStage::isFinished(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= (int)cookTimes.size()) {
        return false;
    }
    return pizzaPresent[slotIndex] && cookTimes[slotIndex] >= targetCookTimes[slotIndex];
}

/**
 * Returns whether a pizza is currently on the grill slot
 */
bool CookingStage::hasPizza(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= (int)pizzaPresent.size()) {
        return false;
    }
    return pizzaPresent[slotIndex];
}
