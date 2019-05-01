#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "ghostmoving.h"
#include "ShortestRandom.h"
#include "scoreboard.h"
#include "Besh_Random.h"
#include "LostWin.h"
#include <SFML/Window.hpp>
#include <string>
using namespace sf;
using namespace std;

scoreboard score_board;

int maze1[50][50];

int score = 0;//Abnb
int lives = 3;//Abnb
bool mood = false;   //Mood --> Chase
bool Abnb_check1 = false;
bool Abnb_check2 = false;

int const rows = 28;
int const cols = 28;
int Dir = 0, cnt = 0, fright = 0;
bool vary = 0;
Texture backGround, pac, wall, blinky, dot, bigdot, pink;
Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkSprite;

Texture backgr, lives_pacman1, lives_pacman2, lives_pacman3, lives_pacman4, lives_pacman5, inky, clyde;
Sprite  backgr_score, lives_pacman_sprite1, lives_pacman_sprite2, lives_pacman_sprite3, lives_pacman_sprite4, lives_pacman_sprite5, inkySprite, clydeSprite;

Sound eatdot, eatbigdot;
SoundBuffer eatdotBuffer, eatbigdotBuffer;


Text  text_score, text, control, control1, control2, control3, control4;
Font font, fon, fo;
string s;
void declare();
void detectdirection(int x, int y);
void playeranimation(int dir, int cnt);
int pac_diffPOS(int curr_pac_speed, int pacman_speed);

void enterusernamefn();

void startfn();
void gamefn(int pacman_speed);
void scoreBoardfn();
void draw_your_maze();

void Return_game_to_the_start();

int main()
{
	declare();
	//enterusernamefn();
	startfn();
}

