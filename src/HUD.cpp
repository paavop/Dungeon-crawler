#include "HUD.hpp"

HUD::HUD(){
	std::cout<<"nope"<<std::endl;
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

	heroMaxHp=10;
	heroHp=0;
	heroStr=0;
	heroAgi=0;
	heroDef=0;
	heroMana=0;
	heroLvl=0;
	heroExp=0;
	heroExpToNext=0;
}

HUD::HUD(Hero & hero){
	std::cout<<"oikein"<<std::endl;
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
	
	heroMaxHp=hero.getMaxHp();
	heroHp=hero.getHp();
	heroStr=hero.getStr();
	heroAgi=hero.getAgi();
	heroDef=hero.getDef();
	heroMana=hero.getMana();
	heroLvl=hero.getLvl();
	heroExp=hero.getExp();
	heroExpToNext=hero.getExpToNext();

}
void HUD::updateStats(Hero & hero){
	heroMaxHp=hero.getMaxHp();
	heroHp=hero.getHp();
	heroStr=hero.getStr();
	heroAgi=hero.getAgi();
	heroDef=hero.getDef();
	heroMana=hero.getMana();
	heroLvl=hero.getLvl();
	heroExp=hero.getExp();
	heroExpToNext=hero.getExpToNext();
}
void HUD::drawHUD(sf::RenderWindow & window){
	sf::RectangleShape rect(sf::Vector2f(width-2*bordersize,height-2*bordersize));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(borderColor);
	rect.setPosition(startx+bordersize,starty+bordersize);
	window.draw(rect);
	drawTextBox(window);
	drawStats(window);
}

void HUD::sendMsg(std::string msg){
	messages.push_front(msg);
	if(messages.size()>10){
		messages.pop_back();
	}
}
void HUD::drawStats(sf::RenderWindow & window){

	std::ostringstream oss;
	
	sf::Font font;
	font.loadFromFile("resources/joystix_monospace.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(14);
	text.setColor(sf::Color::Black);
	
	oss<<"Health: "<<heroHp<<"/"<<heroMaxHp<<std::endl;
	oss<<"Mana  : "<<heroMana<<std::endl<<std::endl;
	oss<<"Exp   : "<<heroExp<<"/"<<heroExpToNext<<std::endl;
	oss<<"Level : "<<heroLvl<<std::endl<<std::endl;
	oss<<"S:"<<heroStr<<" D:"<<heroDef<<" A:"<<heroAgi; 
	std::string str1=oss.str();
	text.setString(str1);
	text.setPosition(20,starty+height-bordersize-6*5-5*20);
	window.draw(text);
	
	
	
	
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
	
	
	
	
	
	
