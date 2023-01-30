#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <vector>
#include "class_player.h"
#include "class_croupier.h"

class Board {
protected:
	unsigned int tabID = 0, min_lvl = 1, max_seats = 4, max_seats_one_person = 1, min_entry = 10, max_entry = 500 , win=0, lose=0, winratio=0;
	float cash_profit=0;
	bool bots=0;
	
public:
	virtual void Disp_table(Player &play1) = 0;
	virtual void shuffle_cards() = 0;
	virtual void play_game(Player &play1, Croupier*& croupier) = 0;
	virtual void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C) = 0;
	virtual void bet(Player &play1,bool &fin, Croupier*& croupier) = 0;
	virtual bool check_shuffle() = 0;
	
};
class Board_BJ :public Board {

	
	unsigned int draw=0, BJ=0;
	bool side_bets = 0;
	short int shoe_size = 6;
	
	std::vector<int> all_cards; //kolejnosc od 2 do asa; kier, karo, pik, trefl
	std::vector<std::string> card_name = { "2 kier", "2 karo","2 pik","2 trefl","3 kier", "3 karo","3 pik","3 trefl" ,"4 kier", "4 karo","4 pik","4 trefl",
	"5 kier", "5 karo","5 pik","5 trefl","6 kier", "6 karo","6 pik","6 trefl","7 kier","7 karo","7 pik","7 trefl","8 kier", "8 karo","8 pik","8 trefl",
	"9 kier", "9 karo","9 pik","9 trefl","10 kier", "10 karo","10 pik","10 trefl","Walet kier", "Walet karo","Walet pik","Walet trefl",
	"Dama kier", "Dama karo","Dama pik","Dama trefl","Krol kier", "Krol karo","Krol pik","Krol trefl","As kier", "As karo","As pik","As trefl" };
	std::vector<int> card_value = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11};
	std::vector<std::string> deck;//POTASOWANE KARTY
	std::vector<int> deck_value; //WARTOSCI POTASOWANYCH KART
	std::vector<std::string> cards_croupier;
	std::vector<int> cards_croupier_value;
	std::vector<std::vector<std::string>> cards_players;
	std::vector<std::vector<int>> cards_players_value;
	short unsigned int cards_played = 0, red_card_deck = 0;
	std::vector<float>bets_players;
	std::vector<float>bets_bots;
	std::vector<bool>empty_seat;
	std::vector<bool>empty_seat_player;
	bool deck_finish = 0;
public:
	Board_BJ(unsigned int input);
	void Disp_table(Player& play1);
	void shuffle_cards();
	void play_game(Player& play1, Croupier*& croupier);
	void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C);
	void bet(Player& play1, bool &fin,Croupier* &croupier);
	bool check_shuffle();

	float betting_menu(Player& play1,bool &bet_error,char &choice, char& choice2, Croupier*& croupier);
	bool insurance(Player& play1, size_t input);

	// KOLEJNOSC: DISP TABLE W TLE, BET, PLAY_GAME.  CROUPIER CHANGE I SHUFFLE CARDS W RAZIE POTRZEBY
};
class Board_roulette :public Board {

	//COMIN SOON
public:
	virtual void Disp_table(Player& play1);
	virtual void shuffle_cards();
	virtual void play_game(Player& play1, Croupier*& croupier);
	virtual void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C);
	virtual void bet(Player& play1, bool &fin, Croupier*& croupier);
	bool check_shuffle();
	Board_roulette(int input);
};
class Board_bacarrat :public Board {

public:
	virtual void Disp_table(Player& play1);
	virtual void shuffle_cards();
	virtual void play_game(Player& play1, Croupier*& croupier);
	virtual void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int& curr_C);
	virtual void bet(Player& play1, bool &fin, Croupier*& croupier);
	bool check_shuffle();
	Board_bacarrat(int input);
	//COMIN SOON

};
class Board_poker :public Board {
public:
	virtual void Disp_table(Player& play1);
	virtual void shuffle_cards();
	virtual void play_game(Player& play1, Croupier*& croupier);
	virtual void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int &curr_C);
	virtual void bet(Player& play1, bool &fin, Croupier*& croupier);
	bool check_shuffle();
	Board_poker(int input);
	//COMIN SOON


};
class Board_war :public Board {
public:
	virtual void Disp_table(Player& play1);
	virtual void shuffle_cards();
	virtual void play_game(Player& play1, Croupier*& croupier);
	virtual void croupier_change(Croupier*& ptr, std::vector<Croupier> &C_vec, short unsigned int &curr_C);
	virtual void bet(Player& play1, bool &fin, Croupier*& croupier);
	bool check_shuffle();
	Board_war(int input);
};