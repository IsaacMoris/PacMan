#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "setting.h"
#include "ghostmoving.h"
#include "ShortestRandom.h"
#include "pinky.h"
#include "LostWin.h"
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

int maze1[50][50];

int const rows = 28;
int const cols = 28;
int Dir = 0, cnt = 0, fright = 0;
bool vary = 0;
Texture backGround      , pac      , wall      , blinky      ,dot         , bigdot       ,pink;
Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite  , pinkSprite;

Sound eatdot , eatbigdot;
SoundBuffer eatdotBuffer , eatbigdotBuffer;
void declare();
void detectdirection(int x, int y);
void playeranimation(int dir , int cnt);

void settingfn();
void startfn();
void gamefn();
int main()
{
	declare();
	startfn();
}

void declare()
{
	fstream inputStream;
	inputStream.open("maps/map4.txt");
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> maze1[i][j];


	backGround.loadFromFile("img/startbackground.jpg");              // BackGround
	backGroundsprite.setTexture(backGround);
	backGroundsprite.setTextureRect(IntRect(0, 0, 1600, 900));
	backGroundsprite.setColor(Color(255, 255, 255, 64));


	dot.loadFromFile("img/dot.png");                                // dot
	dotSprite.setTexture(dot);

	eatdot.setBuffer(eatdotBuffer);							       // dot sound
	eatdotBuffer.loadFromFile("effects/dot.wav");

	eatbigdot.setBuffer(eatbigdotBuffer);                               // big dot sound
	eatbigdotBuffer.loadFromFile("effects/bigdot.wav");

	bigdot.loadFromFile("img/bigdot.png");                        // big dot
	bigdotSprite.setTexture(bigdot);


	wall.loadFromFile("img/wall.png");                              // Wall
	wallSprite.setTexture(wall);

	pac.loadFromFile("img/sheet.png");                            // PacmMan
	pacSprite.setTexture(pac);
	pacSprite.setPosition(Vector2f(13*32, 16*32));
	pacSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	blinky.loadFromFile("img/blinky.png");                          // Blinky
	blinkySprite.setTexture(blinky);
	blinkySprite.setPosition(Vector2f(448, 448));
	blinkySprite.setTextureRect(sf::IntRect(0, 0, 28, 28));


	pink.loadFromFile("img/g3.png");
	pinkSprite.setTexture(pink);									// pinky 
	pinkSprite.setPosition(Vector2f(448, 448));
	pinkSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void startfn()
{
	RenderWindow startScreen(sf::VideoMode(1600, 900), "Pacman", Style::Close | Style::Resize);
	Menu menu(startScreen.getSize().x, startScreen.getSize().y);


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
					case 0:                        // start game
						startScreen.close();
						gamefn();
						break;

					case 1:                  
						startScreen.close();      // open setting
						settingfn();
						break;

					case 2:
						exit(0);                 // exit game 
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
		startScreen.draw(backGroundsprite);
		menu.draw(startScreen);
		startScreen.display();
	}

}

void settingfn()
{
	sf::RenderWindow settingScreen(sf::VideoMode(1600, 900), "Hello Sfml!");
	Setting setting(settingScreen.getSize().x, settingScreen.getSize().y);

	while (settingScreen.isOpen())
	{
		sf::Event event;
		while (settingScreen.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case::Keyboard::Up:
					setting.MoveUp();
					break;
				case::Keyboard::Down:
					setting.MoveDown();
					break;
				case::Keyboard::Return:
					switch (setting.GetPressedItem())
					{
					case 0:
						cout << "You pressed controls" << endl;
						break;
					case 1:
						cout << "you prssed leader board" << endl;
						break;
					case 2:
						settingScreen.close();
						startfn();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				settingScreen.close();
				break;
			}
		}
		settingScreen.clear();
		settingScreen.draw(backGroundsprite);
		setting.draw(settingScreen);
		settingScreen.display();
	}
}



