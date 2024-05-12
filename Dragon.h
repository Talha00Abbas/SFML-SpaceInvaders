// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for the final boss, the code is inherited from Enemy base Logic

#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
using namespace sf;

#include <iostream>
using namespace std;


class Dragon : public Enemy
{
public:
	
	float speed=0.3;
	int x,y;
	vector<Bomb> bullets;
	
	Dragon(string png_path)
	{
		tex.loadFromFile("img/dragon2.png");
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.5,0.5);
		shootTime = 3;
		health = 1;
		isDead = false;
		clock.restart(); // Restart the clock for each invader
		moveSpeed = 0.5f;
	}
	
	Dragon(float st, int x, int y) 
	{
		srand (time(0));
		tex.loadFromFile("img/dragon2.png");
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(0.5,0.5);
		shootTime = rand() % (int)st + 1;
		//cout<<"Shoot Time is " <<shootTime<<endl;
		health = 20;
		isDead = false;
		clock.restart(); // Restart the clock for each invader
		moveSpeed = 0.5f;
	}
	
	void checkHealthStatus()
	{
		
		if(health <= 0)
		{
			
			isDead = true;
		}
		
	}
	
	void move() override
	{  	
    	cout<<"X : "<<sprite.getPosition().x<<" Y : " << sprite.getPosition().y <<endl;
    	
		if (!isDead)
		{
		    if (sprite.getPosition().x >= 500)
		    {
		        // Sprite reached the right edge, change direction to move left
		        moveSpeed *= -1;
		    }
		    
		    if (sprite.getPosition().x <= -50)
		    {
		        // Sprite reached the left edge, change direction to move right
		        moveSpeed *= -1;
		    }
		}
		sprite.move(moveSpeed, 0);
		
	}


    void fire(vector<Bomb>& bullets) override
    {
    	if(!isDead)
    	{
			
			if (clock.getElapsedTime().asSeconds() < getShootTime()) 
			{
				
				return;
			}	
			
			//Instantiate the bullet 1
		    Vector2f bulletPosition = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition.x += sprite.getGlobalBounds().width / 2;	
		    	
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition);
		    
		    //////////////////////////
		    
		    
		    //Instantiate the bullet 2
		    Vector2f bulletPosition2 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition2.x += sprite.getGlobalBounds().width / 2 + 50;		
		    
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition2);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 3
		    Vector2f bulletPosition3 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition3.x += sprite.getGlobalBounds().width / 2  + 100;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition3);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 4
		    Vector2f bulletPosition4 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition4.x += sprite.getGlobalBounds().width / 2 + 150;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition4);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 8
		    Vector2f bulletPosition8 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition8.x += sprite.getGlobalBounds().width / 2 + 320;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition8);
		    
		    //////////////////////////
		    
		    
		    //Instantiate the bullet 5
		    Vector2f bulletPosition5 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition5.x += sprite.getGlobalBounds().width / 2 - 50;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition5);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 6
		    Vector2f bulletPosition6 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition6.x += sprite.getGlobalBounds().width / 2 - 100;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition6);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 7
		    Vector2f bulletPosition7 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition7.x += sprite.getGlobalBounds().width / 2 - 150;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition7);
		    
		    //////////////////////////
		    
		    //Instantiate the bullet 9
		    Vector2f bulletPosition9 = sprite.getPosition();
						
		    // Move the Bullet
		    bulletPosition9.x += sprite.getGlobalBounds().width / 2 - 320;		
		    
		    //Put it at the end of the vector graph for destroying		
		    bullets.emplace_back(bulletPosition9);
		    
		    //////////////////////////
		    
		    
		    clock.restart();
        }
    }
	
	int getHealth() const {return health;}
	bool getDead() override {return isDead;}
	
	void setHealth(int h){health = h;}
	
	void reduceHealth(int h){health -= h;	}
	
	float getShootTime(){return shootTime;}
	
private:
	float moveSpeed;
	float shootTime;
	Clock clock; // Non-static Clock variable for each invader
	
};


