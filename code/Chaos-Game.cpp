// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 

using namespace sf;
using namespace std;

void returnTriangle(vector<Vector2f>& vertices, vector<Vector2f>& midpoint); //Triangle: Creates midpoint and updates point vector
void returnSquare(vector<Vector2f>& vertices, vector<Vector2f>& midpoint, int& tempNum); //Square: Creates midpoint and updates point vector
void returnPentagon(vector<Vector2f>& vertices, vector<Vector2f>& midpoint, int& tempNum); //Square: Creates midpoint and updates point vector
void draw(RenderWindow& win, RectangleShape rectangle, vector<Vector2f> points, string color);

int main()
{
	srand((int)time(0));
	int width = 1920;
	int height = 1080;
	Vector2f origin = {-440,2};
	VideoMode vm(width, height); // Create a video mode object
	RenderWindow window(vm, "Sierpinksi Triangle!!", Style::Default); // Create and open a window for the game
	RectangleShape rect(Vector2f{ 1,1 }); //Set the size of rectangles and color
	rect.setFillColor(Color::Magenta);


	vector<Vector2f> vertices;//First 3 clicks
	vector<Vector2f> point; //4th click and beyond

	Vector2f clicked; //User clicks
	Event event;

	bool endClicks = true; //Flips to stop user input after maxClicks
	bool endShape = true; //Flips after user chooses shape

	int userClicks = 0; //increments based on users Clicks
	int maxClicks = 0; //Sets max number of clicks based on fractal choice
	int tempNum = 10; //Used for functions Square and Pentagon, makes sure random num isn't same as last random num
	int speed = 75;
	string color = ""; 

	Font font; //load text, set font
	Font font2;
	if (!font.loadFromFile("font/RobotoMono-Medium.ttf"))
	{
	    cout << "Error loading font";
	}
	if (!font2.loadFromFile("font/RobotoMono-Bold.ttf"))
	{
	    cout << "Error loading font";
	}
	Text text;
	text.setFont(font);
	text.setOrigin(-330,-400); 
	text.setString("WELCOME TO THE CHAOS GAME.");
	text.setCharacterSize(85);
	text.setFillColor(Color::White);
	Text text2;
	text2.setFont(font2);
	text2.setOrigin(-730,-550); 
	text2.setString("press the spacebar to continue");
	text2.setCharacterSize(25);
	text2.setFillColor(Color::White);

	

	while (window.isOpen())  //Main Loop
	{
		window.clear(); //Clear screen every frame

		if (Keyboard::isKeyPressed(Keyboard::Escape)) //Esc closes Program
		{
			window.close();
		}

		while (window.pollEvent(event)) //Gets user input for clicks and shape
		{
			if (event.type == Event::KeyPressed)
			{
				text.setCharacterSize(45);
				text.setOrigin(-385,-400);
				text.setString("What color fractal would you like to draw?\n             Enter P for Pink.\n             Enter B for Blue.\n             Enter G for Green.");
				text2.setString(""); 
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::P) {color += "P"; }
					if (event.key.code == Keyboard::B) {color += "B"; }
					if (event.key.code == Keyboard::G) {color += "G"; }
				}
			}
			if (event.type == Event::KeyPressed && (color == "P" || color == "B" || color == "G"))
			{
				text.setCharacterSize(45);
				text.setOrigin(-460,-400);
				text.setString("Enter 1 to draw a triangular fractal.\n  Enter 2 to draw a square fractal.\nEnter 3 to draw a pentagonal fractal.");
				if (event.type == Event::KeyPressed && endShape == true)
				{
					text2.setOrigin(-5,-1040);
					text2.setCharacterSize(22); 
					text2.setString("click esc at any time to exit the program"); 
					if (event.key.code == Keyboard::Num1)
					{
						cout << "User entered 1" << endl;
						maxClicks = 3;
						endShape = false;
						text.setOrigin(-740,2);
						text.setString("Draw 3 vertices.");
						
					}
					if (event.key.code == Keyboard::Num2)
					{
						cout << "User entered 2" << endl;
						maxClicks = 4;
						endShape = false;
						text.setOrigin(-740,2);
						text.setString("Draw 4 vertices.");
						
					}
					if (event.key.code == Keyboard::Num3)
					{
						cout << "User entered 3" << endl;
						maxClicks = 5;
						endShape = false;
						text.setOrigin(-740,2);
						text.setString("Draw 5 vertices.");
					}
						
				}
			}
			if (event.type == Event::MouseButtonPressed && endClicks == true && endShape == false)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

					if (userClicks < maxClicks) //Three or Four Clicks, stores in two seperate vectors
					{
						vertices.push_back(Vector2f(clicked.x, clicked.y));
						point.push_back(Vector2f(clicked.x, clicked.y));
						userClicks++; //Increment towards maxClicks
						if ((userClicks) == maxClicks)
						{
							text.setOrigin(-370,2); 
							text.setString("Draw a final midpoint to start the algorithm.");
						}
					}
					else //Fourth or Fifth Click, bool value flips so algorithm starts and user can no longer click
					{
						point.push_back(Vector2f(clicked.x, clicked.y));
						endClicks = false;
					}
				}
			}
		}

		if (endClicks == false) //Calls algorithm functions after user done inputting
		{
			if (maxClicks == 3)
			{
				for (int i = 0; i <= speed; i++)
					returnTriangle(vertices, point);
			}
			else if (maxClicks == 4)
			{
				for (int i = 0; i <= speed; i++)
					returnSquare(vertices, point, tempNum);
			}
			else if (maxClicks == 5)
			{
				for (int i = 0; i <= speed; i++)
					returnPentagon(vertices, point, tempNum);
			}
		}

		draw(window, rect, point, color);

		window.draw(text); //Draw text 
		window.draw(text2);
		window.display(); //Display 

	}
	return 0;
}

