#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>




class Item{
	public:
		//Item(std::string t, std::string n, int v, std::string i);
		std::string getName() const;
		int getValue() const;
		std::string getType() const;
		void changeValue(int newvalue); 
		std::string getImagename() const;
		std::string getDescription() const;
	protected:
		std::string name;
		int value;
		std::string type;
		std::string image;
		std::string description;
};

class Armor: public Item{
	public:
		Armor(std::string name, int value, std::string image,std::string description);

};

class Weapon: public Item{
	public:
		Weapon(std::string name, int value, std::string image, double hitchance,std::string description);
		double getHitchance();
	private:
		double hitchance;
};

#endif
