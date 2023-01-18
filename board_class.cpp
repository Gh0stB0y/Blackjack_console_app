#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include "board_class.h"
#include <vector>
#include <fstream>
#include <cstdlib>

Board_BJ::Board_BJ(unsigned int input) {

	size_t pos = 0, variable_count = 0;
	std::string delimiter = "/", token;
	std::ifstream tab_data;
	
	tab_data.open("games_tables_data.bin", std::ios::in);

	std::string linia_plik;
	std::vector<std::string> tables_data;
	bool found = false;
	while (getline(tab_data, linia_plik) &&found==false) {		//TU SIE ZACZYNA SPRAWDZANIE CALEJ LINII
		pos = 0;
		variable_count = 0;
		tables_data.clear();
		bool access = true;

		while ((pos = linia_plik.find(delimiter)) != std::string::npos && access==true) {	//SPRAWDZENIE DANYCH Z LINII ODDZIELONYCH DELIMITEREM
			token = linia_plik.substr(0, pos);
			//std::cout << token <<std::endl;

			if (variable_count == 0 && std::stoi(token) == input) {
				access = true;
				found = true;
				//std::cout << "acces granted" << std::endl;
			}
			else if (variable_count == 0 && std::stoi(token) != input) {
				access = false;
				//std::cout << "acces denied" << std::endl;
			}
				linia_plik.erase(0, pos + delimiter.length());
				variable_count++;
				tables_data.push_back(token);//wpisz dane do vectora tables_data
		}
	}
	//std::cout << "rozmiar wektora: " << tables_data.size()<<std::endl;
	//ODCZYTYWANIE WARTOSCI Z PLIKU PO KOLEI
	tab_data.close();
	tabID = std::stoi(tables_data[0]); min_lvl = std::stoi(tables_data[1]); max_seats = std::stoi(tables_data[2]); max_seats_one_person= std::stoi(tables_data[3]);
	min_entry = std::stoi(tables_data[4]); max_entry = std::stoi(tables_data[5]);win= std::stoi(tables_data[6]); lose = std::stoi(tables_data[7]);
	winratio = std::stoi(tables_data[8]); cash_profit = std::stof(tables_data[9]); bots = std::stoi(tables_data[10]);
	draw = std::stof(tables_data[11]); BJ = std::stof(tables_data[12]); side_bets = std::stoi(tables_data[13]); shoe_size = stoi(tables_data[14]);
	//
	//deck.resize(52*shoe_size,"");
	cards_croupier.resize(2, "As serce");
	cards_players.resize(2 * max_seats, "2 wino");
	bets_players.resize(max_seats, 0);
	side_bets_players.resize(max_seats * 2, 0);
	empty_seat.resize(max_seats,1);
	all_cards.resize(52, shoe_size);
}
void Board_BJ::Disp_table(Player& play1) {
	system("CLS");
	Sleep(3000);
	for (size_t i = 0; i < max_seats*10-10; i++) std::cout << " ";
	
	std::cout << "KRUPIER\n";

	for (size_t i = 0; i < max_seats*10-10; i++) std::cout << " ";
	std::cout << this->cards_croupier[0]<<"\n";
	for (size_t i = 0; i < max_seats*10-10; i++) std::cout << " ";
	std::cout << this->cards_croupier[1] << "\n\n\n";

	for (size_t i = 0; i < max_seats; i++) {
	std::cout << this->cards_players[2*i];
	for (size_t j = 0; j < 20 - cards_players[2 * i].size(); j++) {
		std::cout << " ";
	}
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {
	std::cout << this->cards_players[2*i+1];
	for (size_t j = 0; j < 20 - cards_players[2 * i+1].size(); j++) {
		std::cout << " ";
	}
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {

		std::stringstream wypisz;
		wypisz << "Miejsce " << i + 1;
		std::cout << wypisz.str();
		for (size_t j = 0; j < 20 - wypisz.str().size(); j++) std::cout << " ";
		
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {
		if (empty_seat[i] == 1) {
			std::cout << "Wolne               ";
		}
		else play1.Get_username();
	
		
	}
	for (size_t i = 0; i < max_seats + 1; i++) std::cout << "\t";
	std::cout << "\n\n";
	
	Sleep(2000);
}
void Board_BJ::shuffle_cards() {

	deck.clear();
	all_cards.clear();
	all_cards.resize(52, shoe_size);
	bool repeat = 0;
	int pick_card=0, pick_card2=0, limit=0;
	std::vector<int> cards_available;
	cards_available.clear();
	for (size_t j = 0; j < 52; j++)  cards_available.push_back(j);
	for (size_t i = 0; i < this->shoe_size*52; i++) {
		//std::cout << "Licznik kart: " << i + 1;
		do {
			//std::cout << "cards available size: " << cards_available.size();
			if (cards_available.size() > 1) pick_card = rand() % (cards_available.size() - 1);
			else pick_card = 0;
			//std::cout << "pick card: " << pick_card << std::endl;	
			pick_card2 = cards_available[pick_card];
			//std::cout << "all_cards[pick_card2]: " << all_cards[pick_card2] << std::endl;;
			if (all_cards[pick_card2] > 0) {
				deck.push_back(card_name[pick_card2]);
				all_cards[pick_card2]--;
				repeat = 0;
			}
			else {
				repeat = 1;
				cards_available.erase(cards_available.begin() + pick_card);
			}
		} while (repeat);
		std::cout << deck[i]<<"\t"<<i<<"\n";
	}
	std::cout << "losowanie zakonczone";
	Sleep(2000);
	//for (size_t i = 0; i < deck.size(); i++) std::cout << deck[i] << std::endl;
	
}
void Board_BJ::play_game() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_BJ::croupier_change() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_BJ::bet() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}

Board_roulette::Board_roulette(int input) {

	std::cout << "OBJECT POWSTAL" << std::endl;
	Sleep(2000);
}
void Board_roulette::Disp_table(Player& play1) {
	std::cout << "TEST ROULTTE" << std::endl;
	Sleep(2000);
}
void Board_roulette::shuffle_cards() { std::cout << "funkcja pusta"; }
void Board_roulette::play_game() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::croupier_change() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::bet() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}

Board_bacarrat::Board_bacarrat(int input) {

	std::cout << "OBJECT POWSTAL" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::Disp_table(Player& play1) {
	std::cout << "TEST Bacarrat" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::shuffle_cards() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::play_game() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::croupier_change() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::bet() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}

Board_poker::Board_poker(int input) {

	std::cout << "OBJECT POWSTAL" << std::endl;
	Sleep(2000);
}
void Board_poker::Disp_table(Player& play1) {
	std::cout << "TEST poker" << std::endl;
	Sleep(2000);
}
void Board_poker::shuffle_cards() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::play_game() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::croupier_change() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::bet() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}

Board_war::Board_war(int input) {

	std::cout << "OBJECT POWSTAL" << std::endl;
	Sleep(2000);
}
void Board_war::Disp_table(Player& play1) {
	std::cout << "TEST war" << std::endl;
	Sleep(2000);
}
void Board_war::shuffle_cards() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::play_game() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::croupier_change() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::bet() {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
