//Main_menu.cpp

#include "Main_menu.h"
//using namespace std;
bool error;
void play();
void settings();
void stats();
void exit_game() {
	system("CLS");
	std::cout << "Dziekujemy za wizyte w kasynie, do zobaczenia niebawem :)";
	Sleep(5000);
	exit(0);

}

void ile_wejsc() {
	std::fstream wykaz_wejscia;
	std::string linia;
	short int wejscia = 0; //ile wejsc w ciagu ostatnich 7 dni 
	//operacje zapisuja do pliku date aktualnego wejscia do programu
	wykaz_wejscia.open("wykaz_wejsc_do_programu.dat", std::ios::binary | std::ios::app);
	if (wykaz_wejscia.good() == true) {
		wykaz_wejscia << time(0) << std::endl;
		wykaz_wejscia.close();
	}
	//
	// operacje odczytuja liczbe wejsc z ostatnich 7 dni 
	wykaz_wejscia.open("wykaz_wejsc_do_programu.dat", std::ios::binary | std::ios::in);
	if (wykaz_wejscia.good() == true) {
		while (getline(wykaz_wejscia, linia))
		{
			if (time(0) - atoi(linia.c_str()) < 604800) wejscia++;
		}
		wykaz_wejscia.close();

		//
		//wypisanie powitania dla gracza w zaleznosci od liczby wejsc
		if (wejscia > 1) std::cout << "Witaj uzytkowniku! To Twoje " << wejscia << " wejscie w ciagu ostatnich 7 dni, korzystaj z gier hazardowych rozsadnie" << std::endl;
		else if (wejscia == 1) std::cout << "Witaj uzytkowniku! To Twoje pierwsze wejscie w ciagu ostatnich 7 dni, milej zabawy";
		else std::cout << "!!!BLAD PLIKU!!! LICZBA WEJSC WYNOSI MNIEJ NIZ 1";
	}
	else std::cout << "Informacja na temat liczby wejsc jest niedostepna";
	//
	Sleep(2000);

	//TWORZENIE PLIKOW BINARNYCH	generalnie to jest do przebudowania, trzeba wprowadzic pliki binarne i zakodowac zawartosc tak zeby zaden random tego nie odczytal
}




