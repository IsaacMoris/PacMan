#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
class LostWin
{
public:

	LostWin();
	void soundlost();
	void winningsound();
	void lost(RenderWindow &window);
	void win(RenderWindow &window);
private:

	Sound lostsound;
	Sound winsound;
	SoundBuffer winbuffer;
	SoundBuffer lostbuffer;
	Text losttext;
	Text wintext;
	Font font;
};