void declare()
{
	fstream inputStream;
	inputStream.open("maps/map1.txt");
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> maze1[i][j];


	backGround.loadFromFile("img/startbackground.jpg");              // BackGround
	backGroundsprite.setTexture(backGround);
	backGroundsprite.setTextureRect(IntRect(0, 0, 1600, 900));
	backGroundsprite.setColor(Color(255, 255, 255, 64)); //255 64



	backgr.loadFromFile("img/Back__Score.png");              // BackGround for score that exist in the right part of window 
	backgr_score.setTexture(backgr);
	backgr_score.setColor(Color(255, 255, 255, 64));
	backgr_score.setPosition(Vector2f(896, 0));


	dot.loadFromFile("img/dot.png");                                // dot
	dotSprite.setTexture(dot);

	eatdot.setBuffer(eatdotBuffer);							       // dot sound
	eatdotBuffer.loadFromFile("effects/dot.wav");

	eatbigdot.setBuffer(eatbigdotBuffer);                               // big dot sound
	eatbigdotBuffer.loadFromFile("effects/bigdot.wav");

	bigdot.loadFromFile("img/bigdot.png");                        // big dot
	bigdotSprite.setTexture(bigdot);


	wall.loadFromFile("img/wall.jpg");                              // Wall
	wallSprite.setTexture(wall);

	pac.loadFromFile("img/sheet.png");                            // PacmMan
	pacSprite.setTexture(pac);
	pacSprite.setPosition(Vector2f(448, 704));
	pacSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	blinky.loadFromFile("img/blinky.png");                          // Blinky
	blinkySprite.setTexture(blinky);
	blinkySprite.setPosition(Vector2f(384, 416));
	blinkySprite.setTextureRect(sf::IntRect(0, 0, 28, 28));


	pink.loadFromFile("img/g3.png");
	pinkSprite.setTexture(pink);									// pinky 
	pinkSprite.setPosition(Vector2f(416, 416));
	pinkSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	inky.loadFromFile("img/g1.png");
	inkySprite.setTexture(inky);									// inky 
	inkySprite.setPosition(Vector2f(448, 416));
	inkySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	clyde.loadFromFile("img/g4.png");
	clydeSprite.setTexture(clyde);									// clyde
	clydeSprite.setPosition(Vector2f(480, 416));
	clydeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));


	///////////////////////////////////////// The Right part of the window 

	if (!font.loadFromFile("font/MotionPicture_PersonalUseOnly.ttf"))
		cout << "Error" << endl;

	if (!fon.loadFromFile("font/Heavy-Metal-Rocking.ttf"))
		cout << "Error" << endl;

	if (!fo.loadFromFile("font/ARIAL.ttf"))
		cout << "Error" << endl;


	text_score.setFont(fo);
	text_score.setPosition(1056, 128);
	text_score.setFillColor(Color::White);
	text_score.setStyle(Text::Bold);
	text_score.setCharacterSize(80);
	text_score.setString("Score : ");  //To print word "Score"

	text.setFont(fo);
	text.setPosition(1400, 160); //1248
	text.setFillColor(Color::Blue);
	text.setStyle(Text::Bold);
	text.setString(s);                 //To print the score 


	control.setFont(fon);
	control.setPosition(1056, 416);
	control.setFillColor(Color::White);
	control.setStyle(Text::Bold);
	control.setCharacterSize(45);
	control.setString("Controls ");

	control1.setFont(font);
	control1.setPosition(960, 480);
	control1.setFillColor(Color::Green);
	control1.setString("Arrow Keys For Pacman");

	control2.setFont(font);
	control2.setPosition(960, 544);
	control2.setFillColor(Color::Green);
	control2.setString("P --> Pause/UnPause");

	control3.setFont(font);
	control3.setPosition(960, 608);
	control3.setFillColor(Color::Green);
	control3.setString("M --> Mute/UnMute Sound");

	control4.setFont(font);
	control4.setPosition(960, 672);
	control4.setFillColor(Color::Green);
	control4.setString("Esc --> Exit ");


	//------------------------------------------------------ lives --------

	lives_pacman1.loadFromFile("img/live.png");
	lives_pacman_sprite1.setTexture(lives_pacman1);
	lives_pacman_sprite1.setColor(Color::Yellow);
	lives_pacman_sprite1.setPosition(Vector2f(864 + 64, 288));
	lives_pacman_sprite1.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman2.loadFromFile("img/live.png");
	lives_pacman_sprite2.setTexture(lives_pacman2);
	lives_pacman_sprite2.setColor(Color::Yellow);
	lives_pacman_sprite2.setPosition(Vector2f(864 + 64 * 2, 288));
	lives_pacman_sprite2.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman3.loadFromFile("img/live.png");
	lives_pacman_sprite3.setTexture(lives_pacman3);
	lives_pacman_sprite3.setColor(Color::Yellow);
	lives_pacman_sprite3.setPosition(Vector2f(864 + 64 * 3, 288));
	lives_pacman_sprite3.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman4.loadFromFile("img/live.png");
	lives_pacman_sprite4.setTexture(lives_pacman4);
	lives_pacman_sprite4.setColor(Color::Yellow);
	lives_pacman_sprite4.setPosition(Vector2f(864 + 64 * 4, 288));
	lives_pacman_sprite4.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman5.loadFromFile("img/live.png");
	lives_pacman_sprite5.setTexture(lives_pacman5);
	lives_pacman_sprite5.setColor(Color::Yellow);
	lives_pacman_sprite5.setPosition(Vector2f(864 + 64 * 5, 288));
	lives_pacman_sprite5.setTextureRect(sf::IntRect(0, 0, 64, 64));
	///////////////////////////////////////////////////////////////////
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
						gamefn(2);
						break;

					case 1:
						startScreen.close();      // open setting
						scoreBoardfn();
						break;

					case 2:
						startScreen.close();
						draw_your_maze();                // maze 
						break;

					case 3:
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
		menu.draw(startScreen);
		startScreen.draw(backGroundsprite);
		startScreen.display();
	}

}
int pac_diffPOS(int curr_pac_speed, int pacman_speed)
{
	int diff = 0;
	if (curr_pac_speed > 0)  diff = 32 - pacman_speed;
	else if (curr_pac_speed < 0)  diff = -32 + pacman_speed;
	else diff = 0;

	return diff;
}

