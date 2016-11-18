/*File Reader by Pertti Tuorila*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


void PrinLine(std::string line){
	std::cout << line << std::endl;
}

void getKeyValuePair(std::string& current_line, std::vector<std::string>& pair){
	std::string delimiter = ":";
	std::string key = current_line.substr(0, current_line.find(delimiter));
	pair[0] = key;
	std::string value = current_line.substr(current_line.find(delimiter)+1);
	pair[1] = value;


}

void ReadArmor2File(const std::string& filename){

	std::string newline;
	PrinLine(filename);
	std::ifstream open_file(filename.c_str());

	bool isArmor = false;

	if (open_file.is_open()){
		while(std::getline(open_file,newline)){
			//PrinLine(newline);
			newline.erase(std::remove_if(newline.begin(), newline.end(), isspace), newline.end());

			if(newline == "{" && isArmor == false){
				isArmor = true;
				continue;
			}
			if(newline == "}" && isArmor == true){
				isArmor = false;
				continue;
			}
			if(isArmor == true){
				std::vector<std::string> pair(2);
				getKeyValuePair(newline, pair);
				std::cout<< "Key:" << pair[0] << "	Value:" << pair[1] << std::endl;

			}
		}
	}
	else{
		std::cout << "Could not open the file: '" << filename << "'" <<std::endl;
	}
}


int main(){
	std::string filename = "Armors";
	ReadArmor2File(filename);
	return 0;
}