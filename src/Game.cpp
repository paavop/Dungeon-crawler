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
	gameWindow.setFramerateLimit(60);
	state=Game::MainMenu;
	

	if(!bg_track.openFromFile("resources/DungeonBeats.ogg")){
		perror("can't load music"); //error
	}
	bg_track.setLoop(true);

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

	
	switch(state){
		
		case Game::MainMenu:
			{

				showMenu();
				gameWindow.display();
				break;
				
				
			}
		case Game::Playing:
			{
				if(manager.gameOn()){
					manager.updateAll(gameWindow);
					manager.drawAll(gameWindow);
				
					gameWindow.display();
				}else{
					bg_track.stop();
					state=Game::Exit;
				}
				
				break;

			}
		case Game::Exit:
			{

				endGame();
				//gameWindow.close();
				gameWindow.display();
				break;
			}
		
	}
}
void Game::showMenu(){

	int bordersize=5;
	sf::RectangleShape rect(sf::Vector2f(WIDTH-2*bordersize,HEIGHT-2*bordersize));
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setPosition(0+bordersize,0+bordersize);
	gameWindow.draw(rect);
	
	sf::Font font;
	font.loadFromFile("resources/Gameplay.ttf");
	sf::Text text("Press ENTER to start",font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Blue);
	text.setPosition((WIDTH-text.getLocalBounds().width)/2,(HEIGHT-text.getLocalBounds().height)/2);
	gameWindow.draw(text);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		state=Game::Playing;
		bg_track.play();
	}

}
void Game::endGame(){

	std::vector<std::tuple<std::string,std::string>> scores;

	if(!loaded){

		std::ifstream highscore("highscores.txt");
	
		if(!highscore){
			std::cout<<"Problem opening high scores"<<std::endl;	
		}else{

			std::string newline;

			while(std::getline(highscore,newline)){

				std::regex ws_re("\\s+");
				
				std::vector<std::string> result{
					std::sregex_token_iterator(newline.begin(), newline.end(), ws_re, -1), {}
				};

				if(result.size()<2){
					result.push_back("");
				}
				scores.push_back(std::make_tuple(result[0],result[1]));


			}


			highscore.close();

		}
		
		loaded=true;
		/*
		for(int i=0;i<scores.size();i++){
			std::cout<<std::get<0>(scores[i])<<" "<<std::get<1>(scores[i])<<std::endl;
		}
		*/
	}

	int yourScore=manager.getScore();
	std::string my_name="";

	while(gameWindow.isOpen()){

		sf::Event event;
		gameWindow.clear();
		
		while (gameWindow.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				gameWindow.close();
			if (event.type == sf::Event::TextEntered){
				if(event.text.unicode==8){

					if(my_name.length()>0)
						my_name.pop_back();
				}
				else if(event.text.unicode==13){
					
				}
				else if(event.text.unicode==27){
					gameWindow.close();
				}
				else if (event.text.unicode < 128 && my_name.length()<12){
					sf::String tmp=(event.text.unicode);
					std::string tmp2=tmp;
					my_name.append(tmp2);
					

				}
		    
		    

			}
		}
	
	
		int bordersize=5;
		sf::RectangleShape rect(sf::Vector2f(WIDTH-2*bordersize,HEIGHT-2*bordersize));
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineThickness(bordersize);
		rect.setOutlineColor(sf::Color::Red);
		rect.setPosition(0+bordersize,0+bordersize);
		gameWindow.draw(rect);
	
		sf::Font font;
		font.loadFromFile("resources/Gameplay.ttf");
		sf::Text text("GAME OVER",font);
		text.setCharacterSize(70);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Red);
		text.setPosition((WIDTH-text.getLocalBounds().width)/2,(HEIGHT-text.getLocalBounds().height)/3);
		
		gameWindow.draw(text);
		text.setCharacterSize(25);
		text.setColor(sf::Color::White);
		std::ostringstream stm;
   		stm << yourScore;
		text.setString("Your score: "+stm.str());
		text.setPosition((WIDTH-text.getLocalBounds().width)/2,70 +(HEIGHT-text.getLocalBounds().height)/3);
		gameWindow.draw(text);
		text.setString("Enter name:");
		text.setPosition((WIDTH-text.getLocalBounds().width)/2,2*(HEIGHT-text.getLocalBounds().height)/3-10);
		gameWindow.draw(text);
		text.setString(my_name);
		text.setPosition((WIDTH-text.getLocalBounds().width)/2,40+2*(HEIGHT-text.getLocalBounds().height)/3);
		gameWindow.draw(text);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			if(my_name==""){
				my_name="ANON";
			}
			std::tuple<std::string,std::string> tmp(stm.str(),my_name);
			std::tuple<std::string,std::string> tmp2;
			for(int i=0;i<scores.size();i++){
				if(std::stoi(std::get<0>(tmp))>std::stoi(std::get<0>(scores[i]))){
					tmp2=scores[i];
					scores[i]=tmp;
					tmp=tmp2;
				}
			}
			std::ofstream file("highscores.txt");
			if(file.is_open()){
				
				for(int i=0;i<scores.size();i++){
					file<<std::get<0>(scores[i])<<" "<<std::get<1>(scores[i])<<std::endl;
				}
			}else{
				std::cout<<"Can't open high scores"<<std::endl;
			}
			file.close();
			
			while(not sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && gameWindow.isOpen()){
				drawHighScore(scores);
				while (gameWindow.pollEvent(event)){
					if (event.type == sf::Event::Closed)
						gameWindow.close();
				}
			}
			gameWindow.close();
		}
		gameWindow.display();
	}
}
void Game::drawHighScore(std::vector<std::tuple<std::string,std::string>> scores){
	int bordersize=5;
	sf::RectangleShape rect(sf::Vector2f(WIDTH-2*bordersize,HEIGHT-2*bordersize));
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(sf::Color::White);
	rect.setPosition(0+bordersize,0+bordersize);
	gameWindow.draw(rect);
	sf::Font font;
	font.loadFromFile("resources/Gameplay.ttf");
	sf::Text text("HIGH SCORES",font);
	text.setCharacterSize(70);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setPosition((WIDTH-text.getLocalBounds().width)/2,(HEIGHT-text.getLocalBounds().height)/3);
	gameWindow.draw(text);
	text.setCharacterSize(20);
	text.setPosition((WIDTH-text.getLocalBounds().width)/2,(HEIGHT-text.getLocalBounds().height)/2);
	for(int i=0;i<scores.size();i++){
		text.setString(std::get<1>(scores[i])+" "+std::get<0>(scores[i]));
		text.setPosition((WIDTH-text.getLocalBounds().width)/2,i*25+(HEIGHT-text.getLocalBounds().height)/2);
		gameWindow.draw(text);

		
	}
	gameWindow.display();
}
bool Game::loaded=false;
Game::gamestate Game::state=Starting;
sf::RenderWindow Game::gameWindow;
GameManager Game::manager;
sf::Music Game::bg_track;

			
	
