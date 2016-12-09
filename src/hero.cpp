#include "hero.hpp"

		
//Constructor
Hero::Hero(){
	maxhp=100;
	hp=maxhp;
	strength=5;
	agility=5;
	defense=5;
	mana=100;
	lvl=1;
	exp=0;
	expToNextLvl=1000;
	
	eqWepInd=-1;
	eqArmInd=-1;
}
Hero::Hero(int h, int s, int a, int d, int m){
	maxhp=h;
	hp=h;
	strength=s;
	agility=a;
	defense=d;
	mana=m;
	lvl=1;
	exp=0;
	expToNextLvl=1000;
	
	eqWepInd=-1;
	eqArmInd=-1;
}
bool Hero::equip(int itmInd){
	bool equipped=false;
	if(itmInd>=0 && itmInd<bag.size()){
		if(bag[itmInd].getType()=="Armor"){
			if(itmInd!=eqArmInd){
				if(eqArmInd!=-1){
					defense-=bag[eqArmInd].getValue();
				}
				equipped=true;
				eqArmInd=itmInd;
				defense+=bag[eqArmInd].getValue();
			}
		}
		if(bag[itmInd].getType()=="Weapon"){
			if(itmInd!=eqWepInd){
				if(eqWepInd!=-1){
					strength-=bag[eqWepInd].getValue();
				}
				equipped=true;
				eqWepInd=itmInd;
				strength+=bag[eqWepInd].getValue();
			}
		}
	}
	return equipped;
}
		
void Hero::gainExp(int e){
	exp+=e;
	if(exp>expToNextLvl){
		lvlUp();
	}
}
void Hero::lvlUp(void){
	lvl+=1;
	maxhp+=100;
	strength+=1;
	agility+=1;
	defense+=1;
	mana+=50;
	
}	

bool Hero::takeDamage(int dmg){
	hp-=dmg;

	if(hp>0){
		return true;
	}
	else{
		return false;
	}
}

void Hero::heal(int h){
	hp+=h;
	if(hp>maxhp){
		hp=maxhp;
	}
}

int Hero::getHp(){
	//std::cout<<hp<<std::endl<<std::flush;
	return hp;
}
int Hero::getMaxHp(){
	return maxhp;
}
int Hero::getStr(){
	return strength;
}
int Hero::getLvl(){
	return lvl;
}
int Hero::getExp(){
	return exp;
}
int Hero::getExpToNext(){
	return expToNextLvl;
}
int Hero::getAgi(){
	return agility;
}
int Hero::getMana(){
	return mana;
}
int Hero::getDef(){
	return defense;
}
bool Hero::addItem(Item itm){
	if(bag.size()>7){
		return false;
	}
	else{
		bag.push_back(itm);

		return true;
	}
}

std::vector<Item> Hero::getBag(){
	return bag;
}


	
	
