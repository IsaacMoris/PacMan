#include "scoreboard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <iomanip> // setw
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>   // std::greater
using namespace std;
using namespace sf;


scoreboard::scoreboard()
{
	scoreIn.open("Score/Score.txt");
	
	//--------- Read score from file --------------------//
	if (scoreIn.fail())
	{
		cerr << "Error while opening ifstream\n";
		exit(1);
	}

	while (!scoreIn.eof())
	{
		pair<string, int > name_and_score;
		scoreIn >> name_and_score.first >> name_and_score.second;
		Score[name_and_score.first] = name_and_score.second;

	}
	scoreIn.close();

	//----------------- sort score ascending order ---------------//

	size = Score.size();
	it = Score.begin();
	for (; it != Score.end(); it++, i++)
	{
		Sorted_Score[i].first = it->second;
		Sorted_Score[i].second = it->first;
	}

	sort(Sorted_Score, Sorted_Score + size);
}


void scoreboard::Text_Style(Text& t, float Xposition, float Yposition, string s, Color c, int font_size)
{
	if (!font1.loadFromFile("Font//arial.ttf"))
		cout << "Error" << endl;

	t.setFont(font1);
	t.setCharacterSize(font_size);
	t.setFillColor(c);
	t.setStyle(Text::Bold);
	t.setString(s);
	t.setPosition(Xposition, Yposition);
}

void scoreboard::Keyboard_Handling(Event& event, RenderWindow& window)
{
	if (event.type == Event::Closed)
		exit(0);

	if (event.type == Event::TextEntered)
	{
		if (event.text.unicode >= 32 && event.text.unicode <= 126)
			sentence += (char)event.text.unicode;

		else if (event.text.unicode == 8 && sentence.length() > 0)
			sentence.erase(sentence.length() - 1, 1);

		else if (event.text.unicode == 13)
		{
			Score[sentence]=max(Score[sentence],0);
			window.close();
		}
	}
		Text_Style(User_Name, 250,400, "User Name :", Color::Yellow, 60);
		Text_Style(User_Input, 650, 400 , sentence, Color::White, 55);
		User_Input.setString(sentence);
		User_Name.setString("User Name :");
		window.clear();
	window.draw(User_Name);
	window.draw(User_Input);
	window.display();
}


void scoreboard::Print_Score_Board(RenderWindow& window)
{
	float x = 600.0, y = 0;

	Text_Style(Desplay_Score_Word, x, y, "Score", Color::White, 100);

	x = 570.0; y = 120.0;
	window.draw(Desplay_Score_Word);
	for (i = size - 1; i >= 0; i--, y += 90)
	{
		if (Sorted_Score[i].second == "")
			break;

		convert = to_string(Sorted_Score[i].first);

		Text_Style(Desplay_Name, x, y, Sorted_Score[i].second, Color::Yellow, 60);
		Text_Style(Desplay_Score, x + 250, y, convert, Color::Green, 45);

		window.draw(Desplay_Name);
		window.draw(Desplay_Score);
		//window.display();
	}

}


void scoreboard :: Save_Score_Board(int finale_score)
{
	scoreOut.open("Score/Score.txt");
	Score[sentence] = max(finale_score, Score[sentence]);

	scoreOut.clear();
	it = Score.begin();
	for (; it != Score.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
		scoreOut << it->first << " " << it->second << endl;
	}
	scoreOut.close();

}