#include <string>
//class_player.h
class Player {

	std::string username;
	std::string mail;
	std::string password;
	int ID, lvl, exp;
	float bankroll, profit, cash_dep, cash_wth;	//cash deposited, cash withdrawn
	short int seat;
	int BJ_win, BJ_lose, BJ_draw, BJ_BJ, BJ_games;
	
	friend void login();
public:

	



};