/*rapeltaja Huotari*/

#ifndef _MYHEADER_H_
#define _MYHEADER_H_


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "item.hpp"
#include "monster.hpp"

class Reader{
	public:
		Reader(std::string filename,std::string enemyfile);
		//void push_item(Item itemi);
		std::vector<Item*> get_items();
		std::vector<Monster> get_monsters();
	private:
		std::vector<Item*> items;
		std::vector<Monster> monsters;
};


#endif

