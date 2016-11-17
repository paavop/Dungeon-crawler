#include "hero.hpp"

		
//Constructor		
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
	return hp;
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




	
	
