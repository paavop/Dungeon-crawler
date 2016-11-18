#include <string>
#include <iostream>




class Item{
	public:
		Item(std::string t, std::string n, int v, std::string i);
		std::string getName() const;
		int getValue() const;
		std::string getType() const;
		void changeValue(int newvalue); 
		std::string getImagename() const;
	private:
		std::string name;
		int value;
		std::string type;
		std::string image;
};

class Armor: public Item{
	public:
		Armor(std::string name, int value, std::string image);

};

class Weapon: public Item{
	public:
		Weapon(std::string name, int value, std::string image, double hitchance);
		double getHitchance() const;
	private:
		double hitchance;
};
