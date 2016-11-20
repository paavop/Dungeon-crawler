#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>


void Game::Begin(){
	if(state!=Starting){
		return;
	}
	gameWindow.create(sf::VideoMode(WIDTH,HEIGHT), "Luolaluovinta");
	state=Game::MainMenu;

	while(gameWindow.isOpen()){

		Loop();
	}
	

}

sf::RenderWindow& Game::getWindow(){
	return gameWindow;
}
/*
const sf::Keyboard& Game::getInput(){
	return gameWindow.GetInput();
}
*/

void Game::Loop(){
	sf::Event event;

	gameWindow.clear();

	while (gameWindow.pollEvent(event)){
		
		if (event.type == sf::Event::Closed)

			gameWindow.close();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		gameWindow.close();
	}
	switch(state){
		
		case Game::MainMenu:
			{
				gameWindow.clear();
				showMenu();
				gameWindow.display();
				break;
				
				
			}
		case Game::Playing:
			{
				gameWindow.clear();
				manager.updateAll();
				manager.drawAll(gameWindow);
				
				gameWindow.display();
				
				break;

			}
		case Game::Exit:
			{
				
				gameWindow.close();
				gameWindow.display();
				break;
			}
		
	}
}
void Game::showMenu(){

	int bordersize=5;
	sf::RectangleShape rect(sf::Vector2f(WIDTH-2*bordersize,HEIGHT-2*bordersize));
	rect.setFillColor(sf::Color(150, 50, 250));
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(sf::Color(250, 150, 100));
	rect.setPosition(0+bordersize,0+bordersize);
	gameWindow.draw(rect);
	
	sf::Font font;
	font.loadFromFile("resources/Gameplay.ttf");
	sf::Text text("Press ENTER to start",font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setPosition((WIDTH-text.getLocalBounds().width)/2,(HEIGHT-text.getLocalBounds().height)/2);
	gameWindow.draw(text);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		state=Game::Playing;
	}

}

Game::gamestate Game::state=Starting;
sf::RenderWindow Game::gameWindow;
GameManager Game::manager;
			
	