void draw(RenderWindow& win, RectangleShape rectangle, vector<Vector2f> points, string color)
{
	if (color == "P") {rectangle.setFillColor(Color(244,194,194));}
	if (color == "B") {rectangle.setFillColor(Color(145,205,230));}
	if (color == "G") {rectangle.setFillColor(Color(175,222,183));}
	for (int i = 0; i < points.size(); i++) //Draws every point stored in point vector
		{
			rectangle.setPosition(points[i].x, points[i].y);
			win.draw(rectangle);
		}
};

void returnTriangle(vector<Vector2f>& vertices, vector<Vector2f>& midpoint) //Triangle: Creates midpoint and updates point vector
{
	int randNum = rand() % 3;
	Vector2f temp;

	temp.x = (midpoint[midpoint.size() - 1].x + vertices[randNum].x) / 2;
	temp.y = (midpoint[midpoint.size() - 1].y + vertices[randNum].y) / 2;
	midpoint.push_back(Vector2f(temp.x, temp.y));
};

void returnSquare(vector<Vector2f>& vertices, vector<Vector2f>& midpoint, int& tempNum) //Square: Creates midpoint and updates point vector
{
	int randNum = rand() % 4;
	Vector2f temp;

	while (tempNum == randNum) //ensures random num isnt same as last random num
		randNum = rand() % 4;

	tempNum = randNum; //updates new random num, passed by reference so saves globally

	temp.x = (midpoint[midpoint.size() - 1].x + vertices[randNum].x) / 2;
	temp.y = (midpoint[midpoint.size() - 1].y + vertices[randNum].y) / 2;
	midpoint.push_back(Vector2f(temp.x, temp.y));
};

void returnPentagon(vector<Vector2f>& vertices, vector<Vector2f>& midpoint, int& tempNum) //Square: Creates midpoint and updates point vector
{
	int randNum = rand() % 5;
	Vector2f temp;

	while (tempNum == randNum) //ensures random num isnt same as last random num
		randNum = rand() % 5;

	tempNum = randNum; //updates new random num, passed by reference so saves globally
	temp.x = (midpoint[midpoint.size() - 1].x + vertices[randNum].x) / 2;
	temp.y = (midpoint[midpoint.size() - 1].y + vertices[randNum].y) / 2;
	midpoint.push_back(Vector2f(temp.x, temp.y));
};
