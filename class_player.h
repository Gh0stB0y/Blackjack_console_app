#pragma once
#include <iostream>
#include <windows.h>

class Player {
public:
	std::string username;
	std::string mail;
	std::string password;
	int ID = 0, lvl = 1, exp = 0;
	float bankroll = 0, profit = 0, cash_dep = 0, cash_wth = 0;	//cash deposited, cash withdrawn
	short int seat = 0;
	int BJ_win = 0, BJ_lose = 0, BJ_draw = 0, BJ_BJ = 0, BJ_games = 0;

	friend Player login();


	void Get_username() {
		std::cout << "PROBNY TEKST " << username<<std::endl;

	}

	Player(int i, std::string un, std::string um, std::string up) : ID(i), username(un), mail(um), password(up), bankroll(5000)
	{	// konstruktor uzywany przy procesie rejestracji
		system("CLS");
		std::cout << "Witaj " << un << " ,dziekujemy za zalozenie konta w naszym kasynie :)" << std::endl;
		Sleep(3000);
	}
	Player(int i, std::string un, std::string um, std::string up, int b, int p, int cd, int cw, int BJw, int BJl, int BJd, int BJBJ, int BJg)
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

};