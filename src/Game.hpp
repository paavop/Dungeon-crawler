#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "Gamemanager.hpp"

class Game{
public:
	static void Begin();
	static sf::RenderWindow& getWindow();
	//const static sf::Input& getInput();

	const static int WIDTH=750;
	const static int HEIGHT=600;
private:

	enum gamestate{Starting,MainMenu, Playing, Exit};
	
	static gamestate state;
	static void Loop();
	static sf::RenderWindow gameWindow;
	static void showMenu();
	static GameManager manager;
};
