#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
    VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Sierpinski Triangle", Style::Default);
    RectangleShape rect(Vector2f(10,10)); 

    vector<Vector2f> vertices;
    vector<Vector2f> points; 

    Vector2f clicked;

    while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
     
		while (window.pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    clicked.x = event.mouseButton.x; 
                    clicked.y = event.mouseButton.y; 
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        rect.setPosition(clicked.x, clicked.y);
        rect.setFillColor(Color(255,182,193));

        /*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last run frame
		window.clear();
		// Draw our game scene here
        window.draw(rect); 
		window.display();
    }

    return 0; 
}