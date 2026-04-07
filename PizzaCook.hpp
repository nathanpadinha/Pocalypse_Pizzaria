#include "raylib.h"
#include <vector>

/**
 * CookingStage
 * * Represents the stove area where pizza will be cooked
 * * This class is for updating the cooking logic
 * * and drawing the stove surface on the screen
*/
class CookingStage {
public:
    static constexpr int PIZZA_SLOT_COUNT = 4;

    /**
     * Constructor
     * * Initializes the stove rectangle that shows cooking surface
    */
    CookingStage();

    /**
     * Updates stave logic every frame
     * @param dt
     * * Delta time since the last frame
     * 
     * TODO: implement cooking mechanics here
    */
    void update(float dt);

    /**
     * Draws the stove area
     * @note The stove is currectly shown by a gray rectangle
     * 
     * TODO: Make it look like a real grill
    */
    void draw();

    /**
     * Handles mouse clicks on the pizza slots
     */
    void handleClick(Vector2 mousePosition);

    /**
     * Returns the rectangle that represents the stove area
     * @return Rectangle containing the stove position and size
    * ? Used by other classes (Pizza) to position pizza on the stove
    */
    Rectangle getStoveArea(int slotIndex = 0) const;

    /**
     * Returns all pizza cooking areas on the grill
     */
    const std::vector<Rectangle>& getPizzaSlots() const;

    /**
     * Returns how long the pizza has been cooking
     * @return cookTime
     */
    float getCookTime(int slotIndex = 0) const;

    /**
     * Returns true if the pizza finished cooking
     * @return bool
     */
    bool isFinished(int slotIndex = 0) const;

    /**
     * Returns whether a pizza is currently placed in the slot
     */
    bool hasPizza(int slotIndex = 0) const;

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
     * The four timer boxes the red indicator moves around
     */
    std::vector<Rectangle> timerBoxes;

    /**
     * Independent timers and cooking states for each pizza slot
     */
    std::vector<float> cookTimes;
    std::vector<float> targetCookTimes;
    std::vector<bool> cookingStates;
    std::vector<bool> pizzaPresent;

};
