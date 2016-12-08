#include "monster.hpp"

Monster::Monster(sf::Vector2f pos){
	alive = true;
	detects_player = false;
	position = pos;
	name = "Gargant";
	pic_name = "resources/gargant.png";
	maxhp = 1000;			//Monster's max health points	
	hp = maxhp;			//Monster's current health points
	lvl = 0;			//Level of the Monster
	strength = 1;		//Monster's strength stat
	agility = 1;		//Monster's agility stat
	defense = 1;		//Monster's defense stat
	hearing = 3;
	movingUp = false;
	movingDown = false;
	movingLeft = false;
	movingRight = false;
	faceUp = false;
	faceDown = false;
	faceLeft = false;
	faceRight = false;

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
	
	movingUp = false;
	movingDown = false;
	movingLeft = false;
	movingRight = false;
	faceUp = false;
	faceDown = false;
	faceLeft = false;
	faceRight = false;

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

int Monster::getMaxHp(){
	return maxhp;
}
bool Monster::takeDamage(int dmg){
	 hp -= dmg;
	 if(hp > 0){
                 return true;
	         }
	 else{
                 return false;
	         }
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

bool Monster::movesUp(){
	return movingUp;
}
bool Monster::movesDown(){
	return movingDown;
}
bool Monster::movesLeft(){
	return movingLeft;
}
bool Monster::movesRight(){
	return movingRight;
}
void Monster::stopMove(){
	movingDown=false;
	movingLeft=false;
	movingRight=false;
	movingUp=false;
}

int Monster::faceWhere(){

	if(faceUp){
		return 1;
	}
	else if(faceDown){
		return 2;
	}
	else if(faceLeft){
		return 3;
	}
	else if(faceRight){
		return 4;
	}
	return 0;
}
void Monster::faceThere(int dir){

	switch(dir){
	case 1:
		faceUp=true;
		faceDown=false;
		faceLeft=false;
		faceRight=false;
		break;
	case 2:
		faceUp=false;
		faceDown=true;
		faceLeft=false;
		faceRight=false;
		break;
	case 3:
		faceUp=false;
		faceDown=false;
		faceLeft=true;
		faceRight=false;
		break;
	case 4:
		faceUp=false;
		faceDown=false;
		faceLeft=false;
		faceRight=true;
		break;
	}

}
void Monster::moveUp(){
	stopMove();
	movingUp=true;
	faceThere(1);
	position.y-=1;
}
void Monster::moveDown(){
	stopMove();
	movingDown=true;
	faceThere(2);
	position.y+=1;
}
void Monster::moveLeft(){
	stopMove();
	movingLeft=true;
	faceThere(3);
	position.x-=1;
}
void Monster::moveRight(){
	stopMove();
	movingRight=true;
	faceThere(4);
	position.x+=1;
}
void Monster::detectPlr(sf::Vector2f pos){
	detects_player = true;
	setTargetPos(pos);
}

void Monster::undetectPlr(){
	detects_player = false;
}

void Monster::setTargetPos(sf::Vector2f pos){
	target_pos = pos;
}

