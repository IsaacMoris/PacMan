#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;
int const rows = 31;
int const cols = 28;
int main()
{
	int map4[rows][cols];
	fstream inputStream;
	inputStream.open("maps/map4.txt");
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> map4[i][j];


	RenderWindow startScreen(sf::VideoMode(1600, 900), "Pacman", Style::Close | Style::Resize);
	Menu menu(startScreen.getSize().x, startScreen.getSize().y);


	Texture backGround;
	backGround.loadFromFile("img/startbackground.jpg");
	Sprite sprite;
	sprite.setTexture(backGround);
	sprite.setTextureRect(IntRect(0, 0, 1600, 900));
	sprite.setColor(Color(255, 255, 255, 64));


	while (startScreen.isOpen())
	{
		Event event;

		while (startScreen.pollEvent(event))
		{

			switch (event.type)
			{
				//---------------------(Control on Moving in The start Menu  )-------------------
			case Event::KeyReleased:

				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;
					//----------------------------------(Control on The Return value )---------------------------
				case Keyboard::Return:

					switch (menu.GetPressedItem())
					{
					case 0:
						startScreen.close();
						break;

					case 1:
						cout << "Settings button has been pressed " << endl;
						break;

					case 2:
						exit(0);
						break;
					}

					break;
				}

				break;
				//---------------------------------------------------------------------------
			case Event::Closed:
				startScreen.close();
				break;
				//---------------------------------------------------------------------------
			}
		}


		startScreen.clear();
		startScreen.draw(sprite);
		menu.draw(startScreen);
		startScreen.display();
	}





	RenderWindow pacman(VideoMode(1600, 900), "Pacman");
	Texture player;
	player.loadFromFile("img/pac.png");
	Sprite player_s(player);
	player_s.setPosition(Vector2f(32, 32));
	player_s.setTextureRect(sf::IntRect(0, 4, 28, 28));

	Texture wall;
	wall.loadFromFile("img/wall.png");
	Sprite wall_s(wall);


	while (pacman.isOpen())
	{
		Event event;
		while (pacman.pollEvent(event))
		{
			if (event.type == Event::Closed)
				pacman.close();
		}
		pacman.clear();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (map4[i][j] == 1) {
					wall_s.setTextureRect(IntRect(0, 0, 40, 40));
					wall_s.setPosition(j * 40, i * 40);
					pacman.draw(wall_s);
				}
				if (player_s.getGlobalBounds().intersects(wall_s.getGlobalBounds()))
				{

				}
			}

		pacman.draw(player_s);
		pacman.display();
	}


}









