#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "Gamemanager.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <regex>




class Game{
public:
	static void Begin();
	static sf::RenderWindow& getWindow();
	//const static sf::Input& getInput();

	const static int WIDTH=750;
	const static int HEIGHT=600;
private:
	static bool loaded;
	enum gamestate{Starting,MainMenu, Playing, Exit};
	static sf::Music bg_track;
	static gamestate state;
	static void Loop();
	static sf::RenderWindow gameWindow;
	static void showMenu();
	static void endGame();
	static void drawHighScore(std::vector<std::tuple<std::string,std::string>>);
	static GameManager manager;
};
