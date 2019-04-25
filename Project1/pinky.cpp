#include "pinky.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <stdlib.h>
using namespace std;
using namespace sf;


pinky::pinky()
{
}
int pinky::p_x(int pos, Sprite& pink)
{
	return (pink.getPosition().y + pos) / 32;
}

int pinky::p_y(int pos, Sprite & pink)
{
	return (pink.getPosition().x + pos) / 32;
}


void pinky::pinky_ran_move(Sprite & pink, int map[][50], int speed)
{
	int xmod = pink.getPosition().y, ymod = pink.getPosition().x;

	int incx = 0, incy = 0;
	if (pinkyx > 0) incx = 32 - speed; else if (pinkyx < 0) incx = -32 + speed; else incx = 0;
	if (pinkyy > 0) incy = 32 - speed; else if (pinkyy < 0) incy = -32 + speed; else incy = 0;
	int pinky_x = p_x(pinkyy + incy, pink);
	int pinky_y = p_y(pinkyx + incx, pink);
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