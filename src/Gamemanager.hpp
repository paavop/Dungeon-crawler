

#include "monster.hpp"
#include <algorithm>



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

<<<<<<< HEAD
	bool isFreeTile(unsigned int x, unsigned int y);
	bool freeLineOfSight(sf::Vector2f a, sf::Vector2f b); //Tells you is it possible to see from a to b
=======
	bool isFree(const sf::Vector2u pos);
>>>>>>> 15f402ceefe8cbc9bfa65e2d7fc7ae9b860d4acc

	
private:
	void setEnemies();
<<<<<<< HEAD
	void loadEnemyTextures(Monster& enemy);
=======
	void loadEnemyTexture(Monster& enemy);
>>>>>>> 15f402ceefe8cbc9bfa65e2d7fc7ae9b860d4acc
	
	std::vector<std::vector<int>> makeMap(int a);
	void findStart(std::vector<std::vector<int>> map);
	void movePlayer(int a);
	void updatePercentages();
	void drawMap(sf::RenderWindow& window);
	void drawMC(sf::RenderWindow& window);
	void drawFps(sf::RenderWindow& window);
	void drawEnemies(sf::RenderWindow& window);
	Hero hero;
	HUD hud;
	bool movingUp,movingDown,movingLeft,movingRight;
	int n,m,mapsize;
	float animationTime,cmdTime,yPercentage,xPercentage,movePercentage,offsety,offsetx;
	sf::Clock clock;
	sf::Clock fpsClock;
	float fpsTime;
	sf::Vector2f MCspot;
	std::vector<Monster> monsters;
	
	
	sf::Texture wall_t;
	sf::Texture ground_t;
	sf::Texture MC_t;
	sf::Texture stairs_t;
	std::vector<sf::Texture> enemy_textures;
	
	sf::Sprite wall;
	sf::Sprite ground;
	sf::Sprite MC;
	sf::Sprite stairs;
	std::vector<sf::Sprite> enemy_sprites;

	sf::IntRect SourceSprite;
	std::vector<std::vector<int>> map;
	
};
	
