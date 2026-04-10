#include "Pizza.hpp"

Pizza::Pizza() {
    base = 0;
    cookTime = 0;
    numCuts = 0;
    
    position = {400.0f, 400.0f};
    radius = 80.0;

}


//Setter Methods
void Pizza::setBase(int newBase){ base = newBase; }

void Pizza:: setNumCuts(int cuts){ numCuts = cuts; }

void Pizza:: setCookTime(int time){ cookTime = time; }

void Pizza:: addTopping(Topping newTopping){ toppingsList.push_back(newTopping);}

void Pizza::setPosition(Vector2 p) {
    position = p;
}


/*Have outdated branch with no chese or base texture will add when remerged with main
void Pizza::draw() {
    DrawTextureEx(baseTexture, position );
    DrawTextureEx(Cheese, position);
    for (Topping &t : toppingsList){
       t.draw();
    }
    
}
*/

