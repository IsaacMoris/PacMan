#pragma once
#include "SFML/Graphics.hpp"
#include<vector>
using namespace sf;
using namespace std;

class ghostmoving
{
public:
	ghostmoving(int arr[][50], int a, int b);
	

	void findpath(Sprite player, Sprite ghost,  int &xx, int &yy);

	void intialize();

private :
	vector<int> edge[3000];
	int go[5], path[3000], dis[3000], width, height , from , to;
	
};

