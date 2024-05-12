// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is main core of the game, this code drives everything from game logic to how enemies, level, player, music will work

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#include "player.h"
#include "enemy.h"
#include "Bomb.h"
#include "Invader.h"
#include "Raider.h"
#include "Juggernaut.h"
#include "Dragon.h"

const string musicFile = "bgm.wav";
const char title[] = "Main Game";
const int MAX_ENEMY = 14;

using namespace sf;

class Game
{
private:
	bool isPaused;	
	Font font;
    Sprite background; //Game background sprite
	Texture bg_texture;

public:
	
	Player* p; //player 
	
	Enemy* inv[MAX_ENEMY];
	
	Game()						// This works as a start function.
	{
		
		
		isPaused = false;
		p = new Player("img/player_ship.png", 0.1);
		bg_texture.loadFromFile("img/background.jpg");
		background.setTexture(bg_texture);
		background.setScale(2, 1.5);
		
		font.loadFromFile("asd.otf");
        if (!font.loadFromFile("asd.otf"))
        {
            cout << "Failed to load font!" << endl;
        }
		
	}
	
	
	void start_game()
	{
		
		//LEVEL 1
		
		int totalPoints = 0;
		
		for (int i = 0; i < MAX_ENEMY; ++i) 
		{
			if(i < 9 && i%2 == 0)
				inv[i] = new Invader(8 + i, 100 * i, 240);
			if(i < 9 && i%2 == 1)
				inv[i] = new Raider(8 + i, 100 * i, 240);
			
			if(i >= 9)
				inv[i] = new Juggernaut(10 + (i - 7), (140 * (i - 8)) - 100, 100);
		
			totalPoints += inv[i]->getHealth();
		}
		cout<<"Total Points Are : " <<totalPoints<<endl;	  
		
		Music music;
		// Load the music from a file
		music.openFromFile(musicFile);
		music.setLoop(true);
		music.play();			//Plays Background Music
		
		srand(time(0));
		RenderWindow window(VideoMode(780, 780), title);
		Clock clock;
		float timer=0;
		
		vector<Bullet> bullets;
		vector<Bomb> bombs;
		
		//Initializing Pause Menu Items
		
		Sprite pauseBackground; //Game background sprite
		Texture pg_texture;
		
		pg_texture.loadFromFile("img/background_1.png");
		pauseBackground.setTexture(pg_texture);
		pauseBackground.setScale(2, 1.5);
		
		Text pausedText("Game Paused", font, 50);
    	pausedText.setFillColor(sf::Color::White);
    	pausedText.setPosition(window.getSize().x / 2 - pausedText.getGlobalBounds().width / 2, window.getSize().y / 2 - pausedText.getGlobalBounds().height / 2 - 100);

    	Text resumeText("Resume", font, 30);
	    resumeText.setFillColor(sf::Color::Red);
    	resumeText.setPosition(window.getSize().x / 2 - resumeText.getGlobalBounds().width / 2, window.getSize().y / 2);

		Text quitText("Quit", font, 30);
		quitText.setFillColor(sf::Color::White);
		quitText.setPosition(window.getSize().x / 2 - quitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);
		
		
		/////////////////////////////////////////////// 
		
		
		while (window.isOpen())
		{
			
		    float time = clock.getElapsedTime().asSeconds(); 
		    clock.restart();
		    timer += time;  
		    //cout<<time<<endl; 
	 		Event e;
		    while (window.pollEvent(e))
		    {  
				if (e.type == Event::Closed) {
		            window.close();
		        }    
		        if (e.type == Event::KeyPressed) {
		            if (e.key.code == Keyboard::Space) {
		                p->fire(bullets);    
		            }
		            if (e.key.code == Keyboard::P) {
		                //Pause the Game
		                isPaused = !isPaused; // Toggle the pause state
		                    
		            }
		        }       
		                   	    
		    }
		    
		    if (isPaused)
			{
				// Draw the pause menu graphics and text
				window.draw(pausedText);
		        window.draw(resumeText);
		        window.draw(quitText);
		        
		        if (e.type == Event::MouseButtonPressed) 
		        {
                	if (e.mouseButton.button == Mouse::Left) 
                	{
                	    
		            	Vector2i mousePos = Mouse::getPosition(window);
		      	        if (resumeText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
			   	        {
		           		     isPaused = false;
		      	        } 
		       	        else if (quitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
		        	    {
		 	  	            window.close();
	  	     	        }              
                	    
                	}
              	}
				// ...
			}
		    
		    if(!isPaused)
		    {
		    
		    	for (int i = 0; i < MAX_ENEMY; ++i) 
				{
					inv[i]->fire(bombs);
				}
				
				// Check for collision between player and bombs
				if (!p->getDead())
				{
					vector<vector<Bomb>::iterator> collidedBombs; // Store iterators of collided bombs

					for (auto bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
					{
						if (p->sprite.getGlobalBounds().intersects(bomb->shape.getGlobalBounds()))
						{
							// Collision detected
							collidedBombs.push_back(bomb);
						}
					}
					
					// Process the collided bombs
					for (const auto& bomb : collidedBombs)
					{
						p->reduceHealth(1);
						p->checkHealthStatus();
						bombs.erase(bomb);
					}
				}
				
				
				for(int i = 0; i < MAX_ENEMY; i++)
				{
					// Check for collision between player bullets and invaders;
					if (!inv[i]->getDead())
					{
						vector<vector<Bullet>::iterator> collidedBullets; // Store iterators of collided bombs

						for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
						{
							if (inv[i]->sprite.getGlobalBounds().intersects(bullet->shape.getGlobalBounds()))
							{
								// Collision detected
								collidedBullets.push_back(bullet);
							}
						}
						
						// Process the collided bombs
						for (const auto& bullet : collidedBullets)
						{
							inv[i]->reduceHealth(1);
							
							inv[i]->checkHealthStatus();
							bullets.erase(bullet);
							p->setScore(1);
						}
					}
				}
				
				
				  
				if (Keyboard::isKeyPressed(Keyboard::A)) //If left key is pressed
						p->move("l");    // Player will move to left
				if (Keyboard::isKeyPressed(Keyboard::D)) // If right key is pressed
						p->move("r");  //player will move to right
				if (Keyboard::isKeyPressed(Keyboard::W)) //If up key is pressed
						p->move("u");    //playet will move upwards
				if (Keyboard::isKeyPressed(Keyboard::S)) // If down key is pressed
						p->move("d");  //player will move downwards
						
				////////////////////////////////////////////////
				/////  Call your functions here            ////
				/////  Here You can call this like update function ////
				p->centerPlayer();

				//////////////////////////////////////////////

				window.clear(Color::Black); //clears the screen
				window.draw(background);  // setting background
				
				
				
			}
			
			if(p->getScore() >= totalPoints - 1)
			{
				cout<<"Level Finished"<<endl;
				window.close();
				start_game2();
				break;
			}
			
			if(p->getDead())
			{
				music.stop();
				window.close();
				p->maxScore = p->score;
				p->setHighscore();
				gameOver();
				cout<<"Player Score was " <<p->score<<endl;
				
				
			}
			
			
			if(!p->getDead())
			{
				window.draw(p->sprite);   // setting player on screen
			}
				
			for (int i = 0; i < MAX_ENEMY; ++i) 
			{
				
				if(!inv[i]->getDead())
				{
					window.draw(inv[i]->sprite);
				}
			}

			
			for (auto& bullet : bullets) 
			{
				bullet.update();
				if (bullet.isOutOfBounds() || isPaused) {
				    bullets.erase(bullets.begin());
				    //cout<<"Player Bullet Went Out of Bounds"<<endl;
				} else {
				    window.draw(bullet.shape);
				}
			}
				
				
				
			for (auto& bomb : bombs) 
			{
				bomb.update();
				if (bomb.isOutOfBounds() || isPaused) {
			    bombs.erase(bombs.begin());
			    //cout<<"Went Out of Bounds"<<endl;
				} else 
				{
			    	window.draw(bomb.shape);
				}
			}				
			
			
			window.display();  //Displying all the sprites
			
		}
	}
	 
	 
	
	void start_game2()
	{
		//LEVEL 2
		int totalPoints = p->getScore();
		
		for (int i = 0; i < MAX_ENEMY; ++i) 
		{
			if(i < 9 && i%2 == 0)
				inv[i] = new Juggernaut(8 + i, 100 * i, 240);
			if(i < 9 && i%2 == 1)
				inv[i] = new Juggernaut(8 + i, 100 * i, 240);
			
			if(i >= 9)
				inv[i] = new Raider(8 + (i - 7), (140 * (i - 8)) - 100, 100);
		
			totalPoints += inv[i]->getHealth();
		}
		system("clear");
		cout<<"Total Points Are : " <<totalPoints<<endl;	  
		
		Music music;
		// Load the music from a file
		music.openFromFile(musicFile);
		music.setLoop(true);
		//music.play();			//Plays Background Music
		
		srand(time(0));
		RenderWindow window(VideoMode(780, 780), "Level 2");
		Clock clock;
		float timer=0;
		
		vector<Bullet> bullets;
		vector<Bomb> bombs;
		
		//Initializing Pause Menu Items
		
		Sprite pauseBackground; //Game background sprite
		Texture pg_texture;
		
		pg_texture.loadFromFile("img/background_1.png");
		pauseBackground.setTexture(pg_texture);
		pauseBackground.setScale(2, 1.5);
		
		Text pausedText("Game Paused", font, 50);
    	pausedText.setFillColor(sf::Color::White);
    	pausedText.setPosition(window.getSize().x / 2 - pausedText.getGlobalBounds().width / 2, window.getSize().y / 2 - pausedText.getGlobalBounds().height / 2 - 100);

    	Text resumeText("Resume", font, 30);
	    resumeText.setFillColor(sf::Color::Red);
    	resumeText.setPosition(window.getSize().x / 2 - resumeText.getGlobalBounds().width / 2, window.getSize().y / 2);

		Text quitText("Quit", font, 30);
		quitText.setFillColor(sf::Color::White);
		quitText.setPosition(window.getSize().x / 2 - quitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);
		
		
		/////////////////////////////////////////////// 
		
		
		while (window.isOpen())
		{
			
		    float time = clock.getElapsedTime().asSeconds(); 
		    clock.restart();
		    timer += time;  
		    //cout<<time<<endl; 
	 		Event e;
		    while (window.pollEvent(e))
		    {  
				if (e.type == Event::Closed) {
					cout << "Score is : " << p->getScore()<<endl;
		            window.close();
		        }    
		        if (e.type == Event::KeyPressed) {
		            if (e.key.code == Keyboard::Space) {
		                p->fire(bullets);    
		            }
		            if (e.key.code == Keyboard::P) {
		                //Pause the Game
		                isPaused = !isPaused; // Toggle the pause state
		                    
		            }
		        }       
		                   	    
		    }
		    
		    if (isPaused)
			{
				// Draw the pause menu graphics and text
				window.draw(pausedText);
		        window.draw(resumeText);
		        window.draw(quitText);
		        
		        if (e.type == Event::MouseButtonPressed) 
		        {
                	if (e.mouseButton.button == Mouse::Left) 
                	{
                	    
		            	Vector2i mousePos = Mouse::getPosition(window);
		      	        if (resumeText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
			   	        {
		           		     isPaused = false;
		      	        } 
		       	        else if (quitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
		        	    {
		 	  	            window.close();
	  	     	        }              
                	    
                	}
              	}
				// ...
			}
		    
		    if(!isPaused)
		    {
		    
		    	for (int i = 0; i < MAX_ENEMY; ++i) 
				{
					inv[i]->fire(bombs);
				}
				
				// Check for collision between player and bombs
				if (!p->getDead())
				{
					vector<vector<Bomb>::iterator> collidedBombs; // Store iterators of collided bombs

					for (auto bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
					{
						if (p->sprite.getGlobalBounds().intersects(bomb->shape.getGlobalBounds()))
						{
							// Collision detected
							collidedBombs.push_back(bomb);
						}
					}
					
					// Process the collided bombs
					for (const auto& bomb : collidedBombs)
					{
						p->reduceHealth(1);
						p->checkHealthStatus();
						bombs.erase(bomb);
					}
				}
				
				
				for(int i = 0; i < MAX_ENEMY; i++)
				{
					// Check for collision between player bullets and invaders;
					if (!inv[i]->getDead())
					{
						vector<vector<Bullet>::iterator> collidedBullets; // Store iterators of collided bombs

						for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
						{
							if (inv[i]->sprite.getGlobalBounds().intersects(bullet->shape.getGlobalBounds()))
							{
								// Collision detected
								collidedBullets.push_back(bullet);
							}
						}
						
						// Process the collided bombs
						for (const auto& bullet : collidedBullets)
						{
							inv[i]->reduceHealth(1);
							
							inv[i]->checkHealthStatus();
							bullets.erase(bullet);
							p->setScore(1);
						}
					}
				}
				
				
				  
				if (Keyboard::isKeyPressed(Keyboard::A)) //If left key is pressed
						p->move("l");    // Player will move to left
				if (Keyboard::isKeyPressed(Keyboard::D)) // If right key is pressed
						p->move("r");  //player will move to right
				if (Keyboard::isKeyPressed(Keyboard::W)) //If up key is pressed
						p->move("u");    //playet will move upwards
				if (Keyboard::isKeyPressed(Keyboard::S)) // If down key is pressed
						p->move("d");  //player will move downwards
						
				////////////////////////////////////////////////
				/////  Call your functions here            ////
				/////  Here You can call this like update function ////
				p->centerPlayer();

				//////////////////////////////////////////////

				window.clear(Color::Black); //clears the screen
				window.draw(background);  // setting background
				
				
				
			}
			
			if(p->getScore() >= 61 )	//61
			{
				cout<<"Level Finished"<<endl;
				window.close();
		
				bossLevel();
				break;
		
			}
			
			if(p->getDead())
			{
				music.stop();
				window.close();
				p->maxScore = p->score;
				p->setHighscore();
				gameOver();
				cout<<"Player Score was " <<p->getScore()<<endl;
				
				
			}
			
			
			if(!p->getDead())
			{
				window.draw(p->sprite);   // setting player on screen
			}
				
			for (int i = 0; i < MAX_ENEMY; ++i) 
			{
				
				if(!inv[i]->getDead())
				{
					window.draw(inv[i]->sprite);
				}
			}

			
			for (auto& bullet : bullets) 
			{
				bullet.update();
				if (bullet.isOutOfBounds() || isPaused) {
				    bullets.erase(bullets.begin());
				    //cout<<"Player Bullet Went Out of Bounds"<<endl;
				} else {
				    window.draw(bullet.shape);
				}
			}
				
				
				
			for (auto& bomb : bombs) 
			{
				bomb.update();
				if (bomb.isOutOfBounds() || isPaused) {
			    bombs.erase(bombs.begin());
			    //cout<<"Went Out of Bounds"<<endl;
				} else 
				{
			    	window.draw(bomb.shape);
				}
			}				
			
			
			window.display();  //Displying all the sprites
			
		}
	}
	
	
	
	void bossLevel()
	{
		//LEVEL 3
		int totalPoints = p->getScore();
		
		for (int i = 0; i < MAX_ENEMY; ++i) 
		{
			if (i == 0)
			{
				inv[i] = new Dragon(8 + i, 250, 50);
			}
			
		
			totalPoints += inv[i]->getHealth();
		}
		system("clear");
		cout<<"Total Points Are : " <<totalPoints<<endl;	  
		
		Music music;
		// Load the music from a file
		music.openFromFile(musicFile);
		music.setLoop(true);
		//music.play();			//Plays Background Music
		
		srand(time(0));
		RenderWindow window(VideoMode(780, 780), "Level 2");
		Clock clock;
		float timer=0;
		
		vector<Bullet> bullets;
		vector<Bomb> bombs;
		
		//Initializing Pause Menu Items
		
		Sprite pauseBackground; //Game background sprite
		Texture pg_texture;
		
		pg_texture.loadFromFile("img/background_1.png");
		pauseBackground.setTexture(pg_texture);
		pauseBackground.setScale(2, 1.5);
		
		Text pausedText("Game Paused", font, 50);
    	pausedText.setFillColor(sf::Color::White);
    	pausedText.setPosition(window.getSize().x / 2 - pausedText.getGlobalBounds().width / 2, window.getSize().y / 2 - pausedText.getGlobalBounds().height / 2 - 100);

    	Text resumeText("Resume", font, 30);
	    resumeText.setFillColor(sf::Color::Red);
    	resumeText.setPosition(window.getSize().x / 2 - resumeText.getGlobalBounds().width / 2, window.getSize().y / 2);

		Text quitText("Quit", font, 30);
		quitText.setFillColor(sf::Color::White);
		quitText.setPosition(window.getSize().x / 2 - quitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);
		
		
		/////////////////////////////////////////////// 
		
		
		while (window.isOpen())
		{
			
		    float time = clock.getElapsedTime().asSeconds(); 
		    clock.restart();
		    timer += time;  
		    //cout<<time<<endl; 
	 		Event e;
		    while (window.pollEvent(e))
		    {  
				if (e.type == Event::Closed) {
					cout << "Score is : " << p->getScore()<<endl;
		            window.close();
		        }    
		        if (e.type == Event::KeyPressed) {
		            if (e.key.code == Keyboard::Space) {
		                p->fire(bullets);    
		            }
		            if (e.key.code == Keyboard::P) {
		                //Pause the Game
		                isPaused = !isPaused; // Toggle the pause state
		                    
		            }
		        }       
		                   	    
		    }
		    
		    if (isPaused)
			{
				// Draw the pause menu graphics and text
				window.draw(pausedText);
		        window.draw(resumeText);
		        window.draw(quitText);
		        
		        if (e.type == Event::MouseButtonPressed) 
		        {
                	if (e.mouseButton.button == Mouse::Left) 
                	{
                	    
		            	Vector2i mousePos = Mouse::getPosition(window);
		      	        if (resumeText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
			   	        {
		           		     isPaused = false;
		      	        } 
		       	        else if (quitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
		        	    {
		 	  	            window.close();
	  	     	        }              
                	    
                	}
              	}
				// ...
			}
		    
		    if(!isPaused)
		    {
		    	inv[0]->move();
		    	for (int i = 0; i < MAX_ENEMY; ++i) 
				{
					inv[i]->fire(bombs);
				}
				
				// Check for collision between player and bombs
				if (!p->getDead())
				{
					vector<vector<Bomb>::iterator> collidedBombs; // Store iterators of collided bombs

					for (auto bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
					{
						if (p->sprite.getGlobalBounds().intersects(bomb->shape.getGlobalBounds()))
						{
							// Collision detected
							collidedBombs.push_back(bomb);
						}
					}
					
					// Process the collided bombs
					for (const auto& bomb : collidedBombs)
					{
						p->reduceHealth(1);
						p->checkHealthStatus();
						bombs.erase(bomb);
					}
				}
				
				
				for(int i = 0; i < MAX_ENEMY; i++)
				{
					// Check for collision between player bullets and invaders;
					if (!inv[i]->getDead())
					{
						vector<vector<Bullet>::iterator> collidedBullets; // Store iterators of collided bombs

						for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
						{
							if (inv[i]->sprite.getGlobalBounds().intersects(bullet->shape.getGlobalBounds()))
							{
								// Collision detected
								collidedBullets.push_back(bullet);
							}
						}
						
						// Process the collided bombs
						for (const auto& bullet : collidedBullets)
						{
							inv[i]->reduceHealth(1);
							
							inv[i]->checkHealthStatus();
							bullets.erase(bullet);
							p->setScore(1);
						}
					}
				}
				
				
				  
				if (Keyboard::isKeyPressed(Keyboard::A)) //If left key is pressed
						p->move("l");    // Player will move to left
				if (Keyboard::isKeyPressed(Keyboard::D)) // If right key is pressed
						p->move("r");  //player will move to right
				if (Keyboard::isKeyPressed(Keyboard::W)) //If up key is pressed
						p->move("u");    //playet will move upwards
				if (Keyboard::isKeyPressed(Keyboard::S)) // If down key is pressed
						p->move("d");  //player will move downwards
						
				////////////////////////////////////////////////
				/////  Call your functions here            ////
				/////  Here You can call this like update function ////
				p->centerPlayer();

				//////////////////////////////////////////////

				window.clear(Color::Black); //clears the screen
				window.draw(background);  // setting background
				
				
				
			}
			
			if(p->getScore() >= 79 )
			{
				cout<<"Level Finished"<<endl;
				music.stop();
				window.close();
				gameWon();
				p->maxScore = p->score;
				p->setHighscore();
				break;
			}
			
			if(p->getDead())
			{
				music.stop();
				window.close();
				gameOver();
				cout<<"Player Score was " <<p->getScore()<<endl;
				p->maxScore = p->score;
				cout<<"Player Score was " <<p->getScore()<<endl;	
				p->setHighscore();
			}
			
			
			if(!p->getDead())
			{
				window.draw(p->sprite);   // setting player on screen
			}
				
			for (int i = 0; i < MAX_ENEMY; ++i) 
			{
				
				if(!inv[i]->getDead())
				{
					window.draw(inv[i]->sprite);
				}
			}

			
			for (auto& bullet : bullets) 
			{
				bullet.update();
				if (bullet.isOutOfBounds() || isPaused) {
				    bullets.erase(bullets.begin());
				    //cout<<"Player Bullet Went Out of Bounds"<<endl;
				} else {
				    window.draw(bullet.shape);
				}
			}
				
				
				
			for (auto& bomb : bombs) 
			{
				bomb.update();
				if (bomb.isOutOfBounds() || isPaused) {
			    bombs.erase(bombs.begin());
			    //cout<<"Went Out of Bounds"<<endl;
				} else 
				{
			    	window.draw(bomb.shape);
				}
			}				
			
			
			window.display();  //Displying all the sprites
			
		}
	}
	
	
	
	
	
	
void gameOver() 
{
    RenderWindow window(sf::VideoMode(800, 600), "Game Over");
    if (!font.loadFromFile("asd.otf")) 
    {
        return;
    }

    Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2 - 200);
    
    Text scoreText("Your Score is " + to_string(p->getScore()), font, 50);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(window.getSize().x / 2 - scoreText.getGlobalBounds().width / 2, window.getSize().y / 2 - scoreText.getGlobalBounds().height / 2 - 100);

    Text maxScoreText("Max Score is " + to_string(p->getMaxScore()), font, 50);
    maxScoreText.setFillColor(Color::White);
    maxScoreText.setPosition(window.getSize().x / 2 - maxScoreText.getGlobalBounds().width / 2, window.getSize().y / 2 - maxScoreText.getGlobalBounds().height / 2);

    sf::Text exitText("Exit", font, 30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            } 
            else if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(Color::Black);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(maxScoreText);
        window.draw(exitText);
        window.display();
    }
}


	
void gameWon() 
{
    RenderWindow window(sf::VideoMode(800, 600), "Game Won");
    if (!font.loadFromFile("asd.otf")) 
    {
        return;
    }

    Text gameOverText("Game Won", font, 50);
    gameOverText.setFillColor(sf::Color::Green);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2 - 200);
    
    Text scoreText("Your Score is " + to_string(p->getScore()), font, 50);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(window.getSize().x / 2 - scoreText.getGlobalBounds().width / 2, window.getSize().y / 2 - scoreText.getGlobalBounds().height / 2 - 100);

    Text maxScoreText("Max Score is " + to_string(p->getMaxScore()), font, 50);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(window.getSize().x / 2 - maxScoreText.getGlobalBounds().width / 2, window.getSize().y / 2 - maxScoreText.getGlobalBounds().height / 2);


    sf::Text exitText("Exit", font, 30);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 2 + 100);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            } 
            else if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(Color::White);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(maxScoreText);
        window.draw(exitText);
        window.display();
    }
}
	


};

