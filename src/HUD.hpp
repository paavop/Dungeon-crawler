#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include <utility>

class HUD{

public:
	HUD();
	void drawHUD(sf::RenderWindow & window);
	void sendMsg(std::string s);
	
private:
	void drawTextBox(sf::RenderWindow & window);
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
};
	
