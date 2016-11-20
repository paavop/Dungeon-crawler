#include "HUD.hpp"

HUD::HUD(){
	bordersize=5;
	width=750;
	height=150;
	startx=0;
	starty=450;
	fillColor.r=150;
	fillColor.g=50;
	fillColor.b=250;

	borderColor.r=250;
	borderColor.r=150;
	borderColor.r=100;

}

void HUD::drawHUD(sf::RenderWindow & window){
	sf::RectangleShape rect(sf::Vector2f(width-2*bordersize,height-2*bordersize));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(borderColor);
	rect.setPosition(startx+bordersize,starty+bordersize);
	window.draw(rect);
	drawTextBox(window);
}

void HUD::sendMsg(std::string msg){
	messages.push_front(msg);
	if(messages.size()>10){
		messages.pop_back();
	}
}

void HUD::drawTextBox(sf::RenderWindow & window){
	sf::RectangleShape rect(sf::Vector2f(width/3,height-2*bordersize-2*5));
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(width/2-(width/6),starty+bordersize+5);
	window.draw(rect);
	int textx=(int) rect.getPosition().x;
	int texty=(int) rect.getPosition().y;
	int i;
	sf::Font font;
	font.loadFromFile("resources/ShareTech.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(14);
	text.setColor(sf::Color::White);
	for (i=0;i<messages.size();i++){
		if(i>5){
			break;
		}
		text.setString(messages[i]);
		text.setPosition(textx+10,texty+height-2*bordersize-7*5-i*20);
		window.draw(text);
		
	}
		
}
	
	
	
	
	
	
