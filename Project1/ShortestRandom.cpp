#include "ShortestRandom.h"
#include <iostream>
#include<vector>
#include "SFML/Graphics.hpp"
#include<queue>;
using namespace sf;
using namespace std;


ShortestRandom::ShortestRandom(int arr[][50], int a, int b, int ghostspeed)
{
	speed = ghostspeed;
	width = a;
	height = b;
	go[0] = 1;			 // right
	go[1] = -1;			 // left
	go[2] = width;	     // down
	go[3] = -width;      // up
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			maze[i][j] = arr[i][j];

			if (arr[i][j] == 1)
				continue;
			int from = i * width + j;
			for (int k = 0; k < 4; k++)
			{
				int to = from + go[k];

				if (to < 0 || to / width >= height || (to % width == 0 && k == 1) || (to % width == width - 1 && k == 0)
					|| arr[to / width][to % width] == 1)
					continue;

				edge[from].push_back(to);
			}
		}
	}
}

void ShortestRandom::intialize()
{
	for (int i = 0; i < 2888; i++)
	{
		path[i] = 0;
		dis[i] = 1e9;
	}
}


Sprite ShortestRandom::findpath(Sprite player, Sprite ghost)
{
	int y = player.getPosition().x / 32;
	int x = player.getPosition().y / 32;
	int from = x * width + y;

	y = ghost.getPosition().x / 32;
	x = ghost.getPosition().y / 32;
	int to = x * width + y;

	int aa = ghost.getPosition().x, bb = ghost.getPosition().y;

	if (path[to] == 0) {
		intialize();
		int node = from;
		dis[node] = 0;
		queue<int> q;
		q.push(node);
		while (!q.empty())
		{
			node = q.front();
			q.pop();
			for (int i = 0; i < edge[node].size(); i++)
			{
				int child = edge[node][i];
				if (dis[child] > dis[node] + 1)
				{
					path[child] = node;
					dis[child] = dis[node] + 1;
					q.push(child);
				}
			}
		}
	}


	if (player.getPosition().x == ghost.getPosition().x && player.getPosition().y == ghost.getPosition().y
		&& (aa / 32 * 32 == aa) && (bb / 32 * 32 == bb))
		ghostx = 0, ghosty = 0;
	else
	{
		if (path[to] != 0 && (aa / 32 * 32 == aa) && (bb / 32 * 32 == bb))
		{
			int x = path[to];
			int d = x - to;

			if (d == 1)
				ghostx = speed, ghosty = 0;
			else if (d == -1)
				ghostx = -speed, ghosty = 0;
			else if (d == width)
				ghostx = 0, ghosty = speed;
			else
				ghostx = 0, ghosty = -speed;
		}
	}
	ghost.setPosition(ghost.getPosition().x + ghostx, ghost.getPosition().y + ghosty);
	return ghost;
}


int ShortestRandom::p_x(int pos, Sprite & pink)
{
	return (pink.getPosition().y + pos) / 32;
}

int ShortestRandom::p_y(int pos, Sprite & pink)
{
	return (pink.getPosition().x + pos) / 32;
}


void ShortestRandom::pinky_ran_move(Sprite & pink)
{
	int xmod = pink.getPosition().y, ymod = pink.getPosition().x;

	int  Nextx = 0, Nexty = 0;
	if (ghostx > 0) Nextx = 32; else if (ghostx < 0) Nextx = -32; else  Nextx = 0;
	if (ghosty > 0) Nexty = 32; else if (ghosty < 0) Nexty = -32; else Nexty = 0;
	int pinky_x = p_x(Nexty, pink);
	int pinky_y = p_y(Nextx, pink);
	int random = rand() % 20 + 1;
	//srand(10);

	if (cn == 5)
		vary = vary || ran;
	ran = rand() % 3;

	if ((maze[pinky_x][pinky_y] == 1 || cn % 20 == 0) && !(xmod % 32) && !(ymod % 32))
	{
		if ((ghostx > 0 || ghostx < 0) && !ghosty) // right or left
		{
			if (vary)
			{
				if (maze[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					ghostx = 0, ghosty = -speed;

				else if (maze[p_x(32, pink)][p_y(0, pink)] != 1) // down
					ghostx = 0, ghosty = speed;

				else if (maze[p_x(0, pink)][p_y(32, pink)] != 1) // right
					ghostx = speed, ghosty = 0;

				else if (maze[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					ghostx = -speed, ghosty = 0;
			}

			else
			{
				if (maze[p_x(32, pink)][p_y(0, pink)] != 1) // down
					ghostx = 0, ghosty = speed;

				else if (maze[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					ghostx = 0, ghosty = -speed;

				else if (maze[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					ghostx = -speed, ghosty = 0;

				else if (maze[p_x(0, pink)][p_y(32, pink)] != 1) // right
					ghostx = speed, ghosty = 0;

			}
		}
		//------------------------------------------------------------------------------//
		else if (!ghostx && (ghosty > 0 || ghosty < 0)) // down or up
		{

			if (vary)
			{
				if (maze[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					ghostx = -speed, ghosty = 0;

				else if (maze[p_x(0, pink)][p_y(32, pink)] != 1) // right
					ghostx = speed, ghosty = 0;

				else if (maze[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					ghostx = 0, ghosty = -speed;

				else if (maze[p_x(32, pink)][p_y(0, pink)] != 1) // down
					ghostx = 0, ghosty = speed;
			}

			else
			{
				if (maze[p_x(0, pink)][p_y(32, pink)] != 1) // right
					ghostx = speed, ghosty = 0;

				else if (maze[p_x(0, pink)][p_y(-32, pink)] != 1) // left
					ghostx = -speed, ghosty = 0;

				else if (maze[p_x(32, pink)][p_y(0, pink)] != 1) // down
					ghostx = 0, ghosty = speed;

				else if (maze[p_x(-32, pink)][p_y(0, pink)] != 1) // up
					ghostx = 0, ghosty = -speed;

			}
		}


		(vary) ? vary = 0 : vary = 1;
	}
	pink.move(ghostx, ghosty);
	cn += rand() % 10;
	cn %= 1000000000 + 7;
}

void ShortestRandom::short_with_tiles(Sprite pac, Sprite & ghost)
{

	if (moving_switch % 100 <= 50)
	{

		ghost = findpath(pac, ghost);
		moving_switch++;

		/*if (moving_delay >= 20)
			moving_delay = 0;*/

	}
	else
	{

		pinky_ran_move(ghost);
		moving_switch++;
	}
}
