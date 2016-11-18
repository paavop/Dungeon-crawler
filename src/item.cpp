#include "item.hpp"

Weapon::Weapon(std::string name, int value, std::string image, double hitchance){
	this->name = name;
	this->value = value;
	this->type = "Weapon";
	this->image = image;
	this->hitchance = hitchance
}

Armor::Armor(std::string name, int value, std::string image){
	this->name = name;
	this->value = value;
	this->type = "Armor";
	this->image = image;
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