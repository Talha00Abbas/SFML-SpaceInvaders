// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for START MENU. It shows instructions and starts the first Level

#include "game.h"
using namespace sf;

class Menu
{
	public:

	//add menu attributes here

	void display_menu()
	{
		
        //display menu screen here
        RectangleShape startButton(sf::Vector2f(100, 50));
        startButton.setPosition(350, 275);
        startButton.setFillColor(Color::Green);

        RectangleShape instructionButton(sf::Vector2f(100, 50));
        instructionButton.setPosition(350, 350);
        instructionButton.setFillColor(Color::Yellow);

        RenderWindow window(VideoMode(800, 600), "Main Menu");
		
		window.setFramerateLimit(240);
		
        Font font;
        font.loadFromFile("asd.otf");
        if (!font.loadFromFile("asd.otf"))
        {
            cout << "Failed to load font!" << endl;
        }

        Text startText("Start Game", font, 10);
        startText.setPosition(startButton.getPosition().x + 15, startButton.getPosition().y + 10);
        startText.setFillColor(Color::Black);

        Text instructionText("Instructions", font, 10);
        instructionText.setPosition(instructionButton.getPosition().x + 5, instructionButton.getPosition().y + 10);
        instructionText.setFillColor(Color::Black);

        bool isMainMenuOpen = true;
        

        while (window.isOpen() && isMainMenuOpen)
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        Vector2i mousePosition = Mouse::getPosition(window);
                        if (startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            // Start the game
                            Game g;
                            g.start_game();
                            isMainMenuOpen = false;
                        }
                        else if (instructionButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                        	window.close();
							//display instruction screen here
							
							Font font;
							font.loadFromFile("asd.otf");
							if (!font.loadFromFile("asd.otf"))
							{
								cout << "Failed to load font!" << endl;
								//font.loadFromFile("asd.otf");
							}
							
							Text instructionTitle("Instructions", font, 30);
                            instructionTitle.setPosition(310, 120);
                            instructionTitle.setFillColor(Color::Black);

                            Text instructionContent("Use arrow keys to move. Press spacebar to fire.", font, 20);
                            instructionContent.setPosition(160, 200);
                            instructionContent.setFillColor(Color::Black);
                            
                            
							RectangleShape backButton(sf::Vector2f(100, 50));
							backButton.setPosition(350, 275);
							backButton.setFillColor(Color::Red);



							Text backText("Back", font, 20);
							backText.setPosition(backButton.getPosition().x + 30, backButton.getPosition().y + 10);
							backText.setFillColor(Color::White);

							RenderWindow window(sf::VideoMode(800, 600), "Instruction Menu");
							

							while (window.isOpen())
							{

                            
								Event event;
								while (window.pollEvent(event))
								{
									if (event.type == sf::Event::Closed)
										window.close();

									if (event.type == sf::Event::MouseButtonPressed)
									{
										if (event.mouseButton.button == sf::Mouse::Left)
										{
											sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
											if (backButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
											{
												// Close instruction screen window and return to main menu
												window.close();
												display_menu();
											}
										}
									}
								}

								window.clear(Color::White);

								// Draw your instruction menu here
								window.draw(backButton);
								window.draw(backText);
								window.draw(instructionTitle);
								window.draw(instructionContent);

								window.display();
							}
                        }
                    }
                }
            }
		    window.clear(Color::White);

		    // Draw your main menu here
		    window.draw(startButton);
		    window.draw(instructionButton);
		    
		    // Draw start button text
			window.draw(startText);

			// Draw instruction button text
			window.draw(instructionText);

		    window.display();
    	}

		// add functionality of all the menu options here

		//if Start game option is chosen 
		
		window.close();

	}

};
