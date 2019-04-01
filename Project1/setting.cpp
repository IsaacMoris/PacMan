#include "Setting.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Setting::Setting(float width, float height)
{
	if (!font.loadFromFile("font/ARIAL.ttf"))
	{
		cout << "Error" << endl;

	}
	setting[0].setFont(font);
	setting[0].setFillColor(sf::Color::Yellow);
	setting[0].setString("Controls");
	setting[0].setPosition(sf::Vector2f(200, 200));

	setting[1].setFont(font);
	setting[1].setFillColor(sf::Color::White);
	setting[1].setString("Leader Board");
	setting[1].setPosition(sf::Vector2f(200, 300));

	setting[2].setFont(font);
	setting[2].setFillColor(sf::Color::White);
	setting[2].setString("Back");
	setting[2].setPosition(sf::Vector2f(200, 400));

	selectedItemIndex = 0;
}




void Setting::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(setting[i]);
	}

}



void Setting::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		setting[selectedItemIndex].setFillColor(sf::Color::White)
			;	selectedItemIndex--;
		setting[selectedItemIndex].setFillColor(sf::Color::Yellow)
			;
	}
}

void Setting::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		setting[selectedItemIndex].setFillColor(sf::Color::White)
			;	selectedItemIndex++;
		setting[selectedItemIndex].setFillColor(sf::Color::Yellow)
			;
	}
}