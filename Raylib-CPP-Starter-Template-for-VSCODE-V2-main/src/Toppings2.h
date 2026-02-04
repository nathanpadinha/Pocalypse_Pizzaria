#include "raylib.h"

// Makes one circle (Topping)
struct Topping {
    Vector2 position;  // Where the topping is
    float radius; // How big circle is
    bool active; // true = visible, false = gone
};

void initToppings();

void updateToppings(float deltaTime);

void drawToppings();

#endif;