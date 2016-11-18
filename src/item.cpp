#include "item.hpp"

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