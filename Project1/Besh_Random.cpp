#include "Besh_Random.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <stdlib.h>
using namespace std;
using namespace sf;


Besh_Random::Besh_Random()
{
}
int Besh_Random::p_x(int pos, Sprite& pink)
{
	return (pink.getPosition().y + pos) / 32;
}
// return the next position
int Besh_Random::p_y(int pos, Sprite & pink)
{
	return (pink.getPosition().x + pos) / 32;
}


void Besh_Random::pinky_ran_move(Sprite & pink, int map[][50], int speed)
{
	int xmod = pink.getPosition().y, ymod = pink.getPosition().x;

	int  Nextx = 0, Nexty = 0;
	if (pinkyx > 0) Nextx = 32; else if (pinkyx < 0) Nextx = -32; else  Nextx = 0;
	if (pinkyy > 0) Nexty = 32; else if (pinkyy < 0) Nexty = -32; else Nexty = 0;
	int pinky_x = p_x(Nexty, pink);
	int pinky_y = p_y(Nextx, pink);
	int random = rand() % 20 + 1;
	//srand(10);

	if (cn == 5)
		vary = vary || ran;
	ran = rand() % 3;

	if ((map[pinky_x][pinky_y] == 1 || cn % 20 == 0) && !(xmod % 32) && !(ymod % 32))
	{
		if ((pinkyx > 0 || pinkyx < 0) && !pinkyy) // right or left
		{
			if (vary)
			{
				if (map[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					pinkyx = 0, pinkyy = -speed;

				else if (map[p_x(32, pink)][p_y(0, pink)] != 1) // down
					pinkyx = 0, pinkyy = speed;

				else if (map[p_x(0, pink)][p_y(32, pink)] != 1) // right
					pinkyx = speed, pinkyy = 0;

				else if (map[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					pinkyx = -speed, pinkyy = 0;
			}

			else
			{
				if (map[p_x(32, pink)][p_y(0, pink)] != 1) // down
					pinkyx = 0, pinkyy = speed;

				else if (map[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					pinkyx = 0, pinkyy = -speed;

				else if (map[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					pinkyx = -speed, pinkyy = 0;

				else if (map[p_x(0, pink)][p_y(32, pink)] != 1) // right
					pinkyx = speed, pinkyy = 0;

			}
		}
		//------------------------------------------------------------------------------//
		else if (!pinkyx && (pinkyy > 0 || pinkyy < 0)) // down or up
		{

			if (vary)
			{
				if (map[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					pinkyx = -speed, pinkyy = 0;

				else if (map[p_x(0, pink)][p_y(32, pink)] != 1) // right
					pinkyx = speed, pinkyy = 0;

				else if (map[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					pinkyx = 0, pinkyy = -speed;

				else if (map[p_x(32, pink)][p_y(0, pink)] != 1) // down
					pinkyx = 0, pinkyy = speed;
			}

			else
			{
				if (map[p_x(0, pink)][p_y(32, pink)] != 1) // right
					pinkyx = speed, pinkyy = 0;

				else if (map[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					pinkyx = -speed, pinkyy = 0;

				else if (map[p_x(32, pink)][p_y(0, pink)] != 1) // down
					pinkyx = 0, pinkyy = speed;

				else if (map[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					pinkyx = 0, pinkyy = -speed;

			}
		}


		(vary) ? vary = 0 : vary = 1;
	}
	pink.move(pinkyx, pinkyy);
	cn += rand() % 10;
	cn %= 1000000000 + 7;
}