void login() {

	std::vector<bool> err_vec(13, false);
	std::vector<std::string> err_vec_str = { "Wykryto niedozwolony znak, wpisz inna nazwe!","Zbyt duzo znakow! Wymysl krotsza nazwe uzytkownika",
		"Blad adresu email! Nie mozna wpisac dwoch kropek obok siebie","Blad adresu email! Nie mozna podac kropki (.) ani myslnika (-) na poczatku i na koncu adresu",
		"Blad adresu email! Nie wykryto znaku @","Blad adresu email! Wykryto wiecej niz 1 znak @",
		"Blad adresu email! Wykryto niedozwolony znak","Blad adresu email! Czesc lokalna (czesc przed znakiem @) jest dluzsza niz 63 znaki)",
		"Wykryto niedozwolony znak, wpisz inne haslo","Haslo nie zawiera wielkiej litery","Haslo nie zawiera malej litery","Haslo nie zawiera cyfry",
		"Haslo nie zawiera znaku specjalnego" };
	system("CLS");
	std::cout << "1. Zaloguj sie do kasyna\t2. Zarejestruj sie\t3. Zagraj jako gosc" << std::endl;

	do {

		char choice = _getch();
		std::string username_temp;
		std::string email_temp;	//zmienne przechowujace to co uzytkownik wpisal
		std::string pass_temp;
		std::string wypisz_sign_up = "\t\tRejestracja nowego uzytkownika:\nLogin: ";
		std::string wypisz_sign_up2 = "E-mail: ";
		std::string wypisz_sign_up3 = "Haslo: ";//(Musi zawierac co najmniej jedna wielka i mala litere, znak specjalny oraz liczbe): ";
		std::string user_data_line;
		std::stringstream zapis_plik;
		std::fstream UD, UDI;
		switch (choice) {

		case '1':
			error = false;

			//TRZEBA SPRAWDZIC CZY ZGADZAJA SIE DANE LOGOWANIA
			break;
		case '2'://REJESTRACJA NOWEGO UZYTKOWNIKA
			error = false;
			do {
				do {
					error = false;
					system("CLS");
					std::cout << wypisz_sign_up;
					getline(std::cin, username_temp);

					for (int i = 0; i < username_temp.length(); i++) {//SPRAWDZENIE CZY NAZWA UZYTKOWNIKA ZAWIERA ZNAK STANDARDOWE Z ASCII
						if (username_temp[i] < 32 || username_temp[i]>126) {
							err_vec[0] = true;
						}
						if (i > 15) { //NAZWA UZYTKOWNIKA MOZE MIEC MAX 15 ZNAKOW	
							err_vec[1] = true;
							i = username_temp.length();
						}
					}
					for (int k = 0; k < 2; k++) {
						if (err_vec[k] == true) {
							error = true;
							std::cout << err_vec_str[k];
							err_vec[k] = false;
						}
					}

					if (error) Sleep(2000);
				} while (error); //etap pierwszy wpisanie loginu

				do {
					error = false;
					int malpa = 0;
					system("CLS");
					std::cout << wypisz_sign_up + username_temp << std::endl << wypisz_sign_up2;
					getline(std::cin, email_temp);

					for (int i = 0; i < email_temp.length(); i++) {

						if (email_temp[i] == '.' && email_temp[i + 1] == '.') {// 2 KROPKI OBOK SIEBIE
							err_vec[2] = true;
						}
						if (email_temp[0] == '.' || email_temp[email_temp.length() - 1] == '.' || email_temp[0] == '-' || email_temp[email_temp.length() - 1] == '-') {
							err_vec[3] = true;
						}
						if (email_temp[i] == '@') malpa++;

						if (email_temp[i] < 32 || email_temp[i]>126) {//SPRAWDZENIE CZY NAZWA UZYTKOWNIKA ZAWIERA ZNAK STANDARDOWE Z ASCII
							err_vec[6] = true;
						}
						if (malpa == 0 && i > 63) {//ZA DLUGA PIERWSZA CZESC MAILA
							err_vec[7] = true;
						}
						//najprostsze rozwiazanie DO POPRAWY!!! wypada zrobic liste bledow i na jej podstawie wysylac do usera komunikaty
					}

					if (malpa < 1) {
						err_vec[4] = true;
						//std::cout << "Blad adresu email! Nie wykryto znaku @";//ZA MALO MALP
					}
					if (malpa > 1) {
						err_vec[5] = true;
						//std::cout << "Blad adresu email! Wykryto wiecej niz 1 znak @";//ZA DUZO MALP
					}
					for (int k = 2; k < 8; k++) {
						if (err_vec[k] == true) {
							error = true;
							std::cout << err_vec_str[k] << std::endl;
							err_vec[k] = false;
						}
					}
					if (error) Sleep(2000);
				} while (error); //etap drugi wpisanie maila OBSLUGA BLEDOW DO ROZSZERZENIA

				do {

					error = false;
					for (int i = 9; i < 13; i++) err_vec[i] = true;//bledy informujace o braku danego typu znaku w hasle,
					system("CLS");
					std::cout << wypisz_sign_up + username_temp << std::endl << wypisz_sign_up2 + email_temp << std::endl << wypisz_sign_up3;
					getline(std::cin, pass_temp);
					//std::cout << std::endl << err_vec[8];
					for (int i = 0; i < pass_temp.length(); i++) {

						if (pass_temp[i] < 32 || pass_temp[i]>126) err_vec[8] = true;//wykrycie niedozwolonych znakow
						if (pass_temp[i] > 64 && pass_temp[i] < 90) err_vec[9] = false;//jesli wielka litera wystepuje w hasle to skasuj blad
						if (pass_temp[i] > 96 && pass_temp[i] < 123) err_vec[10] = false;//jesli mala litera wystepuje w hasle to skasuj blad
						if (pass_temp[i] > 47 && pass_temp[i] < 58) err_vec[11] = false;//jesli cyfra wystepuje w hasle to skasuj blad
						if ((pass_temp[i] > 31 && pass_temp[i] < 48) || (pass_temp[i] > 57 && pass_temp[i] < 65) ||
							(pass_temp[i] > 90 && pass_temp[i] < 97) || (pass_temp[i] > 122 && pass_temp[i] < 127)) err_vec[12] = false;//jesli znak specjalny wystepuje w hasle to skasuj blad			
					}
					for (int k = 8; k < 13; k++) {
						if (err_vec[k] == true) {
							error = true;
							std::cout << err_vec_str[k] << std::endl;
							err_vec[k] = false;
						}
					}
					if (error) Sleep(2000);
				} while (error); //etap trzeci wpisanie hasla

				UD.open("User_data.bin", std::ios::in);
				int counter = 1;
				if (UD.good()) {

					while (getline(UD, user_data_line))
					{
						counter++;
					}
					UD.close();
				}
				UD.open("User_data.bin", std::ios::out | std::ios::app | std::ios::binary);
				if (UD.good()) {
					zapis_plik << counter << ' ';
					zapis_plik << username_temp + ' ' + email_temp + ' ' + pass_temp + ' ' + "1" + ' ' + "0" + ' ' + "5000" + ' ' + "0" + ' ' + "5000" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" + '\n';
					//linijka zapis_plik: ID username mail password lvl exp bankroll profit cash_dep cash_wth BJ_win BJ_lose BJ_draw BJ_BJ BJ_games
					UD << zapis_plik.rdbuf();
					UD.close();
				}
				else {
					error = true;
					std::cout << std::endl << "Blad podczas zapisywania danych, sprobuj ponownie";
					Sleep(3000);
				}
			} while (error == true);

			break;
		case '3':
			error = false;
			//TRZEBA UTWORZYC OBIEKT KLASY "GRACZ" O NAZWIE GOSC;
			break;
		default:
			std::cout << "ZLE! Wybierz liczbe z zakresu 1 - 3 " << std::endl;
			error = true;
			break;


		}
	} while (error);


}




void Display_main_menu() {
	char sign;


	system("CLS");
	std::cout << "\t\tMenu glowne" << std::endl << std::endl;
	std::cout << "1. GRAJ" << std::endl;
	std::cout << "2. USTAWIENIA" << std::endl;
	std::cout << "3. STATYSTYKI" << std::endl;
	std::cout << "4. ZMIEN UZYTKOWNIKA" << std::endl;
	std::cout << "5. WYJSCIE" << std::endl;

	do {
		sign = _getch();
		switch (sign) {

		case '1':
			error = false;
			//play();
			break;
		case '2':
			error = false;
			//settings();
			break;
		case '3':
			error = false;
			//stats();
			break;
		case '4':
			error = false;
			//login();
			break;
		case '5':
			error = false;
			exit_game();
		default:
			std::cout << "ZLE! Wybierz liczbe z zakresu 1 - 5 " << std::endl;
			error = true;
			break;
		}
	} while (error);


}


void initialize() {

	ile_wejsc();
	login();
	Display_main_menu();

}