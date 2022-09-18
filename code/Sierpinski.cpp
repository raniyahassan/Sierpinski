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
	for (int i = 0; i < points.size(); i+=19)
	{
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

	bool endClicks = true; //Flips to stop user input after maxClicks
	int userClicks = 0; //increments based on users Clicks
	int maxClicks = 3; //Should be either 3 or 4 based on user input, max vertices allowed
	int tempNum = 10; //Used for square function, makes sure random num isn't same as last random num
    Clock clock; 
    
	Font font;

    font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");

    Text text("    Welcome to the Chaos Game. \n\n To begin, click anywhere to create \nthree points to become your vertices. \n       Then select a fourth point.", font);

    text.setCharacterSize(40);
    text.setStyle(sf::Text::Regular);
	text.setPosition(660,2);
    text.setFillColor(Color::White);

	while (window.isOpen())  //Main Loops
	{
        float time = clock.restart().asSeconds();
        float fps = 1.0f / (time);
        std::cout << "fps: " << fps << std::endl; 

		window.clear(); //Clear screen every frame

		window.draw(text); 

		if (Keyboard::isKeyPressed(Keyboard::Escape)) //Esc closes Program
		{
			window.close();
		}

		if (window.pollEvent(event)) //Gets user input for clicks
		{
			//if (event.type == sf::Event::Closed)  //Not sure what this does
				//window.close();

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
				if (maxClicks == 3)
					point = returnTriangle(vertices, point);
				else if (maxClicks == 4)
					point = returnSquare(vertices, point, tempNum);
			}

			drawer(window, rect, point); 

			window.display(); //Display 

	}

	return 0;
}