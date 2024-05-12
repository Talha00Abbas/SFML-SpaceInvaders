// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for an enemy version JUGGERNAUT(toughest type), the code is inherited from Enemy base Logic

#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
using namespace sf;

#include <iostream>
using namespace std;


class Juggernaut : public Enemy
{
public:
	
	float speed=0.3;
	int x,y;
	vector<Bomb> bullets;
	
	Juggernaut(string png_path)
	{
		tex.loadFromFile("img/enemy_2.png");
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.1,0.1);
		shootTime = 3;
		health = 1;
		isDead = false;
		clock.restart(); // Restart the clock for each invader
	}
	
	Juggernaut(float st, int x, int y) 
	{
		srand (time(0));
		tex.loadFromFile("img/enemy_3.png");
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(0.5,0.5);
		shootTime = rand() % (int)st + 1;
		//cout<<"Shoot Time is " <<shootTime<<endl;
		health = 3;
		isDead = false;
		clock.restart(); // Restart the clock for each invader
	}
	
	void checkHealthStatus()
	{
		
		if(health <= 0)
		{
			
			isDead = true;
		}
		
	}
	
	void move()
	{
		//No need to implement it here 
		cout<<"Called an exception" <<endl;
	}


    void fire(vector<Bomb>& bullets) override
    {
    	if(!isDead)
    	{
			
			if (clock.getElapsedTime().asSeconds() < getShootTime()) 
			{
				
				return;
			}	
			
			//Instantiate the bullet
		    Vector2f bulletPosition = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition.x += sprite.getGlobalBounds().width / 2;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition);
		    clock.restart();
        }
    }
	
	int getHealth() const {return health;}
	bool getDead() override {return isDead;}
	
	void setHealth(int h){health = h;}
	
	void reduceHealth(int h){health -= h;	}
	
	float getShootTime(){return shootTime;}
	
private:
	
	float shootTime;
	Clock clock; // Non-static Clock variable for each invader
	
};


