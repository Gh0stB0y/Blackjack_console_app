#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
//#include "board_class.h"
//#include "class_croupier.h"
//
class Player {

	std::string username;
	std::string mail;
	std::string password;
	int ID = 0, lvl = 1, exp = 0;
	float bankroll = 0, profit = 0, cash_dep = 0, cash_wth = 0;	//cash deposited, cash withdrawn
	short int seats=0;
	int BJ_win = 0, BJ_lose = 0, BJ_draw = 0, BJ_BJ = 0, BJ_games = 0;

	friend Player login();
	friend void user_save(Player&);
	friend class Board_BJ;
public:
	std::string Get_username() {
		return username;
	}
	bool Get_ID() {
		if (ID == 4) return 1;
		else return 0;
	}
	void add_seat() { seats++; }
	void remove_seat() { seats--; }
	void remove_all_seats() { seats=0; }
	short int how_many_seats() {return seats;}
	Player(int i, std::string un, std::string um, std::string up) : ID(i), username(un), mail(um), password(up), bankroll(5000)
	{	// konstruktor uzywany przy procesie rejestracji
		system("CLS");
		std::cout << "Witaj " << un << " ,dziekujemy za zalozenie konta w naszym kasynie :)" << std::endl;
		Sleep(3000);
	}
	Player(int i, std::string un, std::string um, std::string up, int l, int ex, int b, int p, int cd, int cw, int BJw, int BJl, int BJd, int BJBJ, int BJg) :
		ID(i), username(un), mail(um), password(up), lvl(l), exp(ex), bankroll(b), profit(p), cash_dep(cd), cash_wth(cw), BJ_win(BJw), BJ_lose(BJl), BJ_draw(BJd), BJ_BJ(BJBJ), BJ_games(BJg)
	{	// konstruktor uzywany przy procesie logowania
		system("CLS");
		std::cout << "Witaj ponownie " << un << ", zyczymy pomyslnych lowow ;)" << std::endl;
		Sleep(3000);
	}
	Player()
	{	// konstruktor uzywany przy wejsciu do gry jako gosc}
		system("CLS");
		std::cout << "Witamy szanownego goscia ;)" << std::endl;
		Sleep(3000);
		username = "Gosc";
		bankroll = 1000;
	}
	void Disp_values() {
		system("CLS");
		std::cout << std::endl;
		std::cout << "Nick: " << this->username << std::endl;
		std::cout << "Poziom: " << this->lvl << std::endl;
		std::cout << "Doswiadczenie: " << this->exp << std::endl;
		std::cout << "Stan konta: " << this->bankroll << std::endl;
		std::cout << "Wplacone pieniadze: " << this->cash_dep << std::endl;
		std::cout << "Wyplacone pieniadze: " << this->cash_wth << std::endl;
		std::cout << "Zarobki: " << this->profit << std::endl;
		if (this->BJ_games > 0)std::cout << "% Wygranych rozdan: " << this->BJ_win / this->BJ_games * 100 << std::endl;
	}
	std::string save_val() {

		std::stringstream ss;
		ss << ID << " " << username << " " << mail << " " << password << " " << lvl << " " << exp << " " << bankroll << " " << profit << " " << cash_dep << " " << cash_wth << " " << BJ_win << " " << BJ_lose << " " << BJ_draw << " " << BJ_BJ << " " << BJ_games << " ";
		std::string rtrn_val = ss.str();
		//std::cout << "print stringstream -> string: " << rtrn_val << std::endl;
		return(rtrn_val);
		//zapis_plik: ID username mail password lvl exp bankroll profit cash_dep cash_wth BJ_win BJ_lose BJ_draw BJ_BJ BJ_games
	}
	void Main_menu_data() {
		std::cout << "Gracz: " << username << "\tID: " << ID << "\tBankroll: " << bankroll << std::endl;
	}
	void Game_data(){ std::cout << "Gracz: " << username << "\tBankroll: " << bankroll << std::endl; }
};