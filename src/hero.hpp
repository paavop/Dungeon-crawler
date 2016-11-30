#include "item.hpp"
#include <vector>

class Hero {
	public:
		Hero();
		Hero(int h, int s, int a, int d, int m);
		void gainExp(int e);
		void lvlUp(void);
		bool takeDamage(int dmg);
		void heal(int h);
		int getHp();
		int getMaxHp();
		int getStr();
		int getLvl();
		int getExp();
		int getExpToNext();
		int getAgi();
		int getMana();
		int getDef();
		bool addItem(Item itm);
		std::vector<Item> getBag();
		
	private:
		std::vector<Item> bag;  //Hero's available items
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
