#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include "board_class.h"
#include <vector>
#include <fstream>
#include <cstdlib>
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
	cards_croupier.resize(2, card_name[51]);
	cards_croupier_value.resize(2, card_value[51]);
	cards_players.resize(2 * max_seats, card_name[0]);
	cards_players_value.resize(2 * max_seats, card_value[0]);
	bets_players.resize(max_seats, 0);
	side_bets_players.resize(max_seats * 2, 0);
	bets_bots.resize(max_seats, 0);
	side_bets_bots.resize(max_seats * 2, 0);
	empty_seat.resize(max_seats,1);
	empty_seat_player.resize(max_seats, 1);
	all_cards.resize(52, shoe_size);

}
void Board_BJ::Disp_table(Player& play1) {
	system("CLS");
	short int space=30;
	play1.Game_data();
	for (size_t i = 0; i < max_seats * (space/2) - (space / 2); i++) std::cout << " ";
	
	std::cout << "KRUPIER\n";

	for (size_t i = 0; i < max_seats* (space / 2) - (space / 2); i++) std::cout << " ";
	std::cout << this->cards_croupier[0]<<"\n";
	for (size_t i = 0; i < max_seats* (space / 2) - (space / 2); i++) std::cout << " ";
	std::cout << this->cards_croupier[1] << "\n\n\n";

	for (size_t i = 0; i < max_seats; i++) {
	std::cout << this->cards_players[2*i];
	for (size_t j = 0; j < space - cards_players[2 * i].size(); j++) {
		std::cout << " ";
	}
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {
	std::cout << this->cards_players[2*i+1];
	for (size_t j = 0; j < space - cards_players[2 * i+1].size(); j++) {
		std::cout << " ";
	}
	}
	std::cout << "\n";
	for (size_t i = 0; i < max_seats; i++) {

		std::stringstream wypisz;
		wypisz << "Wartosc kart ";
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
		wypisz << "Bet: " << bets_players[i];
		std::cout << wypisz.str();
		for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
	}
	std::cout << "\n";
	//for (size_t i = 0; i < max_seats + 1; i++) std::cout << "\t";
	if (side_bets == 1) {
		for (size_t i = 0; i < max_seats; i++) {

			std::stringstream wypisz;
			wypisz << "21+3: " << side_bets_players[2*i];
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
		}
		std::cout << "\n";
		for (size_t i = 0; i < max_seats; i++) {

			std::stringstream wypisz;
			wypisz << "Perfect pairs: " << side_bets_players[2 * i+1];
			std::cout << wypisz.str();
			for (size_t j = 0; j < space - wypisz.str().size(); j++) std::cout << " ";
		}
	}

	std::cout << "\n\n";

	
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
	for (size_t i = 0; i < red_card; i++) deck_temp.push_back(deck[i]);
	deck.erase(deck.begin(), deck.begin() + red_card);
	for(size_t i=0;i<deck_temp.size();i++) deck.push_back(deck_temp[i]);
	red_card_cut=((rand() % 20)+40)*0.01*52*shoe_size;
	red_card_deck = red_card_cut;
	std::cout << "losowanie zakonczone\n\n";
	Sleep(2000);
	//////
}
void Board_BJ::play_game(Player& play1) {
	this->Disp_table(play1);
	std::vector<bool> seat_play;
	seat_play.resize(max_seats, 0);
	//rozpoznanie gdzie krupier ma polozyc karty
	for (size_t i = 0; i < max_seats; i++) {

		if (bets_players[i] > 0 || bets_bots[i] > 0 || side_bets_players[2*i] > 0 || side_bets_players[2 * i] > 0 || side_bets_bots[2*i] > 0) { seat_play[i] = 1; }

	}
	// 
	//wykladanie kart zgodnie z procedura
	//wykrywanie blackjacka i ubezpieczenia
	//decyzje gracza
	//dobieranie krupiera
	//koniec

	Sleep(2000);
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
void Board_BJ::bet(Player& play1, bool &fin) {

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
			Sleep(3000);
			break;

		case '4':

			if (no_seat == 1) { std::cout << "Wybierz najpierw miejsce przy stole!"; Sleep(2000); bet_error = 1; }
			else {
				do {
					
					//TRZEBA TUTAJ DOPISAC OBSLUGE BOTOW
					// 
					//
					char choice3, choice4, choice5;
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
									
									bets_players[choice4 - 48 - 1]= this->betting_menu(play1, bet_error, choice4);
								}
								else {
									std::cout << "Wybierz rodzaj zakladu lub cofnij: 1.Standard 2. 21+3 3. Perfect Pairs 4. Cofnij" << std::endl;
									Sleep(2000);
									choice5 = _getch();
									if (choice5 - 48 < 1 || choice5 - 48 > 4) {
										std::cout << "ZLE! Podaj numer od 1 do 4" << std::endl;
										Sleep(2000);
										this->Disp_table(play1);
										bet_error = 1;
									}
									else {
										if (choice5 - 48 == 1) {bets_players[choice4 - 48 - 1] = this->betting_menu(play1, bet_error, choice4);}
										else if (choice5 - 48 == 2) { side_bets_players[(choice4 - 48 - 1)*2] = this->betting_menu(play1, bet_error, choice4);}
										else if (choice5 - 48 == 3) { side_bets_players[((choice4 - 48 - 1) * 2) + 1] = this->betting_menu(play1, bet_error, choice4); }
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
							this->play_game(play1);
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
int Board_BJ::betting_menu(Player& play1, bool& bet_error, char& choice) {
	int bet = 0;
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
			if (bet == 0) { play1.bankroll += bets_players[choice - 48 - 1]; bets_players[choice - 48 - 1] = bet; }
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
			else { play1.bankroll -= bet; }
		}
	} while (bet_error);
	
	return bet;
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
void Board_roulette::play_game(Player& play1) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_roulette::bet(Player& play1, bool &fin) {
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
void Board_bacarrat::play_game(Player& play1) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_bacarrat::bet(Player& play1, bool &fin) {
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
void Board_poker::play_game(Player& play1) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_poker::bet(Player& play1, bool &fin) {
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
void Board_war::play_game(Player& play1) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
void Board_war::bet(Player& play1, bool &fin) {
	std::cout << "TEST" << std::endl;
	Sleep(2000);
}
bool Board_war::check_shuffle() { return 0; }