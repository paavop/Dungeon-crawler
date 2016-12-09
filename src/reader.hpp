/*rapeltaja Huotari*/

#ifndef _MYHEADER_H_
#define _MYHEADER_H_


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "item.hpp"

class Reader{
	public:
		Reader(std::string filename = "itemlist.txt");
		void push_item(Item itemi);
		std::vector<Item> get_items();
	private:
		std::vector<Item> items;
};


#endif

