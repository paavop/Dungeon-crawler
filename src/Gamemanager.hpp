
#include "HUD.hpp"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>


class GameManager
{
public:
	GameManager();
	void updateAll();
	void drawAll(sf::RenderWindow & window);
	
private:
	std::vector<std::vector<int>> makeMap(int a);
	void findStart(std::vector<std::vector<int>> map);
	void movePlayer(int a);
	void updatePercentages();
	void drawMap(sf::RenderWindow& window);
	void drawMC(sf::RenderWindow& window);
	void drawFps(sf::RenderWindow& window);
	Hero hero;
	HUD hud;
	bool movingUp,movingDown,movingLeft,movingRight;
	int n,m,mapsize;
	float animationTime,cmdTime,yPercentage,xPercentage,movePercentage,offsety,offsetx;
	sf::Clock clock;
	sf::Clock fpsClock;
	float fpsTime;
	sf::Vector2f MCspot;
	
	
	sf::Texture wall_t;
	sf::Texture ground_t;
	sf::Texture MC_t;
	sf::Texture stairs_t;
	
	sf::Sprite wall;
	sf::Sprite ground;
	sf::Sprite MC;
	sf::Sprite stairs;
	sf::IntRect SourceSprite;
	std::vector<std::vector<int>> map;
	
};
	
