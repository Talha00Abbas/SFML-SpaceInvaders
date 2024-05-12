// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for player logic and behaviour, also sets the player Highscore

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string.h>
#include <vector>
#include "bullet.h"
using namespace sf;
class Player
{
public:
	Texture tex;
	Sprite sprite;
	float speed=0.7;
	int x,y;
	vector<Bullet> bullets;
	
	Player(string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);
		shootTime = 1;
		maxHealth = 3;
		health = 3;
		isDead = false;
		score = 0;
		
		ifstream file("Highscore.txt");

		if (file.is_open())
		{
		    if (file >> maxScore)
		    {
		        cout << "Highscore read successfully: " << maxScore << std::endl;
		    }
		    else
		    {
		        cout << "Failed to read the highscore from the file." << endl;
		    }
		    file.close();
		}
		else
		{
		    cout << "Failed to open the file." << std::endl;
		}
	}
	
	
	Player(string png_path, float st)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);
		shootTime = st;
		maxHealth = 3;
		health = 3;
		isDead = false;
		score = 0;
		
		ifstream file("Highscore.txt");

		if (file.is_open()) {
		    if (file >> maxScore) {
		        cout << "Highscore read successfully: " << maxScore << std::endl;
		    } else {
		        cout << "Failed to read the highscore from the file." << endl;
		    }
		    file.close();
		} else {
		    cout << "Failed to open the file." << std::endl;
		}
	}
	
	
	void centerPlayer()
	{		
		if (sprite.getPosition().x > 750)
		{
		    sprite.setPosition(0, sprite.getPosition().y);
		}
		
		if (sprite.getPosition().x < -25)
		{
		    sprite.setPosition(700, sprite.getPosition().y);
		}
	}
	
	void checkHealthStatus()
	{
		// Check max health status
		if(health > maxHealth)
		{ 
			health = maxHealth;
		}
		
		if(health <= 0)
		{
			cout<<"Player Died"<<endl;
			isDead = true;
		}
		
	}
	
    void fire(vector<Bullet>& bullets) 
    {
    	if(!isDead)
    	{
			static Clock clock;
			if (clock.getElapsedTime().asSeconds() < shootTime) {
				
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
	
	void move(std::string s)
	{
		float delta_x=0,delta_y=0;
		
		
		if(!isDead)
		{
			if(s=="l")
			{
				//move the player left
				delta_x = -1.5;
				
			}
			else if(s=="r")
			{
				//move the player right
				delta_x = 1.5;
				
			}
			if(s=="u"){
				delta_y=-1;
					
			}
			else if(s=="d"){
				delta_y=1;
					
			}

			delta_x*=speed;
			delta_y*=speed;


			sprite.move(delta_x, delta_y);
			centerPlayer();
		}
	}
	
	//Change Screen to Game over Screen
	
	float getShootTime(){return shootTime;}
	
	void setShootTime(float st){shootTime = st;}
	
	int getHealth(){return health;}
	int getMaxHealth(){return maxHealth;}
	bool getDead(){return isDead;}
	int getScore(){return score; }
	
	void setHealth(int h){health = h;}
	void setMaxHealth(int h){maxHealth = h;}	
	void setScore(int h){score += h; }
	
	void resetScore(){score = 0; }
	
	int getMaxScore(){return maxScore;}
	
	void getHighscore()
    {
        
        ifstream file("Highscore.txt");
        if (file.is_open())
        {
            if (file >> maxScore)
            {
                cout << "Highscore read successfully: " << maxScore << endl;
            }
            else
            {
                cout << "Failed to read the highscore from the file." << endl;
            }
            file.close();
        }
        else
        {
            cout << "Failed to open the file." << endl;
        }
        
    }
	
	void setHighscore()
	{
		getHighscore();
		if (score >= maxScore)
		{
		    ofstream file("Highscore.txt");
		    if (file.is_open())
		    {
		        maxScore = score;
		        file << maxScore << endl;
		        cout << "New highscore set: " << maxScore << endl;
		        file.close();
		    }
		    else
		    {
		        cout << "Failed to open the file to update highscore." << endl;
		    }
		}
	}
	
	void reduceHealth(int h)
	{
		health -= h;
		
	}
	
	int score; 
	int maxScore;

	
	
private:
	float shootTime;
	int health;
	int maxHealth;
	bool isDead;

};