void gamefn(int pacman_speed)
{
	
	Return_game_to_the_start();
	RenderWindow pacman(VideoMode(1600, 900), "Pacman");


	LostWin oo;
	ghostmoving blinky(maze1, cols, rows, 2);
	ShortestRandom pinky(maze1, cols, rows, 2);
	Besh_Random inky, clyde;
	int xx = 0, yy = 0;
	pacman.setFramerateLimit(100);
	// Besh
	bool move_ch = 1; int Besh_x = 0, Besh_y = 0;
	while (pacman.isOpen())
	{
		//Abnb
		if (pacSprite.getGlobalBounds().intersects(blinkySprite.getGlobalBounds()))
		{
			if (!mood)      //Mood --> Chase  
			{
				lives--;
				Return_game_to_the_start();
			}

		}
		if (pacSprite.getGlobalBounds().intersects(pinkSprite.getGlobalBounds()))
		{
			if (!mood)     //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
		}
		if (pacSprite.getGlobalBounds().intersects(inkySprite.getGlobalBounds()))
		{
			if (!mood)      //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
		}
		if (pacSprite.getGlobalBounds().intersects(clydeSprite.getGlobalBounds()))
		{
			if (!mood)      //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
		}

		cnt = (cnt + 1) % 7;

		
		s = to_string(score);
		text.setString(s);

		Event event;
		while (pacman.pollEvent(event))
		{
			if (event.type == Event::Closed)
				pacman.close();
			if (Keyboard::isKeyPressed(Keyboard::Right))
				xx = pacman_speed, yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Left))
				xx = -pacman_speed, yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Up))
				yy = -pacman_speed, xx = 0;
			if (Keyboard::isKeyPressed(Keyboard::Down))
				yy = pacman_speed, xx = 0;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pacman.close();
				startfn();
			}
			//Besh
			if (move_ch)
			{
				Besh_x = xx;
				Besh_y = yy;
				move_ch = 0;
			}
		}
		playeranimation(Dir, cnt);
		if (pacSprite.getPosition().x < 0)
			pacSprite.setPosition(896, pacSprite.getPosition().y);
		if (pacSprite.getPosition().x > 896)
			pacSprite.setPosition(0, pacSprite.getPosition().y);



		int y = (pacSprite.getPosition().x + xx + pac_diffPOS(xx, pacman_speed)) / 32;
		int x = (pacSprite.getPosition().y + yy + pac_diffPOS(yy, pacman_speed)) / 32;

		int Besh_gety = (pacSprite.getPosition().x + Besh_x + pac_diffPOS(Besh_x, pacman_speed)) / 32;
		int Besh_getx = (pacSprite.getPosition().y + Besh_y + pac_diffPOS(Besh_y, pacman_speed)) / 32;

		int xmod = pacSprite.getPosition().y, ymod = pacSprite.getPosition().x;


		if (!(xmod % 32) && !(ymod % 32))
		{

			if (maze1[x][y] != 1) {
				pacSprite.move(xx, yy), Besh_x = xx, Besh_y = yy;
				detectdirection(xx, yy);
			}


			else if (maze1[Besh_getx][Besh_gety] != 1)
			{

				pacSprite.move(Besh_x, Besh_y);

				detectdirection(Besh_x, Besh_y);
			}

			else
			{
				//if (!(xmod % 32) && !(ymod % 32))
				{
					pacSprite.move(0, 0);
					xx = yy = 0;
				}
			}
		}

		else pacSprite.move(Besh_x, Besh_y);
		pacman.clear();

		if (fright == 0)
			blinkySprite = blinky.findpath(pacSprite, blinkySprite);
		else
			fright--;

		pinky.short_with_tiles(pacSprite, pinkSprite);
		inky.pinky_ran_move(inkySprite, maze1, 2);
		clyde.pinky_ran_move(clydeSprite, maze1, 2);

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
					dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
					pacman.draw(dotSprite);
					if (pacx == j && pacy == i)
					{
						maze1[i][j] = 0;
						score += 10;  //Abnb 
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
						score += 50;  //Abnb 
						if (eatbigdot.getStatus() == Music::Status::Stopped)
							eatbigdot.play();
					}
				}

			}
		pacman.draw(blinkySprite);
		pacman.draw(pinkSprite);
		pacman.draw(inkySprite);
		pacman.draw(clydeSprite);
		pacman.draw(pacSprite);
		pacman.draw(backgr_score);
		pacman.draw(text); //ok
		pacman.draw(text_score);//ok
		pacman.draw(control);
		pacman.draw(control1);
		pacman.draw(control2);
		pacman.draw(control3);
		pacman.draw(control4);
		if (lives >= 1)
			pacman.draw(lives_pacman_sprite1);
		if (lives >= 2)
			pacman.draw(lives_pacman_sprite2);
		if (lives >= 3)
			pacman.draw(lives_pacman_sprite3);
		if (lives >= 4)
			pacman.draw(lives_pacman_sprite4);
		if (lives >= 5)
			pacman.draw(lives_pacman_sprite5);
		pacman.display();
	}
}

