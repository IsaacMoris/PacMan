#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
class pinky
{
public:
	pinky();

	void pinky_ran_move(Sprite& pink, int map[][50], int speed);
	int p_x(int pos, Sprite& pink);
	int p_y(int pos, Sprite& pink);

private:
	int cn = 0, ran = 0, vary = 0;
	int pinkyx = 32, pinkyy = 0;

};