
// Main_menu.h
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include "class_player.h"
#include "class_croupier.h"

//using namespace std;
//

Player login();	/*funkcja pozwala na zalogowanie do gry lub granie jako gosc*/
void Display_main_menu();	/* funkcja wyswietla menu glowne*/
void initialize();	/*funkcja puszczana zawsze na poczatku dzialania programu

wczytuje sie menu glowne oraz wszystkie opcje z nim zwiazane
byc moze w przyszlosci przed menu bedzie wyswietlac sie jeszcze jakas animacja

pozwala tez na wybor i obsluge opcji w menu glownym: gra, ustawienia, statystyki, wyjscie
*/
void play(Player& player1);
/*
funkcja obslugujaca caly proces gry:asd
wybor gry, wybor stolu, ustawienia nastepnej gry, gra, odejscie od stolu
*/

void settings();
/*
ustawienie uczciwosci krupiera
liczb talii w bucie
i w sumie nie wiem czego jeszcze, trzeba isc do kasyna zeby zrobic research :D


*/

void stats(Player& playerr1);
/*
pokazuje statystyki ze wszystkich odbytych gier w tym programie:

bilans kasyna
bilans zsumowany wszystkich graczy
winratio kasyna

i osobno dla kazdego zarejestrowanego gracza:

bilans, winratio, miejsce w rankingu (parametrem jest bilans)

*/


void exit_game();
/*
wyjscie z programu
*/

int choose_game();
void user_save(Player& playerr1);
void ile_wejsc();
std::vector<Croupier> create_croupiers(std::vector<Croupier>& C_vec);
bool check_croupier_change(time_t &c_time, time_t &curr_time);

//Board_BJ create_table(1);
//Board_roulette create_table(2);
//Board_bacarrat create_table(3);
//Board_poker create_table(4);
//Board_war create_table(5);