#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 

using namespace sf;
using namespace std;


vector<Vector2f> returnTriangle(vector<Vector2f> v, vector<Vector2f> midpoint) //Triangle: Creates midpoint and updates point vector
{
	int randNum = rand() % 3;
	Vector2f temp;

	temp.x = (midpoint[midpoint.size() - 1].x + v[randNum].x) / 2;
	temp.y = (midpoint[midpoint.size() - 1].y + v[randNum].y)/2;
	midpoint.push_back(Vector2f(temp.x, temp.y));

	return midpoint;
};

vector<Vector2f> returnSquare(vector<Vector2f> v, vector<Vector2f> midpoint, int &tempNum) //Square: Creates midpoint and updates point vector
{
	int randNum = rand() % 4;
	Vector2f temp;

	while (tempNum == randNum) //ensures random num isnt same as last random num
		randNum = rand() % 4;

	tempNum = randNum; //updates new random num, passed by reference so saves globally

	temp.x = (midpoint[midpoint.size() - 1].x + v[randNum].x) / 2;
	temp.y = (midpoint[midpoint.size() - 1].y + v[randNum].y) / 2;
	midpoint.push_back(Vector2f(temp.x, temp.y));

	return midpoint;
};

void drawer(RenderWindow& win, RectangleShape rectangle, vector<Vector2f> points)    
{
	for (int i = 0; i < points.size(); i+=21)
	{
		rectangle.setFillColor(Color(223,166,147));
		rectangle.setPosition(points[i].x, points[i].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+1].x, points[i+1].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+2].x, points[i+2].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+3].x, points[i+3].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+4].x, points[i+4].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+5].x, points[i+5].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+6].x, points[i+6].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+7].x, points[i+7].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+8].x, points[i+8].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+9].x, points[i+9].y);
		win.draw(rectangle);

		rectangle.setFillColor(Color(220,110,85)); 
		rectangle.setPosition(points[i+10].x, points[i+10].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+11].x, points[i+11].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+12].x, points[i+12].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+13].x, points[i+13].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+14].x, points[i+14].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+15].x, points[i+15].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+16].x, points[i+16].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+17].x, points[i+17].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+18].x, points[i+18].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+19].x, points[i+19].y);
		win.draw(rectangle);
		rectangle.setPosition(points[i+20].x, points[i+20].y);
		win.draw(rectangle);
	}
}

int main()
{
	srand((int)time(0));

	VideoMode vm(1920, 1080); // Create a video mode object
	RenderWindow window(vm, "Sierpinksi Triangle!!", Style::Default); // Create and open a window for the game
	RectangleShape rect(Vector2f{ 3,3 }); //Set the size of rectangles and color
	rect.setFillColor(Color(255,182,193));

	vector<Vector2f> vertices;//First 3 clicks
	vector<Vector2f> point; //4th click and beyond

	Vector2f clicked; //User clicks
	Event event;

	Font font;

    font.loadFromFile("/usr/share/fonts/opentype/urw-base35/NimbusMonoPS-Regular.otf");

    Text text("WELCOME TO THE CHAOS GAME.", font);

    text.setCharacterSize(45);
    text.setStyle(sf::Text::Regular);
	text.setPosition(600,2);
    text.setFillColor(Color::White);

	Text input("\n\n\n Press 3 to form a triangular fractal. \n  Press 4 to form a square fractal.", font);
	input.setCharacterSize(30);
    input.setStyle(sf::Text::Regular);
	input.setPosition(600,2);
    input.setFillColor(Color::White);

	Text error("\n\nError. Enter 3 or 4.", font);
	error.setCharacterSize(20);
    error.setStyle(sf::Text::Regular);
	error.setPosition(660,2);
    error.setFillColor(Color::White);

	Text three("Triangular Fractal\n Draw your points.", font);
	three.setCharacterSize(45);
    three.setStyle(sf::Text::Regular);
	three.setPosition(720,2);
    three.setFillColor(Color::White);

	Text four("  Square Fractal\n Draw your points.", font); 
	four.setCharacterSize(45);
    four.setStyle(sf::Text::Regular);
	four.setPosition(730,2);
    four.setFillColor(Color::White);

	Text alg("Draw one more point to begin the algorithm.", font); 
	four.setCharacterSize(45);
    four.setStyle(sf::Text::Regular);
	four.setPosition(250,2);
    four.setFillColor(Color::White);

	bool endClicks = true; //Flips to stop user input after maxClicks
	int userClicks = 0; //increments based on users Clicks
	int maxClicks = 0; //Should be either 3 or 4 based on user input, max vertices allowed
	int tempNum = 10; //Used for square function, makes sure random num isn't same as last random num

    // Clock clock; 
	/*float time = clock.restart().asSeconds();
        float fps = 1.0f / (time);
        std::cout << "fps: " << fps << std::endl;  ADD above window.clear() */
    

	while (window.isOpen())  //Main Loops
	{
		window.clear(); 

		window.draw(text);
		window.draw(input); 

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {window.close();}
		if (Keyboard::isKeyPressed(Keyboard::Num3)) {maxClicks = 3;}
		if (Keyboard::isKeyPressed(Keyboard::Num4)) {maxClicks = 4;}

		if (window.pollEvent(event)) //Gets user input for clicks
		{
			if (event.type == Event::MouseButtonPressed && endClicks == true)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
					clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

					if (userClicks < maxClicks) //Three or Four Clicks, stores in two seperate vectors
					{
						vertices.push_back(Vector2f(clicked.x, clicked.y));
						point.push_back(Vector2f(clicked.x, clicked.y));
						userClicks+= 1; //Increment towards maxClicks
					}
					else //Fourth or Fifth Click, bool value flips so algorithm starts and user can no longer click
					{
						point.push_back(Vector2f(clicked.x, clicked.y));
						endClicks = false;
					}
				}
			}
		}
			if (endClicks == false) //Calls algorithm function after user done inputting
			{
				if (maxClicks == 3) {
					window.clear();
					window.draw(three); 
					point = returnTriangle(vertices, point); }
				else if (maxClicks == 4) {
					window.clear();
					window.draw(four);
					point = returnSquare(vertices, point, tempNum); }
			}

			drawer(window, rect, point);
			window.display(); 
	}

	return 0;
}