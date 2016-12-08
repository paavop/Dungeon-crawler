#include "monster.hpp"

Monster::Monster(sf::Vector2i pos){
	alive = true;
	detects_player = false;
	position = pos;
	name = "risumies";
	pic_name = "resources/gargant.png";
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
					sf::Vector2i pos, std::string name)
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
sf::Vector2i Monster::getPos(){
	return position;
}
void Monster::setPos(unsigned int x, unsigned int y){
	position = sf::Vector2i(x,y);
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
	dir = Stop;
}

void Monster::moveUp(){
	movingUp=true;
	position.y-=1;
}
void Monster::moveDown(){
	movingDown=true;
	position.y+=1;
}
void Monster::moveLeft(){
	movingLeft=true;
	position.x-=1;
}
void Monster::moveRight(){
	movingRight=true;
	position.x+=1;
}
void Monster::detectPlr(sf::Vector2i pos){
	detects_player = true;
	setTargetPos(pos);
}

void Monster::undetectPlr(){
	detects_player = false;
}

void Monster::setTargetPos(sf::Vector2i pos){
	target_pos = pos;
}


bool Monster::canMove(std::vector<std::vector<int>>& map){
	

	switch(dir)
	{
		case Up 	:return !(map[position.y-1][position.x]);
		case Right 	:return !(map[position.y][position.x+1]);
		case Down 	:return !(map[position.y+1][position.x]);
		case Left 	:return !(map[position.y][position.x-1]);
	}
}

void Monster::moveTowardsTarget(std::vector<std::vector<int>>& map){
	int dx,dy, tx,ty,mx,my;
	tx = target_pos.x;	 ty = target_pos.y;
	mx = position.x;	 my = position.y; 
	dx = tx - mx;
	dy = ty - my;
	bool horizontal = false;
	if(std::abs(dx) > std::abs(dy)) horizontal = true;

	std::vector<int> dirs(2);
	if 		(dx>0) dirs[0] = 1;		//right
	else if (dx<0) dirs[0] = -1;	//left
	else		   dirs[0] = 0;
	if 		(dy>0) dirs[1] = 1;		//down
	else if (dy<0) dirs[1] = -1;	//up
	else		   dirs[1] = 0;

	if (horizontal){
		if(dirs[0]==1) {
			dir = Right;
			if(canMove(map)) moveRight();
		}
		else if(dirs[0]==-1) {
			dir = Left;
			if(canMove(map)) moveLeft();
		}
	}
	else{
		if(dirs[1]==1) {
			dir = Down;
			if(canMove(map)) moveDown();
		}
		else if(dirs[1]==-1) {
			dir = Up;
			if(canMove(map)) moveUp();
		}
	}


}

