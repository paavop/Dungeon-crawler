#include "monster.hpp"

Monster::Monster(sf::Vector2f pos){
	alive = true;
	detects_player = false;
	position = pos;
	name = "risumies";
	pic_name = "resources/enemy_risumies.png";
	maxhp = 1;			//Monster's max health points	
	hp = maxhp;			//Monster's current health points
	lvl = 0;			//Level of the Monster
	strength = 1;		//Monster's strength stat
	agility = 1;		//Monster's agility stat
	defense = 1;		//Monster's defense stat
	hearing = 3;

}

Monster::Monster(	int h, int s, int a, 
					int d,  int lvl, int hearing_radius,
					sf::Vector2f pos, std::string name)
{
	alive = true;
	detects_player = false;
	name = name;
	position = pos;
	pic_name = "resources/enemy_risumies.png";
	maxhp=h;
	hp=h;
	strength=s;
	agility=a;
	defense=d;
	lvl = lvl;
	hearing = hearing_radius;

}

std::string Monster::getName(){
	return name;
}
std::string Monster::getPicName(){
	return pic_name;
}
sf::Vector2f Monster::getPos(){
	return position;
}
void Monster::setPos(unsigned int x, unsigned int y){
	position = sf::Vector2f(x,y);
}
void Monster::setSprite(sf::Sprite& sprite){
	sprite = sprite;
}

int Monster::getHp(){
	return hp;
}
int Monster::getStr(){
	return strength;
}
int Monster::getLvl(){
	return lvl;
}
int Monster::getAgi(){
	return agility;
}
int Monster::getDef(){
	return defense;
}

int	Monster::getHearingRadius(){
	return hearing;
}

void Monster::die(){
	alive = false;
}
bool Monster::isAlive(){
	return alive; 
}

void Monster::detectsPlr(){
	detects_player = true;
}
void Monster::undetectsPlr(){
	detects_player = false;
}

void Monster::setTargetPos(sf::Vector2f pos){
	target_pos = pos;
}