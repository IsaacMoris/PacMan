#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class scoreboard
{
public:
	scoreboard(ifstream& st, string path);


	void Text_Style(Text& t, float Xposition, float Yposition, string s, Color c, int font_size);

	void Keyboard_Handling(Event& event, RenderWindow& window);

	void Print_Score_Board(RenderWindow& window);

public:
	Text User_Input, User_Name;
	Font font1;  string sentence;
	map<string, int > Score;

private:
	int size = Score.size();
	pair<int, string >Sorted_Score[1000];
	map<string, int > ::iterator it = Score.begin();
	int i = 0;
	Text Desplay_Score_Word, Desplay_Name, Desplay_Score;
	string convert;
};