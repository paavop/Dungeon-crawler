#include "item.hpp"



Weapon::Weapon(std::string name, int value, std::string image, double hitchance,std::string description){
	this->name = name;
	this->value = value;
	type = "Weapon";
	this->image = image;
	this->hitchance = hitchance;
	this->description = description;
}

Armor::Armor(std::string name, int value, std::string image,std::string description){
	this->name = name;
	this->value = value;
	type = "Armor";
	this->image = image;
	this->description = description;
}

std::string Item::getDescription() const{
	return description;
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

double Weapon::getHitchance(){
	return hitchance;
}
double Armor::getHitchance(){
	return 0.0f;
}