#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

class Croupier {

	std::string croupiername;
	int ID = 0, win = 0, lose = 0, draw = 0;
	float profit = 0;
	unsigned short int main_croupiers = 5; ///LICZBA KRUPIEROW KTORZY SA ZAWSZE DOSTEPNI 
	
public:
	
	Croupier(std::vector<std::string> input) {
		ID = std::stoi(input[0]);
		croupiername = input[1];
		win= std::stoi(input[2]);
		lose= std::stoi(input[3]);
		draw= std::stoi(input[4]);
		profit= std::stoi(input[5]);
		
	}
	void Save_to_file();
	int get_ID() { return ID; }
	std::string get_name() { return croupiername; }
};