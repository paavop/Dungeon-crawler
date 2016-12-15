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
				bool gotDescription = false;

				std::string tmpname;
				std::string tmpimage;
				std::string tmpdescription;
				int tmpvalue;
				double tmphitchance;

				while(std::getline(open_file, newline) && newline!="}"){
					//newline.erase(std::remove_if(newline.begin(), newline.end(), isspace), newline.end());
					std::string delimiter = ":";
					if(newline.substr(0, newline.find(delimiter)) =="type"){
						std::string tmptype = newline.substr(newline.find(delimiter)+1);
						gotType = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="value"){
						std::string tmptmpvalue = newline.substr(newline.find(delimiter)+1);

						tmpvalue = std::stoi(tmptmpvalue);
						gotValue = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="image"){
						tmpimage = newline.substr(newline.find(delimiter)+1);
						gotImage = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="name"){
						tmpname = newline.substr(newline.find(delimiter)+1);


						gotName = true;
					}
					
					else if(newline.substr(0, newline.find(delimiter)) =="hitchance"){
						std::string tmptmphitchance = newline.substr(newline.find(delimiter)+1);

						tmphitchance = std::stod(tmptmphitchance);

						double tmphitchance = std::stod(tmptmphitchance);

						gotHitchance = true;
					}
					else if(newline.substr(0, newline.find(delimiter)) =="description"){

						tmpdescription=newline.substr(newline.find(delimiter)+1);

						

						gotDescription = true;
					}
				}
				
				if(gotType && gotValue && gotImage && gotName && !gotHitchance && gotDescription){
					items.push_back(new Armor(tmpname, tmpvalue, tmpimage, tmpdescription));
					
				}
				
				else if(gotType && gotValue && gotImage && gotName && gotHitchance && gotDescription){
					items.push_back(new Weapon(tmpname, tmpvalue, tmpimage, tmphitchance,tmpdescription));
					/*
					for(int i=0;i<items.size();i++){
						std::cout<<items[i]->getHitchance()<<"  "<<tmphitchance<<std::endl;
					}
					std::cout<<std::endl<<std::flush;
					*/
				}
				else{
					std::cout << "Itemin tiedot vialliset" << std::endl <<std::flush;
				}
			}
		}
	}
	else{
		std::cout << "Could not open the file: '" << filename << "'" << std::endl;
	}


}
/*
void Reader::push_item(Item itemi){
	items.push_back(itemi);
}
*/
std::vector<Item*> Reader::get_items(){

	return items;
}

