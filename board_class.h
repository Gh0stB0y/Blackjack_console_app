#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>

class Board {
protected:
	unsigned int min_lvl,max_seats,max_seats_one_person,min_entry,max_entry,win,lose,winratio;
	float cash_profit;
	bool bots;
public:
	virtual void Disp_table() = 0;
	virtual void shuffle_cards() = 0;
	virtual void play_game() = 0;
	virtual void croupier_change() = 0;
	virtual void bet() = 0;

};
class Board_BJ :public Board {

	bool side_bets;
	short int shoe_size;
	unsigned int draw, BJ;
public:
	//virtual void Disp_table();
	//virtual void shuffle_cards();
	//virtual void play_game();
	//virtual void croupier_change();
	//virtual void bet();
};


class Board_roulette :public Board {

	//COMIN SOON
public:
	//virtual void Disp_table();
	//virtual void play_game();
	//virtual void croupier_change();
	//virtual void bet();

};
class Board_bacarrat :public Board {

public:
	//virtual void Disp_table();
	//virtual void shuffle_cards();
	//virtual void play_game();
	//virtual void croupier_change();
	//virtual void bet();
	//COMIN SOON

};
class Board_Poker :public Board {
public:
	//virtual void Disp_table();
	//virtual void shuffle_cards();
	//virtual void play_game();
	//virtual void croupier_change();
	//virtual void bet();
	//COMIN SOON


};
class Tab_war :public Board {
public:
	//virtual void Disp_table();
	//virtual void shuffle_cards();
	//virtual void play_game();
	//virtual void croupier_change();
	//virtual void bet();

	//COMIN SOON


};