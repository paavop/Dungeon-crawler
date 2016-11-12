

class Hero {
	public:
		Hero(int h, int s, int a, int d, int m);
		void gainExp(int e);
		void lvlUp(void);
		bool takeDamage(int dmg);
		void heal(int h);
		int getHp();
		int getStr();
		int getLvl();
		int getExp();
		int getExpToNext();
		int getAgi();
		int getMana();
		int getDef();
		
	private:
		int maxhp;			//Hero's max health points	
		int hp;				//Hero's current health points
		int lvl;			//Level of the hero
		int exp;			//Experience points
		int strength;		//Hero's strength stat
		int agility;		//Hero's agility stat
		int defense;		//Hero's defense stat
		int mana;			//Hero's mana stat
		int expToNextLvl;	//Needed exp to next lvl
		
};
		
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




	
	