void scoreBoardfn()
{
	RenderWindow Score_Screen(sf::VideoMode(1600, 900), "Score Board");

	while (Score_Screen.isOpen())
	{
		Event event;
		while (Score_Screen.pollEvent(event))
		{
			if (event.type == Event::Closed)
				Score_Screen.close();

			else if (event.text.unicode == 27) //27 Esc button
			{
				Score_Screen.close();
				startfn();
				break;
			}
		}
		Score_Screen.clear();
		score_board.Print_Score_Board(Score_Screen);
		Score_Screen.display();
	}
}
void draw_your_maze()
{
	Return_game_to_the_start();
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Draw Your Maze");

	int drawmaze[50][50] = {};
	fstream inputStream;
	inputStream.open("maps/drawurmaze.txt");
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> drawmaze[i][j];

	Texture textur;
	textur.loadFromFile("img/drawurmaze.png");
	Sprite sprite(textur);
	sprite.setPosition(896, 0);


	//--------------------------//

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				ofstream outfile;
				outfile.open("filename.txt", ios::out);
				outfile.clear();
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++)
						outfile << drawmaze[i][j] << " ";
					outfile << "\n";
				}
				outfile.close();
				cout << "done";
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				startfn();
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						maze1[i][j] = drawmaze[i][j];
				window.close();
				startfn();
			}
		}

		int b = Mouse::getPosition(window).x / 32, a = Mouse::getPosition(window).y / 32;
		if (drawmaze[a][b] != 4 && drawmaze[a][b] != 6 && a != 0 && b != 0 && a != 27 && b != 27)
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
				drawmaze[a][b] = 2;
			else if (Keyboard::isKeyPressed(Keyboard::B))
				drawmaze[a][b] = 3;
			else if (Keyboard::isKeyPressed(Keyboard::W))
				drawmaze[a][b] = 1;
			else if (Keyboard::isKeyPressed(Keyboard::S))
				drawmaze[a][b] = 0;
		}
		window.clear();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{

				if (drawmaze[i][j] == 1)
				{
					wallSprite.setTextureRect(IntRect(0, 0, 32, 32));
					wallSprite.setPosition(j * 32, i * 32);
					window.draw(wallSprite);
				}
				else if (drawmaze[i][j] == 2)
				{
					dotSprite.setTextureRect(IntRect(0, 0, 16, 16));
					dotSprite.setColor(Color::Red);
					dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
					window.draw(dotSprite);
				}
				else if (drawmaze[i][j] == 3)
				{
					bigdotSprite.setTextureRect(IntRect(0, 0, 32, 32));
					bigdotSprite.setPosition(j * 32, i * 32);
					window.draw(bigdotSprite);
				}
			}


		window.draw(blinkySprite);
		window.draw(pinkSprite);
		window.draw(inkySprite);
		window.draw(clydeSprite);
		window.draw(pacSprite);
		window.draw(sprite);
		window.display();
	}
}
void playeranimation(int dir, int cnt)
{
	pacSprite.setTextureRect(IntRect(cnt * 32, dir * 32, 32, 32));
}

void detectdirection(int x, int y)
{
	if (x == 2)
		Dir = 0;
	if (x == -2)
		Dir = 2;
	if (y == 2)
		Dir = 1;
	if (y == -2)
		Dir = 3;
}
void Return_game_to_the_start()
{
	pacSprite.setPosition(Vector2f(448, 704));


	blinkySprite.setPosition(Vector2f(384, 416));

	pinkSprite.setPosition(Vector2f(416, 416));

	inkySprite.setPosition(Vector2f(448, 416));

	clydeSprite.setPosition(Vector2f(480, 416));

	sleep(seconds(1));

}
void enterusernamefn()
{
	RenderWindow username(VideoMode(1600, 900), "Enter your name");
	while (username.isOpen())
	{
		Event event;
		while (username.pollEvent(event))
			score_board.Keyboard_Handling(event, username);
	}
}