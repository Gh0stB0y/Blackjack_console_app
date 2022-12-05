//Main_menu.cpp
#include "class_player.h"
#include "Main_menu.h"
//using namespace std;
bool error;
void play();

void settings() {
	char sign;
	char sign2;
	bool finish = false;
	system("CLS");
	std::cout << "\t\tStatystyki" << std::endl << std::endl;
	std::cout << "Opcja w budowie" << std::endl;
	std::cout << "Nacisnij esc, aby wrocic do menu glownego..." << std::endl;

	do {
		sign2 = _getch();
	} while (sign2 != 27);
}

void stats(Player& playerr1) {
	bool finish = false;
	do {
		system("CLS");
		std::cout << "\t\tUstawienia" << std::endl << std::endl;
		std::cout << "1. Statystyki gracza" << std::endl;
		std::cout << "2. Statystyki kasyna" << std::endl;
		std::cout << "3. Ranking graczy" << std::endl;
		std::cout << "Nacisnij esc, aby wrocic do menu glownego..." << std::endl;
		char sign;
		char sign2;
		do {
			sign = _getch();
			switch (sign) {

			case '1':
				error = false;
				playerr1.Disp_values();
				std::cout << "Nacisnij esc, aby wrocic do okna statystyk..." << std::endl;
				do {
					sign2 = _getch();
				} while (sign2 != 27);
				break;
			case '2':
				error = false;
				system("CLS");
				std::cout << "Statystyki kasyna pojawia sie wkrotce..." << std::endl;
				std::cout << "Nacisnij esc, aby wrocic do okna statystyk..." << std::endl;
				do {
					sign2 = _getch();
				} while (sign2 != 27);
				break;
			case '3':
				error = false;
				system("CLS");
				std::cout << "Ranking graczy pojawi sie wkrotce..." << std::endl;
				std::cout << "Nacisnij esc, aby wrocic do okna statystyk..." << std::endl;
				do {
					sign2 = _getch();
				} while (sign2 != 27);
				break;
			case 27:
				error = false;
				finish = true;
				break;
			default:
				std::cout << "ZLE! Wybierz liczbe z zakresu 1 - 3 " << std::endl;
				error = true;
				break;
			}
		} while (error);

	} while (!finish);
}

void exit_game(Player& player1) {
	user_save(player1);
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
	Sleep(3500);

	//TWORZENIE PLIKOW BINARNYCH	generalnie to jest do przebudowania, trzeba wprowadzic pliki binarne i zakodowac zawartosc tak zeby zaden random tego nie odczytal
}

