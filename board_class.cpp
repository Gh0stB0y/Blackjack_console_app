#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include "board_class.h"
#include <vector>
#include <fstream>
#include <cstdlib>s
#include "class_croupier.h"
#include <conio.h>

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

	cards_players.resize(max_seats);
	cards_players_value.resize(max_seats);
	for (size_t i = 0; i < max_seats; i++) {
		cards_players[i].resize(2, "");
		cards_players_value[i].resize(2, 0);	
	}
	cards_croupier.resize(2,"");
	cards_croupier_value.resize(2,0);
	bets_players.resize(max_seats*3, 0);
	bets_bots.resize(max_seats*3, 0);
	empty_seat.resize(max_seats,1);
	empty_seat_player.resize(max_seats, 1);
	all_cards.resize(52, shoe_size);
	suma_player.resize(max_seats);

}
void Board_BJ::Disp_table(Player& play1) {
	system("CLS");
	short int space=30;
	play1.Game_data();
	std::cout << "Zagrane karty: " << cards_played << " Zostalo w decku: " << deck.size() << " Zostalo w decku2: " << deck_value.size()<<"Red card: "<< red_card_deck <<std::endl;
	for (size_t i = 0; i < max_seats * (space/2) - (space / 2); i++) std::cout << " ";
	std::cout << "KRUPIER\n";

	for (size_t k = 0; k < cards_croupier.size(); k++) {
		for (size_t i = 0; i < max_seats * (space / 2) - (space / 2); i++) std::cout << " ";
		std::cout << this->cards_croupier[k] << "\n";
	}
	for (size_t i = 0; i < max_seats * (space / 2) - (space / 2)+3; i++) std::cout << " ";
	std::cout << this->suma_croupier << "\n";
	unsigned short int ile_spacji;
	if (6 - cards_croupier.size() < 1)ile_spacji = 1;
	else ile_spacji = 6 - cards_croupier.size();
	for (size_t k = 0; k < ile_spacji; k++) { std::cout << "\n"; }
	
	
	for (size_t k = 0; k < cards_players[0].size(); k++) {
		for (size_t i = 0; i < max_seats; i++) {
			std::cout << this->cards_players[i][k];
			for (size_t j = 0; j < space - cards_players[i][k].size(); j++) { std::cout << " "; }
		}
		std::cout << "\n";
	}
		
	for (size_t i = 0; i < max_seats; i++) {

		std::stringstream wypisz;
		int suma_kart = 0,ile_asow=0;
		for (size_t k = 0; k < cards_players_value[i].size(); k++) { 
			suma_kart += cards_players_value[i][k]; 
		}
		for (size_t n = 0; n < cards_players_value[i].size(); n++) {
			if (cards_players_value[i][n] == 11) ile_asow++;
		}
		while(suma_kart > 21&& ile_asow>0) {
			suma_kart -= 10;
			ile_asow--;
		}


		if(suma_kart==0) wypisz << "";
		else wypisz << suma_kart;
		std::cout << wypisz.str();
		for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
	}
	std::cout << "\n\n";
	
	for (size_t i = 0; i < max_seats; i++) {

		std::stringstream wypisz;
		wypisz << "Miejsce " << i+1;
		std::cout << wypisz.str();
		for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {
		if (empty_seat_player[i] == 1) {
			std::stringstream wypisz;
			wypisz << "Wolne ";
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
		}
		else {
			std::stringstream wypisz;
			wypisz << play1.Get_username();
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
		}
		
	}
	std::cout << "\n\n";
	for (size_t i = 0; i < max_seats; i++) {

		std::stringstream wypisz;
		wypisz << "Bet: " << bets_players[3*i];
		std::cout << wypisz.str();
		for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
	}
	std::cout << "\n";
	//for (size_t i = 0; i < max_seats + 1; i++) std::cout << "\t";
	if (side_bets == 1) {
		for (size_t i = 0; i < max_seats; i++) {

			std::stringstream wypisz;
			wypisz << "21+3: " << bets_players[(3*i)+1];
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
		}
		std::cout << "\n";
		for (size_t i = 0; i < max_seats; i++) {

			std::stringstream wypisz;
			wypisz << "Perfect pairs: " << bets_players[(3 * i)+2];
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
			
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	
	
}
void Board_BJ::shuffle_cards() {

	//FAZA TASOWANIA KART
	system("CLS");
	std::cout << "Krupier tasuje karty..." << std::endl;
	Sleep(5000);
	deck.clear();
	deck_value.clear();
	all_cards.clear();
	all_cards.resize(52, shoe_size);
	red_card_deck = 0;
	cards_played = 0;
	bool repeat = 0;
	int pick_card=0, pick_card2=0, limit=0;
	std::vector<int> cards_available;
	cards_available.clear();
	srand((unsigned)time(NULL));
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
				deck_value.push_back(card_value[pick_card2]);
				all_cards[pick_card2]--;
				repeat = 0;
			}
			else {
				repeat = 1;
				cards_available.erase(cards_available.begin() + pick_card);
			}
		} while (repeat);
	}
	//
	//PRZEDZIELENIE CZERWONA KARTA 
	short unsigned int red_card_min = shoe_size * 52 * 0.1, red_card_max = shoe_size * 52 * 0.9,red_card=shoe_size*26, red_card_cut=50;
	bool error_cin = false;
	do {
		system("CLS");
		error_cin = false;
		std::cout << "Przedziel deck czerwona karta,wybierz liczbe od " << red_card_min << " do " << red_card_max << std::endl;
		std::cin >> red_card;
		if (red_card >= red_card_min && red_card <= red_card_max) {}
		else {
			std::cin.clear(); std::cin.ignore(100, '\n');
			error_cin = true;
			red_card = 0;
			std::cout << "Nie wpisales odpowiedniej liczby, sprobuj ponownie" << std::endl;
			Sleep(3000);
		}
	} while (error_cin);

	std::vector<std::string> deck_temp;
	std::vector<int> deck_value_temp;
	for (size_t i = 0; i < red_card; i++) {
		deck_temp.push_back(deck[i]);
		deck_value_temp.push_back(deck_value[i]);
	}
	deck.erase(deck.begin(), deck.begin() + red_card);
	deck_value.erase(deck_value.begin(), deck_value.begin() + red_card);
	for (size_t i = 0; i < deck_temp.size(); i++) {
		deck.push_back(deck_temp[i]);
		deck_value.push_back(deck_value_temp[i]);
	}
	red_card_cut=52*shoe_size*0.75;
	red_card_deck = red_card_cut;
	//spalenie pierwszej karty
	deck.erase(deck.begin());
	deck_value.erase(deck_value.begin());
	cards_played++;
	std::cout << "losowanie zakonczone\n\n";
	Sleep(2000);
	//////
}
void Board_BJ::play_game(Player& play1, Croupier*& croupier) {
	this->Disp_table(play1);
	std::vector<bool> seat_play;
	std::vector<int> split_count;
	seat_play.resize(max_seats, 0);
	split_count.resize(max_seats, 0);
	bool show_card = 0;
	std::string hidden_card = "";
	int hidden_card_value = 0;
	std::vector<bool>insurance;
	std::vector<float>insurance_value;
	std::vector<int> ace_counter;
	ace_counter.resize(max_seats, 0);
	insurance.resize(max_seats, 0);
	insurance_value.resize(max_seats, 0);
	std::vector<int> suma;
	suma.resize(max_seats, 0);
	//rozpoznanie gdzie krupier ma polozyc karty
	for (size_t i = 0; i < max_seats; i++) {
		if (bets_players[3 * i] > 0 || bets_bots[3 * i] > 0 || bets_players[3 * i + 1] > 0 || bets_bots[3 * i + 1] > 0 || bets_players[3 * i + 2] > 0 || bets_bots[3 * i + 2] > 0) { seat_play[i] = 1; }
	}
	//wykladanie kart
	for (size_t k = 0; k < 2; k++) {
		for (size_t i = 0; i < max_seats; i++) {

			if (seat_play[max_seats - 1 - i] == 1) {
				cards_players[max_seats - 1 - i][k] = deck.front();
				deck.erase(deck.begin());
				cards_players_value[max_seats - 1 - i][k] = deck_value.front();
				deck_value.erase(deck_value.begin());
				cards_played++;
				this->Disp_table(play1);
				Sleep(750);
			}
			else { cards_players[max_seats - 1 - i][k] = ""; cards_players_value[max_seats - 1 - i][k] = 0; }
		}
		cards_croupier[k] = deck.front();
		deck.erase(deck.begin());
		cards_croupier_value[k] = deck_value.front();
		deck_value.erase(deck_value.begin());
		cards_played++;

		if (k == 1) {
			hidden_card = cards_croupier[1];
			hidden_card_value = cards_croupier_value[1];
			cards_croupier[1] = "zakryta karta";
			cards_croupier_value[1] = 0;
		}
		this->Disp_table(play1);
		Sleep(750);

	}
	suma_croupier = cards_croupier_value[0];
	
	//SPRAWDZENIE SIDE BETOW
	if (side_bets == 1) {
		check_sideBet(play1, croupier);
		for (size_t i = 0; i < max_seats; i++) {
			if (bets_players[3 * i] == 0)seat_play[i] = 0;
		}
	}
	// 
	
	//DECYZJA ODNOSNIE UBEZPIERCZENIA
	for (size_t j = 0; j < max_seats; j++) {

		if (cards_croupier_value[0] == 11 && bets_players[3 * j] > 0) {

			if (cards_players_value[j][0] + cards_players_value[j][1] < 21) {


				if (play1.bankroll >= bets_players[3 * j] / 2)insurance[(j)] = this->insurance(play1, j);
				else { insurance[j] = 0; }
				if (insurance[j] == 1) {
					insurance_value[j] = bets_players[3 * j] / 2; play1.bankroll -= insurance_value[j]; play1.profit -= insurance_value[j]; this->cash_profit += insurance_value[j]; croupier->profit += insurance_value[j];
				}
				else { insurance_value[j] = 0; }
			}
			else {
				char choice;
				bool ins_error = 0;
				do {
					ins_error = 0;
					std::cout << "Miejsce " << j + 1 << ": Proponuje wyplate wygranej 1:1. Zgadzasz sie?" << std::endl << "1. Tak\t2. Nie" << std::endl;
					choice = _getch();
					if (choice - 48 == 1) {
						seat_play[j] = 0; play1.bankroll += 2 * bets_players[3 * j]; play1.profit += 2 * bets_players[3 * j]; play1.BJ_win++; play1.BJ_games++; play1.BJ_BJ++; this->lose++; this->cash_profit -= 2 * bets_players[3 * j]; croupier->profit -= 2 * bets_players[3 * j]; croupier->lose++; std::cout << "Gratulacje, wygrywasz " << 2 * bets_players[3 * j] << "!" << std::endl; Sleep(2000); bets_players[3 * j] = 0;
					}
					else if (choice - 48 == 2) { std::cout << "Odrzucono propozycje, gramy dalej" << std::endl; Sleep(2000); }
					else {
						this->Disp_table(play1);
						ins_error = 1;
						std::cout << "ZLE! Podaj numer od 1 do 2" << std::endl;
						Sleep(2000);
					}
				} while (ins_error);
			}

		}
	}
	//
	//WERYFIKACJA BLACKJACKA KRUPIERA
	if (cards_croupier_value[0] == 11) {
		if (hidden_card_value == 10) {//blackjack krupiera
			for (size_t j = 0; j < max_seats; j++) {
				if (bets_players[3 * j] > 0 && seat_play[j] == 1) {
					if (cards_players_value[j][0] + cards_players_value[j][1] < 21) {
						if (insurance[j] == 1) { seat_play[j] == 0; bets_players[3 * j] = 0; play1.bankroll += insurance_value[j] * 3; play1.profit += insurance_value[j] * 3; play1.BJ_lose++; play1.BJ_games++; this->BJ++; this->win++; this->cash_profit -= insurance_value[j] * 3; croupier->profit -= insurance_value[j] * 3; croupier->win++; } //przegrana z ubezpieczeniem
						else { seat_play[j] = 0; bets_players[3 * j] = 0; play1.BJ_lose++; play1.BJ_games++; this->BJ++; this->win++; croupier->win++; } //przegrana bez ubezpieczenia
					}
					else { seat_play[j] = 0; play1.bankroll += bets_players[3 * j]; play1.profit += bets_players[3 * j]; play1.BJ_games++; play1.BJ_draw++; play1.BJ_BJ++; this->cash_profit -= bets_players[3 * j]; this->draw++; this->BJ++; croupier->profit -= bets_players[3 * j]; croupier->draw++; bets_players[3 * j] = 0; }//remis blackjack vs blackjack

				}
			}
			std::cout << "Blackjack u krupiera!" << std::endl;
			Sleep(2000);
			cards_croupier[1] = hidden_card;
			cards_croupier_value[1] = hidden_card_value;
			this->Disp_table(play1);
			Sleep(3000);
		}
		else { //brak blackjacka u krupiera
			std::cout << "Brak blackjacka u krupiera" << std::endl; Sleep(2000);
			for (size_t j = 0; j < max_seats; j++) {
				if (cards_players_value[j][0] + cards_players_value[j][1] == 21 && seat_play[j] == 1) {
					seat_play[j] = 0; play1.bankroll += bets_players[3 * j] * 2.5; play1.profit += bets_players[3 * j] * 2.5; play1.BJ_BJ++; play1.BJ_win++; play1.BJ_games++; this->cash_profit -= bets_players[3 * j] * 2.5; this->lose++; croupier->lose++; croupier->profit -= bets_players[3 * j] * 2.5; bets_players[3 * j] = 0;
					std::cout << "Blackjack dla gracza na miejscu " << j + 1 << "!" << std::endl << std::endl; Sleep(2000);
				}
			}
		}
	}

	//BLACKJACK U GRACZA BEZ ASA U KRUPIERA
	for (int j = max_seats - 1; j >= 0;) {

		if (cards_players_value[j][0] + cards_players_value[j][1] == 21 && seat_play[j] == 1) {
			seat_play[j] = 0; play1.bankroll += bets_players[3 * j] * 2.5; play1.profit += bets_players[3 * j] * 2.5; play1.BJ_BJ++; play1.BJ_win++; play1.BJ_games++; this->cash_profit -= bets_players[3 * j] * 2.5; this->lose++; croupier->lose++; croupier->profit -= bets_players[3 * j] * 2.5; bets_players[3 * j] = 0;
			std::cout << "Blackjack dla gracza na miejscu " << j + 1 << "!" << std::endl << std::endl; Sleep(2000);
		}
		j--;
	}
	//

	
	
	for (size_t i = 0; i < max_seats; i++) {
		for (size_t j = 0; j < cards_players_value[i].size(); j++) {
			if (cards_players_value[i][j] == 11) ace_counter[i]++;
		}
	}

	//decyzje gracza
	for (int j = max_seats - 1; j >= 0;) {
		
		int decision_counter = 0, decisions = 2, cards_for_player = 2;
		bool decision_finish = 0, decision_error = 0;
		
		char choice = 0;
		for (size_t i = 0; i < cards_players_value[j].size(); i++) suma[j] += cards_players_value[j][i];//zliczenie wartosci kart
		//this->Disp_table(play1);
		do {
			
			
			//cards_for_player = 2;
			
			if (seat_play[j] == 1) {
				
				do {
					//menu decyzji
					this->Disp_table(play1);
					//
					for (size_t i = 0; i < max_seats; i++) std::cout << "seat_play: "<<seat_play[i]<<"                  ";
					std::cout << std::endl;
					//for (size_t i = 0; i < max_seats; i++) std::cout << "Ace_counter: " << ace_counter[i] << "                ";
					//std::cout<<std::endl;
					//
					decision_error = 0;
					decisions = 2;
					std::cout << "Miejsce " << j + 1 << ": Prosze podjac decyzje:" << std::endl << "1. Dobierz\t2. Pasuj";
					if (decision_counter == 0) { std::cout << "\t3. Podwojenie"; decisions++; }
					if (cards_players_value[j][0] == cards_players_value[j][1] && decision_counter == 0) { std::cout << "\t4. Rozdziel karty"; decisions++; }
					std::cout << std::endl;
					Sleep(500);
					choice = _getch();

					if (choice - 48 == 1) {//dobierz
						decision_error = 0;
						cards_for_player++;
						decision_counter++;
						cards_played++;
						for (size_t n = 0; n < max_seats; n++) {
							if (cards_for_player > cards_players[n].size()) {
								cards_players[n].resize(cards_for_player, "");
								cards_players_value[n].resize(cards_for_player, 0);
							}
						}
						cards_players[j][cards_for_player -1]=deck.front();
						cards_players_value[j][cards_for_player - 1]=deck_value.front();
						if (cards_players_value[j][cards_for_player - 1]==11)ace_counter[j]++;
						deck.erase(deck.begin());
						deck_value.erase(deck_value.begin());				
						suma[j] += cards_players_value[j][cards_for_player - 1];
						if (suma[j] > 21) {
							if (ace_counter[j] > 0) {
								suma[j] -= 10; ace_counter[j]--;
							}
							else {
								bets_players[3 * j] = 0; decision_finish = 1; seat_play[j] = 0; play1.BJ_games++; play1.BJ_lose++; this->win++; croupier->win++;
							this->Disp_table(play1); std::cout << "Za duzo! Przegrywasz rozdanie..." << std::endl; Sleep(2000); 
							}
						}
						if (suma[j] == 21) { decision_finish = 1; this->Disp_table(play1); std::cout << "21!" << std::endl; Sleep(2000); }
					}
					else if (choice - 48 == 2) { decision_counter++; decision_finish = 1;}//pasuj
					else if (choice - 48 == 3) {//podwojenie
						if (decisions > 2) {//jesli podwojenie jest mozliwe
							if (play1.bankroll>=bets_players[3*j]) {
								decision_error = 0;
								cards_for_player++;
								decision_counter++;
								cards_played++;
								play1.bankroll -= bets_players[3 * j];play1.profit-= bets_players[3 * j];this->cash_profit+=bets_players[3 * j];croupier->profit += bets_players[3 * j];
								bets_players[3 * j]= bets_players[3 * j]*2;
								for (size_t n = 0; n < max_seats; n++) {
									if (cards_for_player > cards_players[n].size()) {
										cards_players[n].resize(cards_for_player, "");
										cards_players_value[n].resize(cards_for_player, 0);
									}
								}
								cards_players[j][cards_for_player - 1] = deck.front();
								cards_players_value[j][cards_for_player - 1] = deck_value.front();
								if (deck_value.front() == 11)ace_counter[j]++;
								deck.erase(deck.begin());
								deck_value.erase(deck_value.begin());
								suma[j] += cards_players_value[j].back();
								decision_finish = 1;
								if (suma[j] > 21) {
									if (ace_counter[j] > 0) {
									suma[j] -= 10;
									ace_counter[j]--; 
									this->Disp_table(play1);
									}
									else {
									this->Disp_table(play1);
									bets_players[3 * j] = 0; seat_play[j] = 0; play1.BJ_games++; play1.BJ_lose++; this->win++; croupier->win++;
									std::cout << "Za duzo! Przegrywasz rozdanie..." << std::endl; Sleep(2000); 
									}
								}
								else if (suma[j] == 21) { this->Disp_table(play1); std::cout << "21!" << std::endl; Sleep(2000); }
								else { this->Disp_table(play1); }
							}
							else {
								decision_error = 1;
								std::cout << "Masz za malo gotowki..."<< std::endl;
								Sleep(2000);
							}
						}
						else {//jesli podwojenie jest niemozliwe
							decision_error = 1;
							std::cout << "ZLE! Podaj numer od 1 do " << decisions << std::endl;
							Sleep(2000);
						}
					}
					else if (choice - 48 == 4) { //rozdziel karty
						if (decisions > 3) {//jesli rozdzielenie jest mozliwe
						
							split_count.push_back(0);
							for(size_t k=0;k< split_count.size();k++){if (k >= j)split_count[k]++;}
							
						}
						else{//jesli rozdzielenie jest niemozliwe
							decision_error = 1;
							std::cout << "ZLE! Podaj numer od 1 do " << decisions << std::endl;
							Sleep(2000);
						}
					}
					else {//jesli wpisano nieodpowiednia liczbe/znak
						decision_error = 1;
						std::cout << "ZLE! Podaj numer od 1 do " << decisions << std::endl;
						Sleep(2000);
					}
				} while (decision_error);

				if (suma[j] > 21) {}


			}
			else decision_finish = 1; 
		} while (!decision_finish);
		j--;
	}
	
	//dobieranie krupiera
	std::cout << "Koniec dobierania kart przez graczy" << std::endl;
	Sleep(2000);

	cards_croupier[1] = hidden_card;
	cards_croupier_value[1] = hidden_card_value;
	


		
	bool draw_finish = 1;
	int ace_counter_croupier = 0;
	suma_croupier = 0;
	for (size_t j = 0; j < cards_croupier_value.size(); j++) {
		if (cards_croupier_value[j] == 11) ace_counter_croupier++;
	}

	
	for (size_t i = 0; i < max_seats; i++) {if (seat_play[i] == 1)draw_finish = 0;}
	for (size_t i = 0; i < cards_croupier_value.size(); i++) suma_croupier += cards_croupier_value[i];
	if (suma_croupier >= 17)draw_finish = 1;
	this->Disp_table(play1);

	Sleep(3000);
	while (!draw_finish) {

		cards_croupier.push_back(deck.front());
		deck.erase(deck.begin());
		cards_croupier_value.push_back(deck_value.front());
		if (cards_croupier_value[cards_croupier_value.size()-1] == 11)ace_counter_croupier++;
		suma_croupier += deck_value.front();
		deck_value.erase(deck_value.begin());
		cards_played++;

		if (suma_croupier >= 27 && ace_counter_croupier > 0) { ace_counter_croupier--; suma_croupier -= 10; draw_finish = 1; }
		if (suma_croupier > 21 && suma_croupier < 27 && ace_counter_croupier > 0) { ace_counter_croupier--; suma_croupier -= 10; }
		if (suma_croupier >= 17 && ace_counter_croupier==0)  {draw_finish = 1;}
		this->Disp_table(play1);
		Sleep(500);
	}
	
	//
	//sprawdzenie kto wygral 
	if (suma_croupier > 21) {
		for (size_t i = 0; i < max_seats; i++) {
			if (seat_play[i] == 1) { seat_play[i] = 0; play1.bankroll +=2* bets_players[3 * i]; play1.profit += 2*bets_players[3 * i]; play1.BJ_games++; play1.BJ_win++; this->cash_profit -=2* bets_players[3 * i]; this->lose++; croupier->profit -= 2*bets_players[3 * i]; croupier->lose++; bets_players[3 * i] = 0;
			
			}
		}
		std::cout << "Krupier dobral za duzo, gratuluje wygranych" << std::endl;
	}
	else {
		for (size_t i = 0; i < max_seats; i++) {
			if (seat_play[i] == 1) {
				if (suma_croupier > suma[i])//krupier ma wiecej niz gracz
				{
					seat_play[i] = 0; play1.BJ_games++; play1.BJ_lose++; this->win++; croupier->win++; bets_players[3 * i] = 0;
					std::cout <<"Miejsce  "<<i+1<<": Krupier wygral!" << std::endl;
				}
				else if (suma_croupier == suma[i]) //krupier ma tyle samo co gracz
				{
					seat_play[i] = 0; play1.bankroll += bets_players[3 * i]; play1.profit += bets_players[3 * i]; play1.BJ_games++; play1.BJ_draw++; this->cash_profit -= bets_players[3 * i]; this->draw++; croupier->profit -= bets_players[3 * i]; croupier->draw++; bets_players[3 * i] = 0;
					std::cout << "Miejsce  " << i + 1 << ": Remis" << std::endl;
				}
				else //krupier ma mniej niz gracz
				{
					seat_play[i] = 0; play1.bankroll += 2 * bets_players[3 * i]; play1.profit += 2 * bets_players[3 * i]; play1.BJ_games++; play1.BJ_win++; this->cash_profit -= 2 * bets_players[3 * i]; this->lose++; croupier->profit -= 2 * bets_players[3 * i]; croupier->lose++; bets_players[3 * i] = 0;
					std::cout << "Miejsce  " << i + 1 << ": Krupier dobral za malo, gratuluje wygranej" << std::endl;
				}
			}
		}
	}


	//koniec

	Sleep(3000);
	split_count.clear();
	cards_players.clear();
	cards_players_value.clear();
	cards_croupier.clear();
	cards_croupier_value.clear();
	bets_players.clear();
	bets_bots.clear();
	insurance.clear();
	insurance_value.clear();
	seat_play.clear();
	cards_croupier.resize(2,"");
	cards_croupier_value.resize(2,0);
	bets_players.resize(max_seats * 3, 0);
	bets_bots.resize(max_seats * 3, 0);
	cards_players.resize(max_seats);
	cards_players_value.resize(max_seats);
	for (size_t i = 0; i < max_seats; i++) {
		cards_players[i].resize(2, "");
		cards_players_value[i].resize(2, 0);
		
	}
	ace_counter.clear();
	suma_croupier = 0;
	ace_counter_croupier = 0;
}
void Board_BJ::croupier_change(Croupier*& ptr,std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	srand((unsigned)time(NULL));
	int raffle = 0;
	do {
	raffle = rand() % (C_vec.size() - 1);
	} while (raffle == curr_C);
	ptr= &C_vec[raffle];
	curr_C = raffle;
	std::cout << "Zmiana krupiera, " << ptr->get_name() << " bedzie rozdawac karty." << std::endl;
	Sleep(3000);
}
void Board_BJ::bet(Player& play1, bool &fin, Croupier*& croupier) {

	void betting_menu();
	bool bet_error = 0;
	do {
	this->Disp_table(play1);
	std::cout << "1. Zajmij miejsce przy stole\t2. Zwolnij miejsce przy stole";
	bool no_seat = 1;
	for (size_t i = 0; i < empty_seat.size(); i++) if (empty_seat_player[i] == 0) no_seat = 0;
	if (no_seat == 1) std::cout << "(niedostepne)";
	std::cout << "\t3. Odejdz od stolu\t4. Rozpocznij faze obstawiania"<<std::endl;
		char choice = _getch();
		char choice2 = 0;
		switch (choice) {
		case '1':
			do {
				bet_error = 0;
				if (play1.how_many_seats() >= max_seats_one_person) {
					std::cout << "Nie mozesz zajac wiecej miejsc przy tym stole";
					Sleep(2000);			
				}
				else {
					std::cout << "Podaj numer miejsca, przy ktorym chcesz usiasc:" << std::endl;
					choice2 = _getch();
					if (choice2-48 > max_seats|| choice2 - 48<1) {
						std::cout << "ZLE! Podaj numer od 1 do " << max_seats << std::endl;
						Sleep(2000);
						this->Disp_table(play1);
						bet_error = 1;
					}
					else {
						if (empty_seat_player[choice2 - 48 - 1] == 0 || empty_seat[choice2 - 48 - 1] == 0) {
							std::cout << "To miejsce jest juz zajete, wybierz inne";
							Sleep(2000);
							this->Disp_table(play1);
							bet_error = 1;
						}
						else {
							empty_seat_player[choice2 - 48 - 1] = 0;
							play1.add_seat();
							std::cout << "zajmujesz miejsce " << choice2 - 48;
							Sleep(2000);
						}
					}
				}
			} while (bet_error);
			break;

		case '2':
			do {

				if (no_seat == 1) {
					std::cout << "Wszystkie miejsca sa puste" << std::endl;
					Sleep(2000);
				}
				else {
					std::cout << "Podaj numer miejsca, ktore chcesz zwolnic:" << std::endl;
					choice2 = _getch();
					if (choice2 - 48 > max_seats || choice2 - 48 < 1) {
						std::cout << "ZLE! Podaj numer od 1 do " << max_seats << std::endl;
						Sleep(2000);
						this->Disp_table(play1);
						bet_error = 1;
					}
					else {
						if (empty_seat_player[choice2 - 48 - 1] == 1) {
							std::cout << "To miejsce jest juz wolne, wybierz inne";
							Sleep(2000);
							this->Disp_table(play1);
							bet_error = 1;
						}
						else {
							bet_error = 0;
							empty_seat_player[choice2 - 48 - 1] = 1;
							play1.remove_seat();
							std::cout << "zwalniasz miejsce " << choice2 - 48;
							Sleep(2000);
						}
					}
				}
			} while (bet_error);
			break;

		case '3':
			fin = true;
			std::cout << "Milo bylo z Toba zagrac, do zobaczenia ;)";
			for (size_t i = 0; i < empty_seat_player.size(); i++) empty_seat_player[i] = 1;
			play1.remove_all_seats();
			Sleep(3000);
			break;

		case '4':

			if (no_seat == 1) { std::cout << "Wybierz najpierw miejsce przy stole!"; Sleep(2000); bet_error = 1; }
			else {
				do {
					
					//TRZEBA TUTAJ DOPISAC OBSLUGE BOTOW
					// 
					//
					char choice3, choice4, choice5=49;
					this->Disp_table(play1);
					std::cout << std::endl << "1. Postaw pieniadze 2. Zakoncz obstawianie i rozpocznij gre 3. Cofnij" << std::endl;
					choice3 = _getch();

					if (choice3 - 48 < 1 || choice3 - 48 > 3) {
						std::cout << "ZLE! Podaj numer od 1 do 3" << std::endl;
						Sleep(2000);
						this->Disp_table(play1);
						bet_error = 1;
					}

					else if (choice3 - 48 == 1) {
						std::cout << std::endl << "Wybierz miejsce i postaw..." << std::endl;
						choice4 = _getch();
						if (choice4 - 48 < 1 || choice4 - 48 > max_seats) {
							std::cout << "ZLE! Podaj numer od 1 do " << max_seats << std::endl;
							Sleep(2000);
							this->Disp_table(play1);
							bet_error = 1;
						}
						else {
							if (empty_seat_player[choice4 - 48 - 1] == 1) {
								std::cout << "To nie jest twoje miejsce! Wybierz ponownie..." << std::endl;
								Sleep(2000);
								this->Disp_table(play1);
								bet_error = 1;
							}
							else {
								do {
								bet_error = 0;
								if (side_bets == 0) {
									bets_players[(choice4 - 48 - 1)*3]= this->betting_menu(play1, bet_error, choice4,choice5,croupier);
								}
								else {
									std::cout << "Wybierz rodzaj zakladu lub cofnij: 1.Standard 2. 21+3 3. Perfect Pairs 4. Cofnij" << std::endl;
									choice5 = _getch();
									if (choice5 - 48 < 1 || choice5 - 48 > 4) {
										std::cout << "ZLE! Podaj numer od 1 do 4" << std::endl;
										Sleep(2000);
										this->Disp_table(play1);
										bet_error = 1;
									}
									else {
										if (choice5 - 48 == 1) {bets_players[(choice4 - 48 - 1)*3] = this->betting_menu(play1, bet_error, choice4,choice5,croupier);}
										else if (choice5 - 48 == 2) { bets_players[((choice4 - 48 - 1)*3)+1] = this->betting_menu(play1, bet_error, choice4,choice5,croupier);}
										else if (choice5 - 48 == 3) { bets_players[((choice4 - 48 - 1) * 3) + 2] = this->betting_menu(play1, bet_error, choice4,choice5,croupier); }
										else {}
									}
								}
								}while (bet_error);
							}
						}
						bet_error = 1;
					}

					else if (choice3 - 48 == 2) {
						bool no_bet = 1;
						for (size_t i = 0; i < bets_players.size(); i++) {
							if (bets_players[i] > 0 || bets_bots[i] > 0) no_bet = 0;
						}
						if (no_bet == 1) {
							bet_error = 1;
							std::cout << "Stol jest pusty, gracze musza postawic zetony przed rozpoczeciem gry" << std::endl;
							Sleep(2000);
						}
						else {
							bet_error = 0;
							std::cout << "Rozpoczynamy rozgrywke..." << std::endl;
							Sleep(2000);
							this->play_game(play1, croupier);
						}
					}
					else {
						bet_error = 0;
					}
				} while (bet_error);
			}
			break;

		default:
			bet_error = 1;
			std::cout << "ZLE! Wybierz liczbe z zakresu 1 - 4";
			Sleep(2000);
			break;
		}
	} while (bet_error);

}
bool Board_BJ::check_shuffle() {
	if (cards_played >= red_card_deck) return 1;
	else return 0;
	}
