#include "SFML/Graphics.hpp"
#include<vector>
using namespace sf;
using namespace std;

class ShortestRandom
{
public:
	ShortestRandom(int arr[][50], int a, int b, int ghostspeed);
	Sprite findpath(Sprite player, Sprite ghost);
	void intialize();



	void pinky_ran_move(Sprite& pink);
	int p_x(int pos, Sprite& pink);
	int p_y(int pos, Sprite& pink);


	void short_with_tiles(Sprite pac, Sprite& ghost);

private:
	vector<int> edge[3000];
	int go[5] = {}, path[3000] = {}, dis[3000] = {} ,maze[50][50] , width = 0, height = 0, from = 0, to = 0;

	int cn = 0, ran = 0, vary = 0;
	int ghostx = 32, ghosty = 0;
	int speed;
	int  moving_switch = 0, moving_delay = 0;

};

