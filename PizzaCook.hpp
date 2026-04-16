#include "raylib.h"
#include <vector>
#include "Pizza.hpp"

/**
 * CookingStage
 * * Represents the stove area where pizza will be cooked
 * * This class is for updating the cooking logic
 * * and drawing the stove surface on the screen
*/
class CookingManager {
public:
    static constexpr int PIZZA_SLOT_COUNT = 4;
    int TimerTimes[4];
    bool TimersActive[4];
    /**
     * Constructor
     * * Initializes the stove rectangle, pizza slots,
     * * and timer positions for the cooking screen
    */
    CookingManager();

    /**
     * Updates stove logic every frame
     * @param dt
     * * Delta time since the last frame
    */
    void update(int dayTimeFrame, Pizza PizzaList[]);

    /**
     * Draws the stove area
     * * Draws the grill background and the timer indicators
    */
    void drawTimers();

    /**
     * Handles mouse clicks on the pizza slots
     * @param mousePosition
     * * Current mouse position used to place, stop,
     * * or clear pizzas from the grill
     */
    void handleClick(Vector2 mousePosition);

    /**
     * Returns the rectangle that represents one grill slot
     * @param slotIndex
     * * Which pizza slot to read from the cooking stage
     * @return Rectangle containing the slot position and size
    */
    Rectangle getStoveArea(int slotIndex = 0) const;

    /**
     * Returns all pizza cooking areas on the grill
     * @return Vector of pizza slot rectangles
     */
    const std::vector<Rectangle>& getPizzaSlots() const;

    /**
     * Returns how long the pizza has been cooking
     * @param slotIndex
     * * Which pizza slot timer to read
     * @return cookTime for the selected slot
     */
    float getCookTime(int slotIndex = 0) const;

    /**
     * Returns true if the pizza finished cooking
     * @param slotIndex
     * * Which pizza slot to check
     * @return bool
     */
    bool isFinished(int slotIndex = 0) const;

    /**
     * Returns whether a pizza is currently placed in the slot
     * @param slotIndex
     * * Which pizza slot to check
     * @return bool
     */
    bool hasPizza(int slotIndex = 0) const;


    bool overcharge = false;


private:
    /**
     * Rectangle defining the stove position and dimensions
     * ! Important: This determines where the pizza can cook 
     */
    Rectangle stoveArea;

    /**
     * The four places where pizzas can be drawn on the grill
     */
    std::vector<Rectangle> pizzaSlots;

    /**
     * The four timer boxes where the timer textures are drawn
     */
    std::vector<Rectangle> timerBoxes;

    /**
     * Independent timers and cooking states for each pizza slot
     * * Each vector index matches the same pizza slot on the grill
     */
    std::vector<float> cookTimes;
    std::vector<float> targetCookTimes;
    std::vector<bool> cookingStates;
    std::vector<bool> pizzaPresent;

    /**
     * Overcharge mechanic variables
     * * When the stove is overcharged, cooking speed increases for a short duration
     * * This adds a risk/reward element to cooking where players can speed up cooking
     */
    int overchargeFrameCount = 0;

    static constexpr int OVERCHARGE_DURATION_FRAMES = 180;
    // static constexpr int OVERCHARGE_CHANCE = 1200;
    static constexpr int OVERCHARGE_COOK_MULTIPLIER = 3;

};