void Board_BJ::check_sideBet(Player& play1, Croupier*& croupier) {
	
	size_t found;
	std::vector<int> kolory_licznik;
	std::vector<int>straight_vec;
	bool straight = 0, flush = 0, three_of_a_kind = 0,pair=0;

	for (size_t i = 0; i < max_seats; i++) {
		
		if (bets_players[3 * i + 1] > 0) {//SIDE BET 21+3
			straight = 0; flush = 0; three_of_a_kind = 0;
			straight_vec.clear();
			kolory_licznik.clear();
			kolory_licznik.resize(4, 0);
			straight_vec.resize(3, 0);
			
			//flush
			for (size_t j = 0; j < 2; j++) {
				if (cards_players[i][j].find("kier") != std::string::npos) { kolory_licznik[0]++; }
				if (cards_players[i][j].find("karo") != std::string::npos) { kolory_licznik[1]++; }
				if (cards_players[i][j].find("pik") != std::string::npos) { kolory_licznik[2]++; }
				if (cards_players[i][j].find("trefl") != std::string::npos) { kolory_licznik[3]++; }
			}
			if (cards_croupier[0].find("kier") != std::string::npos) { kolory_licznik[0]++; }
			if (cards_croupier[0].find("karo") != std::string::npos) { kolory_licznik[1]++; }
			if (cards_croupier[0].find("pik") != std::string::npos) { kolory_licznik[2]++; }
			if (cards_croupier[0].find("trefl") != std::string::npos) { kolory_licznik[3]++; }

			for (size_t k = 0; k < kolory_licznik.size(); k++) { if (kolory_licznik[k] == 3)flush = 1; }
			//
			//straight
			straight_vec[0] = cards_players_value[i][0]; straight_vec[1] = cards_players_value[i][1]; straight_vec[2] = cards_croupier_value[0];

			for (size_t i = 0; i < 2; i++) {//sortowanie

				for (size_t j = 0; j < 2; j++) {
					if (straight_vec[j] > straight_vec[j + 1]) { 
						std::swap(straight_vec[j], straight_vec[j + 1]); 
					} 
				}
			}
			if (straight_vec[1] - straight_vec[0] == 1) {
				if (straight_vec[2] - straight_vec[1] == 1) { straight = 1; }
				else {
					if (straight_vec[0] == 2 && straight_vec[2] == 11) { straight = 1; }
					else { straight = 0; }
				}
			}
			else { straight = 0; }
			//
			//three of a kind
			if (cards_players_value[i][0] == cards_players_value[i][1] && cards_players_value[i][1] == cards_croupier_value[0])three_of_a_kind = 1;
			//
			//seat_play[i] = 0; play1.bankroll += 2 * bets_players[3 * i]; play1.profit += 2 * bets_players[3 * i]; play1.BJ_games++; play1.BJ_win++; this->cash_profit -= 2 * bets_players[3 * i]; this->lose++; croupier->profit -= 2 * bets_players[3 * i]; croupier->lose++; bets_players[3 * i] = 0;
						
			
			//wygrane
			if (flush == 1 && straight == 1) { play1.bankroll += 41 * bets_players[3 * i+1]; play1.profit += 41 * bets_players[3 * i+1]; this->cash_profit -= 41 * bets_players[3 * i+1]; croupier->profit -= 41 * bets_players[3 * i+1];  std::cout << "Straight flush!!! Wygrywasz "<< 40 * bets_players[3 * i + 1]<<std::endl; Sleep(2000); bets_players[3 * i + 1] = 0;}//wyplata 40/1 ->sidebet*41
			else if (flush == 1 && straight == 0) { play1.bankroll +=6 * bets_players[3 * i + 1]; play1.profit += 6 * bets_players[3 * i + 1]; this->cash_profit -= 6 * bets_players[3 * i + 1]; croupier->profit -= 6 * bets_players[3 * i + 1];  std::cout << "Flush!!! Wygrywasz " << 5 * bets_players[3 * i + 1] << std::endl; Sleep(2000); bets_players[3 * i + 1] = 0;}//wyplata 5/1 ->sidebet*6
			else if (flush == 0 && straight == 1) { play1.bankroll += 11 * bets_players[3 * i + 1]; play1.profit += 11 * bets_players[3 * i + 1]; this->cash_profit -=11 * bets_players[3 * i + 1]; croupier->profit -= 11 * bets_players[3 * i + 1];  std::cout << "Straight !!! Wygrywasz " << 10 * bets_players[3 * i + 1] << std::endl; Sleep(2000); bets_players[3 * i + 1] = 0;}//wyplata 10/1 ->sidebet*11
			else { bets_players[3 * i + 1] = 0; }//nic nie wygrywasz

			if (three_of_a_kind == 1 && flush == 1) { play1.bankroll += 101 * bets_players[3 * i + 1]; play1.profit += 101 * bets_players[3 * i + 1]; this->cash_profit -= 101 * bets_players[3 * i + 1]; croupier->profit -= 101 * bets_players[3 * i + 1];  std::cout << "Suited three of a kind!!! Wygrywasz " << 100 * bets_players[3 * i + 1] << std::endl; Sleep(2000); bets_players[3 * i + 1] = 0; }//wyplata 100/1 ->sidebet*101
			else if (three_of_a_kind == 1 && flush == 0) { play1.bankroll += 31 * bets_players[3 * i + 1]; play1.profit += 31 * bets_players[3 * i + 1]; this->cash_profit -= 31 * bets_players[3 * i + 1]; croupier->profit -= 31 * bets_players[3 * i + 1];  std::cout << "Three of a kind!!! Wygrywasz " << 30 * bets_players[3 * i + 1] << std::endl; Sleep(2000); bets_players[3 * i + 1] = 0; }//wyplata 30/1 ->sidebet*31
			else { bets_players[3 * i + 1] = 0; }//nic nie wygrywasz
			//

		}
		if (bets_players[3 * i + 2] > 0) {//SIDE BET PERFECT PAIRS
			kolory_licznik.clear();
			pair = 0;
			if (cards_players_value[i][0] != 10) {
				if (cards_players_value[i][1] == cards_players_value[i][0]) {//masz parke

					for (size_t j = 0; j < 2; j++) {
						if (cards_players[i][j].find("kier") != std::string::npos) { kolory_licznik[0]++; }
						if (cards_players[i][j].find("karo") != std::string::npos) { kolory_licznik[1]++; }
						if (cards_players[i][j].find("pik") != std::string::npos) { kolory_licznik[2]++; }
						if (cards_players[i][j].find("trefl") != std::string::npos) { kolory_licznik[3]++; }
					}
					if (kolory_licznik[0] == 2 || kolory_licznik[1] == 2 || kolory_licznik[2] == 2 || kolory_licznik[3] == 2) { play1.bankroll += 31 * bets_players[3 * i + 2]; play1.profit += 31 * bets_players[3 * i + 2]; this->cash_profit -= 31 * bets_players[3 * i + 2]; croupier->profit -= 31 * bets_players[3 * i + 2];  std::cout << "Perfect Para!!! Wygrywasz " << 31 * bets_players[3 * i + 2] << std::endl; Sleep(2000); bets_players[3 * i + 2] = 0; }//perfekt para
					else if (kolory_licznik[0] + kolory_licznik[1] == 2 || kolory_licznik[2] + kolory_licznik[3] == 2) { play1.bankroll += 13 * bets_players[3 * i + 2]; play1.profit += 13 * bets_players[3 * i +2]; this->cash_profit -= 13 * bets_players[3 * i + 2]; croupier->profit -= 13 * bets_players[3 * i + 2];  std::cout << "Para w kolorze!!! Wygrywasz " << 13 * bets_players[3 * i +2] << std::endl; Sleep(2000); bets_players[3 * i + 2] = 0; }//para w tym samym kolorze
					else { play1.bankroll += 6 * bets_players[3 * i + 2]; play1.profit += 6 * bets_players[3 * i + 2]; this->cash_profit -= 6 * bets_players[3 * i + 2]; croupier->profit -= 6 * bets_players[3 * i + 2];  std::cout << "Para!!! Wygrywasz " << 6 * bets_players[3 * i + 2] << std::endl; Sleep(2000); bets_players[3 * i + 2] = 0; }//para
				}
				else { bets_players[3 * i + 1] = 0; }//nic nie wygrywasz
			}
			else {
				//sprawdzenie czy jest parka
				if (cards_players[i][0].find("10") != std::string::npos && cards_players[i][1].find("10") != std::string::npos) { pair = 1; }
				if (cards_players[i][0].find("Walet") != std::string::npos && cards_players[i][1].find("Walet") != std::string::npos) { pair = 1; }
				if (cards_players[i][0].find("Dama") != std::string::npos && cards_players[i][1].find("Dama") != std::string::npos) { pair = 1; }
				if (cards_players[i][0].find("Krol") != std::string::npos && cards_players[i][1].find("Krol") != std::string::npos) { pair = 1; }

				if (pair == 1) {

					for (size_t j = 0; j < 2; j++) {
						if (cards_players[i][j].find("kier") != std::string::npos) { kolory_licznik[0]++; }
						if (cards_players[i][j].find("karo") != std::string::npos) { kolory_licznik[1]++; }
						if (cards_players[i][j].find("pik") != std::string::npos) { kolory_licznik[2]++; }
						if (cards_players[i][j].find("trefl") != std::string::npos) { kolory_licznik[3]++; }
					}		
							
					if (kolory_licznik[0] == 2 || kolory_licznik[1] == 2 || kolory_licznik[2] == 2 || kolory_licznik[3] == 2) { std::cout << "perfect para"; Sleep(2000); }//perfekt para
					else if (kolory_licznik[0] + kolory_licznik[1] == 2 || kolory_licznik[2] + kolory_licznik[3] == 2) { std::cout << "para w kolorze"; Sleep(2000); }//para w tym samym kolorze
					else { std::cout << "para"; Sleep(2000); }//para
				}
				else { bets_players[3 * i + 2] = 0; }//nic nie wygrywasz
			}
			
		}
	}
}
float Board_BJ::betting_menu(Player& play1, bool& bet_error, char& choice, char& choice2,Croupier*& croupier) {
	float bet = 0;
	std::cout << "ile chcesz postawic?" << std::endl;
	do {
		std::cin >> bet;
		bet_error = 0;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			this->Disp_table(play1);
			std::cout << "Wpisz liczbe... " << std::endl;
			bet_error = 1;
		}
		else {
			if (bet == 0) { play1.bankroll += bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; play1.profit += bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; this->cash_profit -= bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; croupier->profit -= bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)] = bet; }
			else if (bet < 0) {
				std::cin.clear();
				std::cin.ignore();
				this->Disp_table(play1);
				std::cout << "Wpisz dodatnia liczbe..." << std::endl;
				bet = 0;
				bet_error = 1;
				Sleep(1000);
			}
			else if (bet > 0 && bet < min_entry) {
				std::cin.clear();
				std::cin.ignore();
				this->Disp_table(play1);
				std::cout << "Musisz postawic minimum " << min_entry << ", sprobuj ponownie..." << std::endl;
				bet_error = 1;
				Sleep(1000);
			}
			else if (bet > max_entry) {
				std::cin.clear();
				std::cin.ignore();
				this->Disp_table(play1);
				std::cout << "Mozesz postawic maksymalnie " << max_entry << ", sprobuj ponownie..." << std::endl;
				bet_error = 1;
				Sleep(1000);
			}
			else if (bet > play1.bankroll) {
				std::cin.clear();
				std::cin.ignore();
				this->Disp_table(play1);
				std::cout << "Masz za malo gotowki..." << std::endl;
				bet = 0;
				bet_error = 0;
				Sleep(1000);
			}
			else {
			//std::cout << "choice1: " << choice << " choice2: " << choice2 << std::endl;
			//std::cout << "choice komorka" << ((choice - 48 - 1) * 3) + (choice2 - 48 - 1) << std::endl;
			//Sleep(2000);
			play1.bankroll += bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; play1.profit += bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; this->cash_profit -= bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)]; croupier->profit -= bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)];
		    bets_players[((choice - 48 - 1) * 3) + (choice2 - 48 - 1)] = bet;
			play1.bankroll -= bet; play1.profit -= bet; this->cash_profit += bet; croupier->profit += bet;
			}
		}
	} while (bet_error);
	
	return bet;
}
bool Board_BJ::insurance(Player &play1,size_t input) {
	bool ins_error = 0,ins=0;
	char choice;
	
	do {
		std::cout << "Miejsce " << input + 1 << ": Czy chcesz skorzystac z ubezpieczenia ? (kosztuje polowe Twojego glownego zakladu)" << std::endl << "1. Tak\t2.Nie" << std::endl;

		ins_error = 0;
		char choice = _getch();
		if (choice - 48 == 1) { std::cout << "Ubezpieczenie przyznane"<< std::endl; Sleep(2000); ins = 1; }
		else if (choice - 48 == 2) { std::cout << "Ubezpieczenie odrzucone" << std::endl; Sleep(2000); ins = 0; }
		else {
			this->Disp_table(play1);
			ins_error = 1;
			std::cout << "ZLE! Podaj numer od 1 do 2" << std::endl;
			Sleep(2000);
		}
	} while (ins_error);
	return ins;
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
void Board_roulette::play_game(Player& play1, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::bet(Player& play1, bool &fin, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
bool Board_roulette::check_shuffle() { return 0; }


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
void Board_bacarrat::play_game(Player& play1, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::bet(Player& play1, bool &fin, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
bool Board_bacarrat::check_shuffle() { return 0; }


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
void Board_poker::play_game(Player& play1, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::bet(Player& play1, bool &fin, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
bool Board_poker::check_shuffle() { return 0; }


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
void Board_war::play_game(Player& play1, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::bet(Player& play1, bool &fin, Croupier*& croupier) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
bool Board_war::check_shuffle() { return 0; }