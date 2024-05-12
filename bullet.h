// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for the player bullet logic

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Bullet
{
public:
    RectangleShape shape;
    float speed = 5.0f;

    Bullet(Vector2f position) 
    {
        shape.setSize(Vector2f(10.f, 20.f));
        shape.setFillColor(Color::Yellow);
        shape.setPosition(position);
    }

    void update() {
        shape.move(0.f, -speed);
    }

    bool isOutOfBounds() {
    
        return shape.getPosition().y < -1000;
    }
    
private:
	  
	 
};