void gamefn()
{

	RenderWindow pacman(VideoMode(1600, 900), "Pacman");

	LostWin oo;
	ghostmoving obj(maze1, cols, rows);
	ShortestRandom pn(maze1, cols, rows);
	int xx = 0, yy = 0;
	pacman.setFramerateLimit(10);

		//sf::sleep(sf::milliseconds(80));
	// Besh

	bool move_ch = 1; int Besh_x = 0, Besh_y = 0;
	while (pacman.isOpen())
	{
		if (pacSprite.getGlobalBounds().intersects(blinkySprite.getGlobalBounds()))
		{
			//oo.soundlost();
			oo.lost(pacman);
			sleep(sf::milliseconds(10));
		}
		cnt = (cnt + 1) % 7;
		Event event;
		while (pacman.pollEvent(event))
		{
			if (event.type == Event::Closed)
				pacman.close();
			if (Keyboard::isKeyPressed(Keyboard::Right))
				xx = 32,  yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Left))
				xx = -32, yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Up))
				yy = -32, xx = 0;
			if (Keyboard::isKeyPressed(Keyboard::Down))
				yy =  32, xx = 0;
			//Besh
			if (move_ch)
			{
				Besh_x = xx;
				Besh_y = yy;
				move_ch = 0;
			}
		}
		playeranimation(Dir,cnt);
		if (pacSprite.getPosition().x < 0)
			pacSprite.setPosition(896, pacSprite.getPosition().y);
		if (pacSprite.getPosition().x > 896)
			pacSprite.setPosition(0, pacSprite.getPosition().y);

		int y = (pacSprite.getPosition().x + xx) / 32;
		int x = (pacSprite.getPosition().y + yy) / 32;

		int Besh_gety = (pacSprite.getPosition().x + Besh_x) / 32;
		int Besh_getx = (pacSprite.getPosition().y + Besh_y) / 32;

		if (maze1[x][y] != 1) {
			pacSprite.move(xx, yy), Besh_x = xx, Besh_y = yy;
			detectdirection(xx, yy);
		}


		else if (maze1[Besh_getx][Besh_gety] != 1)
		{
			//Besh_x = 0; Besh_y = 0;
			pacSprite.move(Besh_x, Besh_y);
			//	continue;
			detectdirection(Besh_x, Besh_y);
		}

		else
		{
			pacSprite.move(0, 0);
			xx = yy = 0;
		}
		pacman.clear();

		if (fright == 0)
			blinkySprite = obj.findpath(pacSprite, blinkySprite);
		else
			fright--;

		pn.short_with_tiles(pacSprite, pinkSprite);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				int pacx = pacSprite.getPosition().x / 32, pacy = pacSprite.getPosition().y / 32;
				if (maze1[i][j] == 1)
				{
					wallSprite.setTextureRect(IntRect(0, 0, 32, 32));
					wallSprite.setPosition(j * 32, i * 32);
					pacman.draw(wallSprite);
				}
				else if (maze1[i][j] == 2)
				{
					dotSprite.setTextureRect(IntRect(0, 0, 16, 16));
					dotSprite.setColor(Color::Red);
					dotSprite.setPosition(j * 32+8, i * 32+8);
					pacman.draw(dotSprite);
					if (pacx == j && pacy == i)
					{
						maze1[i][j] = 0;
						if (eatdot.getStatus() == Music::Status::Stopped)
						eatdot.play();
					}
				}
				else if (maze1[i][j] == 3)
				{
					bigdotSprite.setTextureRect(IntRect(0, 0, 32, 32));
					bigdotSprite.setPosition(j * 32, i * 32);
					pacman.draw(bigdotSprite);
					if (pacx == j && pacy == i) 
					{
						maze1[i][j] = 0, fright = 10;
						if (eatbigdot.getStatus() == Music::Status::Stopped)
							eatbigdot.play();
					}
				}

			}
		pacman.draw(blinkySprite);
		pacman.draw(pinkSprite);
		pacman.draw(pacSprite);
		pacman.display();
	}
}
void playeranimation(int dir, int cnt)
{
	pacSprite.setTextureRect(IntRect(cnt * 32, dir * 32, 32, 32));
}

void detectdirection(int x, int y)
{
	if (x == 32)
		Dir = 0;
	if (x == -32)
		Dir = 2;
	if (y == 32)
		Dir = 1;
	if (y == -32)
		Dir = 3;
}