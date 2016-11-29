#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include "hero.hpp"
#include <sstream>
class HUD{

public:
	HUD();
	HUD(Hero& hero);
	void drawHUD(sf::RenderWindow & window);
	void sendMsg(std::string s);
	void updateStats(Hero& hero);
	
private:
	void drawTextBox(sf::RenderWindow & window);

	void drawStats(sf::RenderWindow & window);
	std::deque<std::string> messages;
	sf::Color fillColor;
	sf::Color borderColor;
	
	sf::Font font;
	sf::Text text;
	
	int bordersize;
	int width;
	int height;
	int startx;
	int starty;

	int heroMaxHp,heroHp,heroStr,heroAgi,heroDef,heroMana,heroLvl,heroExp, heroExpToNext;
};
	