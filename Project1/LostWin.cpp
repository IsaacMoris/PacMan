#include "LostWin.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;


LostWin::LostWin()
{
	lostsound.setBuffer(lostbuffer);
	lostbuffer.loadFromFile("effects/pacman_death.wav");

	winsound.setBuffer(winbuffer);
	winbuffer.loadFromFile("effects/win.wav");
	
	font.loadFromFile("font/ARIAL.TTF");

	losttext.setFont(font);
	losttext.setString("You Lost");
	losttext.setCharacterSize(100);
	losttext.setPosition(620, 400);
	losttext.setFillColor(Color::Blue);
	losttext.setStyle(Text::Style::Bold);

	wintext.setFont(font);
	wintext.setString("You Win");
	wintext.setCharacterSize(100);
	wintext.setPosition(620, 400);
	wintext.setFillColor(Color::Blue);
	wintext.setStyle(Text::Style::Bold);

}


void LostWin::win(RenderWindow &window) {
	window.draw(wintext);
}


void LostWin::lost(RenderWindow &window) {

	window.draw(losttext);
}


void LostWin::soundlost()
{
		lostsound.play();
}

void LostWin::winningsound()
{
		winsound.play();
}