#include "monster.hpp"

Monster::Monster(sf::Vector2i pos){
	alive = true;
	detects_player = false;
	position = pos;
	name = "Gargant";
	pic_name = "resources/gargant.png";
	maxhp = 100;			//Monster's max health points	
	hp = maxhp;			//Monster's current health points
	lvl = 0;			//Level of the Monster
	strength = 5;		//Monster's strength stat
	agility = 5;		//Monster's agility stat
	defense = 5;		//Monster's defense stat
	hearing = 3;
	movingUp = false;
	movingDown = false;
	movingLeft = false;
	movingRight = false;
	/*
	faceUp = false;
	faceDown = false;
	faceLeft = false;
	faceRight = false;
	*/

}

Monster::Monster(	int h, int s, int a, 
					int d,  int lvl, int hearing_radius,
					sf::Vector2i pos, std::string name,std::string image)
{
	alive = true;
	detects_player = false;
	name = name;
	position = pos;
	pic_name = image;
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
	/*
	faceUp = false;
	faceDown = false;
	faceLeft = false;
	faceRight = false;
	*/
}
void Monster::lvlUp(int lvl){
	this->lvl+=lvl;
	maxhp=maxhp*pow(1.3,lvl);
	hp=hp*pow(1.3,lvl);
	strength=strength*pow(1.3,lvl);
	agility=agility*pow(1.3,lvl);
	defense=defense*pow(1.3,lvl);
	
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
	moving_dir = Stop;
}

int Monster::faceWhere(){

	if(facing_dir == Up){
		return 1;
	}
	else if(facing_dir == Down){
		return 2;
	}
	else if(facing_dir == Left){
		return 3;
	}
	else if(facing_dir == Right){
		return 4;
	}
	return 0;
}
void Monster::faceThere(int dir){

	switch(dir){
	case 1:
		facing_dir = Up;
		break;
	case 2:
		facing_dir = Down;
		break;
	case 3:
		facing_dir = Left;
		break;
	case 4:
		facing_dir = Right;
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
void Monster::detectPlr(sf::Vector2i pos){
	detects_player = true;
	setTargetPos(pos);
}

void Monster::undetectPlr(){
	detects_player = false;
}

void Monster::setTargetPos(sf::Vector2i pos){
	target_pos = pos;
	target_freshness = 3;
}


bool Monster::canMove(std::vector<std::vector<int>>& map){
	
	switch(moving_dir)
	{
		case Up 	:return (map[position.x][position.y-1] == 0);
		case Right 	:return (map[position.x+1][position.y] == 0);
		case Down 	:return (map[position.x][position.y+1] == 0);
		case Left 	:return (map[position.x-1][position.y] == 0);
	}
	return false;
}

void Monster::moveTowardsTarget(std::vector<std::vector<int>>& map){
	int dx,dy, tx,ty,mx,my;
	//ARE THESE OBSOLETE?
	tx = target_pos.x;	 ty = target_pos.y;
	mx = position.x;	 my = position.y; 
	dx = target_pos.x - position.x;
	dy = target_pos.y - position.y;
	bool horizontal = false;
	if(std::abs(dx) > std::abs(dy)) horizontal = true;

	//std::cout << "Toimiiko:"<< horizontal<<  std::flush; //TESTING

	std::vector<int> dirs(2);
	if 		(dx>0) dirs[0] = 1;		//right
	else if (dx<0) dirs[0] = -1;	//left
	else		   dirs[0] = 0;
	if 		(dy>0) dirs[1] = 1;		//down
	else if (dy<0) dirs[1] = -1;	//up
	else		   dirs[1] = 0;

	//std::cout << " where2: " <<dirs[0]<<"x"<<dirs[1] <<std::endl<< std::flush;
	if (horizontal){
		if(dirs[0]==1) {
			moving_dir = Right;
			if(canMove(map)){
				//std::cout<<"RIGHT"<<std::endl<<std::flush;
				moveRight();
			}
		}
		else if(dirs[0]==-1) {
			moving_dir = Left;
			if(canMove(map)) {
				//std::cout<<"LEFT"<<std::endl<<std::flush;
				moveLeft();
			}
		}
	}
	else{
		if(dirs[1]==1) {
			moving_dir = Down;
			if(canMove(map)) {
				//std::cout<<"DOWN"<<std::endl<<std::flush;
				moveDown();
			}		}
		else if(dirs[1]==-1) {
			moving_dir = Up;
			if(canMove(map)) {
				//std::cout<<"UP"<<std::endl<<std::flush;
				moveUp();
			}
		}
	}


}

bool Monster::isFreshTarget(){
	if (target_freshness){
		target_freshness--;
		return true;
	}
	else return false;
}




/*
MonsterCatalog::MonsterCatalog() {}

MonsterCatalog::~MonsterCatalog(){
	for (std::list<MonsterCatalog*>::iterator it = monster_catalog_.begin();
		 it != monster_catalog_.end(); it++)
	{
		delete it;
	}
}
*/

