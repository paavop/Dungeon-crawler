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
	
	stx=2*width/3+20;
	sty=starty+height/2-50;
	
	eqWepInd=-1;
	eqArmInd=-1;
	
	clickedl=false;
	clickedr=false;
	
	
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
	
	stx=2*width/3+20;
	sty=starty+height/2-50;
	
	eqWepInd=-1;
	eqArmInd=-1;
	
	bag=hero.getBag();
	
	clickedl=false;
	clickedr=false;
	

}
void HUD::updateStats(Hero & hero,unsigned int lvl){
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
	dngLvl=lvl;
}
void HUD::drawHUD(sf::RenderWindow & window,std::map<std::string,sf::Sprite> & sprites,Hero& hero){
	sf::RectangleShape rect(sf::Vector2f(width-2*bordersize,height-2*bordersize));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(borderColor);
	rect.setPosition(startx+bordersize,starty+bordersize);
	window.draw(rect);
	drawTextBox(window);
	drawStats(window);

	drawItems(window,sprites,hero);
	
	
	
	

}
void HUD::drawItems(sf::RenderWindow & window,std::map<std::string,sf::Sprite> & sprites,Hero & hero){
	int x,y;
	
	sf::RectangleShape rect(sf::Vector2f(200,100));
	rect.setFillColor(sf::Color(59, 62, 66));
	rect.setPosition(stx,sty);
	rect.setOutlineThickness(5);
	rect.setOutlineColor(sf::Color::Black);
	window.draw(rect);
	for(int z=0;z<8;z++){
		if(z<4){
			x=z;
			y=0;
		}else{
			x=z-4;
			y=1;
		}
		
		sf::RectangleShape rect2(sf::Vector2f(50,50));

	
		rect2.setOutlineColor(sf::Color::Black);
		rect2.setOutlineThickness(1);
		
		rect2.setFillColor(sf::Color::Transparent);
		rect2.setPosition(stx+x*50,sty+y*50);
		window.draw(rect2);
		
	}
	for(int z=0;z<bag.size();z++){
		if(z<4){
			x=z;
			y=0;
		}else{
			x=z-4;
			y=1;
		}
		
		sprites[bag[z].getName()].setPosition(stx+x*50,sty+y*50);
		
		window.draw(sprites[bag[z].getName()]);
	}
	for(int z=0;z<8;z++){
		if(z<4){
			x=z;
			y=0;
		}else{
			x=z-4;
			y=1;
		}
		
		sf::RectangleShape rect2(sf::Vector2f(50,50));

		if(z==eqWepInd){
			rect2.setOutlineColor(sf::Color::Red);
			rect2.setOutlineThickness(2);
			rect2.setFillColor(sf::Color::Transparent);
			rect2.setPosition(stx+x*50,sty+y*50);
			window.draw(rect2);
		}
		if(z==eqArmInd){
			rect2.setOutlineColor(sf::Color::Blue);
			rect2.setOutlineThickness(2);
			rect2.setFillColor(sf::Color::Transparent);
			rect2.setPosition(stx+x*50,sty+y*50);
			window.draw(rect2);
		}
	}
	
	
	sf::Vector2i mousePosition=sf::Mouse::getPosition(window);
	if(mousePosition.x>500 && mousePosition.x<750 && mousePosition.y>450 && mousePosition.y<600){
		//std::cout<<"x: "<<mousePosition.x<<" y: "<<mousePosition.y<<std::endl;
		drawItemStats(mousePosition.x-stx,mousePosition.y-sty,window,hero);
	}
}

void HUD::drawItemStats(int x, int y,sf::RenderWindow & window,Hero & hero){
	if(x<200 && y<100 && x>0 && y>0){
		int selected=x/50+4*(int)(y/50);
		if(selected>=0 && selected<bag.size()){
			//std::cout<<bag[selected].getName()<<std::endl;
			sf::RectangleShape rect(sf::Vector2f(175,50));
			//std::cout<<x<<","<<y<<std::endl;
			rect.setFillColor(sf::Color::Black);
			rect.setOutlineThickness(3);
			rect.setOutlineColor(sf::Color::White);
			rect.setPosition(stx+x-175,sty+y-50);
			window.draw(rect);
			sf::Font font;
			font.loadFromFile("resources/joystix_monospace.ttf");
			sf::Text text(bag[selected].getName(),font);
			text.setCharacterSize(14);
			text.setPosition(stx+x-175,sty+y-50);
			window.draw(text);
			
			std::ostringstream tmp;
			tmp<<bag[selected].getValue();
			text.setCharacterSize(10);
			if(bag[selected].getType()=="Weapon"){
				text.setString("Attack: "+tmp.str());

			}
			if(bag[selected].getType()=="Armor"){
				text.setString("Defense: "+tmp.str());
			}

			text.move(0,20);
			window.draw(text);
			text.setString(bag[selected].getDescription());
			text.move(0,15);
			window.draw(text);
			
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				clickedl=true;
			}
			if(clickedl && not sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			
				if(selected==eqWepInd){
					sendMsg("Unequipped "+bag[selected].getName());
					eqWepInd=-1;
					hero.unEquip(0);
					
				}
				else if(selected==eqArmInd){
					sendMsg("Unequipped "+bag[selected].getName());
					eqArmInd=-1;
					hero.unEquip(1);
				}
				else if(hero.equip(selected)){
					sendMsg("Equipped "+bag[selected].getName());
					if(bag[selected].getType()=="Weapon"){
						eqWepInd=selected;

					}
					if(bag[selected].getType()=="Armor"){
						eqArmInd=selected;
					}
				}
				clickedl=false;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				clickedr=true;

			}
			if(clickedr && not sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				sendMsg("Threw away "+bag[selected].getName());
				if(selected==eqWepInd){
					eqWepInd=-1;
				}
				if(selected==eqArmInd){
					eqArmInd=-1;
				}
				if(selected<eqWepInd){

					eqWepInd-=1;

				}
				if(selected<eqArmInd){
					eqArmInd-=1;
				}
				hero.dropItem(selected);
				clickedr=false;
			}
			
			
			
		}
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
	
	oss<<"Dungeon lvl: "<<dngLvl<<std::endl;
	oss<<"Health: "<<heroHp<<"/"<<heroMaxHp<<std::endl<<std::endl;
	
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
	
	
	
	
	
	
