#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "monster.hpp"
#include <algorithm>
#include <math.h>
#include "reader.hpp"

#include <sstream>
#include "HUD.hpp"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>


class GameManager
{
public:
	GameManager();
	void updateAll(sf::RenderWindow& window);
	void drawAll(sf::RenderWindow & window);

	bool isFreeTile(unsigned int x, unsigned int y);
	bool freeLineOfSight(sf::Vector2i a, sf::Vector2i b); //Tells you is it possible to see from a to b
	bool hearPlayer(Monster& monster);
	bool seePlayer(Monster& monster);
	bool gameOn();
	void tryDetectPlayer(Monster& monster);
	int getScore();
	
private:
	int score;
	bool gameon;
	void itemLottery();
	void newLevel();
	void nextLevel(sf::RenderWindow& window);
	unsigned int dungeonLevel;
	void addMonsters();
	void setEnemies();

	void loadEnemyTexture(Monster& enemy);
	void loadItemTexture(Item* item);
	
	void enemyTurn();

	
	std::vector<std::vector<int> > makeMap(int a);
	void findStart(std::vector<std::vector<int> > map);
	void movePlayer(int a);
	void updatePercentages();
	void drawMap(sf::RenderWindow& window);
	void drawMC(sf::RenderWindow& window);
	void drawFps(sf::RenderWindow& window);
	void drawEnemies(sf::RenderWindow& window);
	Hero hero;
	HUD hud;
	bool movingUp,movingDown,movingLeft,movingRight,plrMadeMove;
	bool fighting;
	int n,m,mapsize;
	float animationTime,cmdTime,yPercentage,xPercentage,movePercentage,offsety,offsetx;
	sf::Clock clock;
	sf::Clock fpsClock;
	float fpsTime;
	sf::Vector2i MCspot;
	std::vector<Monster> availableMonsters;
	std::vector<Monster> monsters;
	std::vector<Item*> items;
	
	
	sf::Texture wall_t;
	sf::Texture ground_t;
	sf::Texture MC_t;
	sf::Texture stairs_t;
	std::map<std::string,sf::Texture> enemy_textures;
	std::map<std::string,sf::Texture> item_textures;
	
	sf::Sprite wall;
	sf::Sprite ground;
	sf::Sprite MC;
	sf::Sprite stairs;
	std::map<std::string,sf::Sprite> enemy_sprites;
	std::map<std::string,sf::Sprite> item_sprites;
	

	sf::IntRect SourceSprite;
	std::vector<std::vector<int> > map;
	
};

#endif
	