Player login() {

	std::vector<bool> err_vec(15, false);
	std::vector<std::string> err_vec_str = { "Wykryto niedozwolony znak, wpisz inna nazwe!","Zbyt duzo znakow! Wymysl krotsza nazwe uzytkownika",
		"Blad adresu email! Nie mozna wpisac dwoch kropek obok siebie","Blad adresu email! Nie mozna podac kropki (.) ani myslnika (-) na poczatku i na koncu adresu",
		"Blad adresu email! Nie wykryto znaku @","Blad adresu email! Wykryto wiecej niz 1 znak @",
		"Blad adresu email! Wykryto niedozwolony znak","Blad adresu email! Czesc lokalna (czesc przed znakiem @) jest dluzsza niz 63 znaki)",
		"Wykryto niedozwolony znak, wpisz inne haslo","Haslo nie zawiera wielkiej litery","Haslo nie zawiera malej litery","Haslo nie zawiera cyfry",
		"Haslo nie zawiera znaku specjalnego","Nie znaleziono wpisanego loginu lub e-maila w bazie danych","Wpisane haslo jest niepoprawne" };
	std::vector < std::string> user_data_str_vec(3, "");
	std::vector < int> user_data_int_vec;
	system("CLS");
	std::cout << "1. Zaloguj sie do kasyna\t2. Zarejestruj sie\t3. Zagraj jako gosc" << std::endl;
	char choice;
	std::string username_temp;
	std::string email_temp;	//zmienne przechowujace to co uzytkownik wpisal
	std::string pass_temp;
	std::string wypisz_sign_up = "\t\tRejestracja nowego uzytkownika:\nPodaj Login: ";
	std::string wypisz_sign_up2 = "Podaj E-mail: ";
	std::string wypisz_sign_up3 = "Podaj Haslo: ";//(Musi zawierac co najmniej jedna wielka i mala litere, znak specjalny oraz liczbe): ";
	std::string wypisz_sign_in = "\t\tZaloguj sie do systemu:\nPodaj Login lub email: ";
	std::string wypisz_sign_in2 = wypisz_sign_up3;
	std::string user_data_line;
	std::stringstream zapis_plik;
	std::fstream UD, UDI;
	int counter = 1;
	size_t pos = 0;
	std::string token;
	std::string delimiter = " ";
	size_t variable_count = 0;
	int check_ID = 0;
	bool check_user_mail = false;
	do {
		choice = _getch();


		switch (choice) {
		case '1': //LOGOWANIE DO SYSTEMU
			do {
				do {
					error = false;
					system("CLS");
					std::cout << wypisz_sign_in;
					getline(std::cin, username_temp);				  //WPROWADZENIE LOGINU LUB MAILA PRZEZ UZYTKOWNIKA
					std::cout << wypisz_sign_in2;
					getline(std::cin, pass_temp);					  //WPROWADZENIE HASLA PRZEZ UZYTKOWNIKA
					for (int i = 0; i < username_temp.length(); i++) {//SPRAWDZENIE CZY NAZWA UZYTKOWNIKA ZAWIERA ZNAK STANDARDOWE Z ASCII
						if (username_temp[i] < 33 || username_temp[i]>126) {
							error = true;
							std::cout << err_vec_str[0];
							Sleep(3000);
						}
					}
					for (int i = 0; i < pass_temp.length(); i++) {//SPRAWDZENIE CZY HASLO ZAWIERA ZNAK STANDARDOWE Z ASCII
						if (pass_temp[i] < 33 || pass_temp[i]>126) {
							error = true;
							std::cout << err_vec_str[0];
							Sleep(3000);
						}
					}

				} while (error);

				UD.open("User_data.bin", std::ios::in);		//OTWIERANIE PLIKU Z DANYMI UZYTKOWNIKA
				if (UD.good()) {
					while (getline(UD, user_data_line)) {	//WCZYTANIE Z PLIKU LINII, KTORA ZAWIERA WSZYSTKIE INFORMACJE NA TEMAT UZYTKOWNIKA
						user_data_str_vec.clear();
						user_data_str_vec.resize(3);
						variable_count = 0;
						pos = 0;
						check_ID = 1;
						while ((pos = user_data_line.find(delimiter)) != std::string::npos && variable_count < 4) {	//SPRAWDZENIE PIERWSZYCH TRZECH DANYCH Z LINII 
							token = user_data_line.substr(0, pos);
							user_data_line.erase(0, pos + delimiter.length());
							variable_count++;
							switch (variable_count) {
							default: break;
							case 1:				//SPRAWDZENIE PIERWSZEJ ZMIENNEJ - ID
								check_ID = stoi(token);
								break;
							case 2:
								user_data_str_vec[0] = token;
								if (username_temp == token) {
									check_user_mail = true;
									error = false;
									err_vec[13] = false;
								}
								else {
									error = true;
									check_user_mail = false;
									err_vec[13] = true;
								}
								break;
							case 3:				//SPRAWDZENIE DRUGIEJ I TRZECIEJ ZMIENNEJ - LOGINU I EMAILA
								user_data_str_vec[1] = token;
								if (username_temp == token) {
									check_user_mail = true;
									error = false;
									err_vec[13] = false;
								}
								else if (username_temp != token && check_user_mail == true) {
									error = false;
									err_vec[13] = false;
								}
								else if (username_temp != token && check_user_mail == false) {
									error = true;
									check_user_mail = false;
									err_vec[13] = true;
								}
								break;
							case 4:				//SPRAWDZENIE CZWARTEJ ZMIENNEJ - HASLA ORAZ PODJECIE DECYZJI O DALSZYCH KROKACH
								user_data_str_vec[2] = token;
								if (check_user_mail == true && pass_temp == token) {		//LOGIN LUB MAIL i haslo PASUJA DO STRINGOW WPISANEGO PRZEZ UZYTKOWNIKA
									std::cout << "Login i haslo poprawne" << std::endl;
									Sleep(2000);
									error = false;
									err_vec[14] = false;
								}
								else if (check_user_mail == true && pass_temp != token) {	//LOGIN/MAIL PRAWIDLOWY, HASLO NIEPRAWIDLOWE
									err_vec[14] = true;
									error = true;
								}
								else {							//ANI LOGIN/MAIL ANI HASLO NIE PASUJA DO STRINGOW WPISANYCH PRZEZ UZYTKOWNIKA								
									err_vec[14] = true;
									error = true;
								}
								break;
							}
						}
						//to sie dzieje po sprawdzeniu pierwszych 4 zmiennych z linii												
						if (!error) break; //jesli i haslo i login zostaly wpisane poprawnie to wiemy ktorego uzytkownika trzeba wczyta (po numerze ID, czyli ID_check)	
						if (error && err_vec[13] == false) break; //jesli login jest dobry ale haslo zle to przestaje szukac uzytkownika w reszcie pliku i zwracam info ze jest zle haslo					
					} // koniec odczytywania linijek					
					if (err_vec[13]) {//zly login
						std::cout << err_vec_str[13] << std::endl;
						Sleep(2000);
					}
					if (err_vec[14] && !err_vec[13]) {	//zle haslo dobry login
						std::cout << err_vec_str[14] << std::endl;
						Sleep(2000);
					}
					while ((pos = user_data_line.find(" ")) != std::string::npos) {	//SPRAWDZENIE PIERWSZYCH TRZECH DANYCH Z LINII 
						user_data_int_vec.push_back(stoi(user_data_line.substr(0, pos)));
						user_data_line.erase(0, pos + delimiter.length());
					}
					//for (size_t i = 0; i < user_data_int_vec.size(); i++) std::cout << user_data_int_vec[i]<<std::endl;
				}
				else {
					error = true;
					std::cout << std::endl << "Blad podczas odczytu danych, sprobuj ponownie";
					Sleep(3000);
				}
				UD.close();
			} while (error);
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
						if (username_temp[i] < 33 || username_temp[i]>126) {
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

						if (email_temp[i] < 33 || email_temp[i]>126) {//SPRAWDZENIE CZY NAZWA UZYTKOWNIKA ZAWIERA ZNAK STANDARDOWE Z ASCII
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

						if (pass_temp[i] < 33 || pass_temp[i]>126) err_vec[8] = true;//wykrycie niedozwolonych znakow
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
				counter = 1;
				if (UD.good()) {

					while (getline(UD, user_data_line)) counter++;
					UD.close();
				}
				UD.open("User_data.bin", std::ios::out | std::ios::app | std::ios::binary);
				if (UD.good()) {
					zapis_plik << counter << ' ';
					zapis_plik << username_temp + ' ' + email_temp + ' ' + pass_temp + ' ' + "1" + ' ' + "0" + ' ' + "5000" + ' ' + "0" + ' ' + "5000" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" + ' ' + "0" +' '+ '\n';
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


	if (choice == '1') {
		Player P1(check_ID, user_data_str_vec[0], user_data_str_vec[1], user_data_str_vec[2], user_data_int_vec[0], user_data_int_vec[1], user_data_int_vec[2], user_data_int_vec[3],
			user_data_int_vec[4], user_data_int_vec[5], user_data_int_vec[6], user_data_int_vec[7], user_data_int_vec[8], user_data_int_vec[9], user_data_int_vec[10]);
		//P1.Disp_values();
		return P1;
	}
	else if (choice == '2') {
		Player P1(counter, username_temp, email_temp, pass_temp);
		//P1.Disp_values();
		return P1;
	}
	else if (choice == '3') {
		Player P1;
		return P1;
	}

}

void user_save(Player& playerr1) {
	std::ifstream UD;
	std::ofstream UD2;
	std::vector<std::string> temp_users;
	std::string temp_users_line;
	size_t licznik = 1;
	UD.open("User_data.bin", std::ios::in);
	if (UD.good()) {
		while (getline(UD, temp_users_line)) {
			if (playerr1.ID == licznik) temp_users.push_back(playerr1.save_val());
			else temp_users.push_back(temp_users_line);
			licznik++;
		}
		UD.close();
	}
	else std::cout << "Blad przy zapisie danych!" << std::endl;
	UD2.open("User_data.bin", std::ios::out | std::ios::trunc);
	if (UD2.good()) {
		for (size_t i = 0; i < temp_users.size(); i++) UD2 << temp_users[i] << std::endl;
	}
	else std::cout << "Blad przy zapisie danych!" << std::endl;
	UD2.close();
}

void Display_main_menu(Player& player1) {
	char sign;
	system("CLS");
	player1.Main_menu_data();
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
			settings();
			break;
		case '3':
			error = false;
			stats(player1);
			break;
		case '4':
			error = false;
			player1 = login();
			break;
		case '5':
			error = false;
			exit_game(player1);
		default:
			std::cout << "ZLE! Wybierz liczbe z zakresu 1 - 5 " << std::endl;
			error = true;
			break;
		}
	} while (error);


}


void initialize() {

	ile_wejsc();
	Player Play1 = login();
	for (;;) Display_main_menu(Play1);

}