#include "monster.hpp"

Monster::Monster(sf::Vector2f pos){
	alive = true;
	this->position = pos;
	name = 'risumies';
	pic_name = 'resources/enemy_risumies.png';
	maxhp = 1;			//Monster's max health points	
	hp = maxhp;			//Monster's current health points
	lvl = 0;			//Level of the Monster
	strength = 1;		//Monster's strength stat
	agility = 1;		//Monster's agility stat
	defense = 1;		//Monster's defense stat
	mana = 0;			//Monster's mana stat
}

Monster::Monster(	int h, int s, int a, 
					int d, int lvl,
					sf::Vector2f pos, std::string name)
{
	alive = true;
	this->name = name;
	this->position = pos;
	maxhp=h;
	hp=h;
	strength=s;
	agility=a;
	defense=d;
	this->lvl = lvl;

}

std::string getName() const{
	return this->name;
}

sf::Vector2f Monster::getPos(){
	return this->position;
}
void Monster::setPos(unsigned int x, unsigned int y){
	this->position = sf::Vector2f(x,y);
}
void Monster::setSprite(sf::Sprite& sprite){
	this->sprite = sprite;
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
void die(){
	this->alive = false;
}
bool isAlive(){
	return this->alive; 
}