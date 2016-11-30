/*rapeltaja Huotari, Pertti Tuorila's reader modified*/
#include "reader.hpp"

Reader::Reader(std::string filename){
	//std::vector<Item> items;
	std::string newline;
	std::ifstream open_file(filename.c_str());
	if(open_file.is_open()){
		while(std::getline(open_file,newline)){
			newline.erase(std::remove_if(newline.begin(), newline.end(), isspace), newline.end());
			if(newline=="{"){
				bool gotType = false;
				bool gotValue = false;
				bool gotImage = false;
				bool gotName = false;
				bool gotHitchance = false;
				while(std::getline(open_file, newline) && newline!="}"){
					newline.erase(std::remove_if(newline.begin(), newline.end(), isspace), newline.end());
					std::string delimiter = ":";
					if(newline.substr(0, newline.find(delimiter)) =="type"){
						std::string tmptype = newline.substr(newline.find(delimiter)+1);
						gotType = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="value"){
						std::string tmptmpvalue = newline.substr(newline.find(delimiter)+1);
						int tmpvalue = std::stoi(tmptmpvalue);
						gotValue = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="image"){
						std::string tmpimage = newline.substr(newline.find(delimiter)+1);
						gotImage = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="name"){
						std::string tmpname = newline.substr(newline.find(delimiter)+1);
						gotName = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="hitchance"){
						std::string tmptmphitchance = newline.substr(newline.find(delimiter)+1);
						int tmphitchance = std::stoi(tmptmphitchance);
						gotHitchance = true;
					}
				}
				if(gotType && gotValue && gotImage && gotName && !gotHitchance){
					Armor::Armor jokuarmor(tmpname, tmpvalue, tmpimage);
					items.push_back(jokuarmor);
				}
				else if(gotType && gotValue && gotImage && gotName && gotHitchance){
					Weapon::Weapon jokuweapon (tmpname, tmpvalue, tmpimage, tmphitchance);
					items.push_back(jokuweapon);
				}
				else{
					std::cout << "Itemin tiedot vialliset" << std::endl;
				}
			}
		}
	}
	else{
		std::cout << "Could not open the file: '" << filename << "'" << std::endl;
	}

}

void Reader::push_item(Item itemi){
	items.push_back(itemi);
}

std::vector<Item> Reader::get_items(){
	return items;
}

/*
int main(){
	Reader keskiviikko();
	auto vektori1 = keskiviikko.get_items();
	std::string randomnimi = vektori1[0].getName();
	std::cout << randomnimi << std::endl;
}
*/