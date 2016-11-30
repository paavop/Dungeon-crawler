#include "item.hpp"



Weapon::Weapon(std::string name, int value, std::string image, double hitchance){
	name = name;
	value = value;
	type = "Weapon";
	image = image;
	hitchance = hitchance;
}

Armor::Armor(std::string name, int value, std::string image){
	name = name;
	value = value;
	type = "Armor";
	image = image;
}

std::string Item::getName() const{
	return name;
}

int Item::getValue() const{
	return value;
}

std::string Item::getType() const{
	return type;
}

void Item::changeValue(int newvalue){
	value = newvalue;
}

std::string Item::getImagename() const{
	return image;
}

double Weapon::getHitchance() const{
	return hitchance;
}
