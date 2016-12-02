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
	
	bag=hero.getBag();

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
	bag=hero.getBag();
}
void HUD::drawHUD(sf::RenderWindow & window,std::map<std::string,sf::Sprite> & sprites){
	sf::RectangleShape rect(sf::Vector2f(width-2*bordersize,height-2*bordersize));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(borderColor);
	rect.setPosition(startx+bordersize,starty+bordersize);
	window.draw(rect);
	drawTextBox(window);
	drawStats(window);
	drawStats(window);
	drawItems(window,sprites);
	

}
void HUD::drawItems(sf::RenderWindow & window,std::map<std::string,sf::Sprite> & sprites){
	int x,y;
	int stx=2*width/3+20;
	int sty=starty+height/2-50;
	sf::RectangleShape rect(sf::Vector2f(200,100));
	rect.setFillColor(sf::Color(59, 62, 66));
	rect.setPosition(stx,sty);
	rect.setOutlineThickness(5);
	rect.setOutlineColor(sf::Color::Black);
	window.draw(rect);
	for(int z=0;z<bag.size();z++){
		if(z<4){
			x=z;
			y=0;
		}else{
			x=z-4;
			y=1;
		}
		
		sf::RectangleShape rect2(sf::Vector2f(50,50));
		rect2.setOutlineThickness(1);
		rect2.setOutlineColor(sf::Color::Black);
		rect2.setFillColor(sf::Color::Transparent);
		rect2.setPosition(stx+x*50,sty+y*50);
		window.draw(rect2);
		sprites[bag[z].getName()].setPosition(stx+x*50,sty+y*50);
		
		window.draw(sprites[bag[z].getName()]);
	}
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
	
	
	
	
	
	
