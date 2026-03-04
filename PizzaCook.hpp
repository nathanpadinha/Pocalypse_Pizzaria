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
     * Returns the rectangle that represents the stove area
     * @return Rectangle containing the stove position and size
     * ? Used by other classes (Pizza) to position pizza on the stove
    */
    Rectangle getStoveArea() const;

private:
    /**
     * Rectangle defining the stove position and dimensions
     * ! Important: This determines where the pizza can cook 
     */
    Rectangle stoveArea;

};
