// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for the enemies bullet logic

#ifndef BOMB_H_
#define BOMB_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Bomb
{
public:
	RectangleShape shape;
    float speed = 2.0f;

    Bomb(Vector2f position) 
    {
        shape.setSize(Vector2f(10.f, 30.f));
        shape.setFillColor(Color::Red);
        shape.setPosition(position);
    }
    
    void getPosition()
    { 
    	cout<<"X : "<<shape.getPosition().x <<" Y : " << shape.getPosition().y <<endl;
    	//return shape.getPosition();
    }


    bool isOutOfBounds() 
    {
        return shape.getPosition().y > 1000;
    }	
    
    void update() {
        shape.move(0.f, speed);

    }

	
	
};

#endif
