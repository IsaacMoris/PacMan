#pragma once
#include "SFML/Graphics.hpp"
#include<vector>
using namespace sf;
using namespace std;

class ghostmoving
{
public:
	ghostmoving(int arr[][50], int a, int b,int ghostspeed);
	

	Sprite findpath(Sprite player, Sprite ghost);

	void intialize();

private :
	vector<int> edge[3000];
	int go[5] = {}, path[3000] = {}, dis[3000] = {}, width = 0, height = 0, from = 0, to = 0;

	int xx=0, yy=0 , speed;
	
};

