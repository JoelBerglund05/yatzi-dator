#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>
#include <unistd.h>
#include <cmath>
#include <functional>
#include <bitset>
using namespace std;
using namespace std::chrono;

class Player {
	private:

	public:
		string name = "Player";
		string combination_left[15] = {"Ettor", "Tvåor", "Treor", "Fyror", "Femmor", "Sexor", 
		"Ett par", "Två par", "Triss", "Fyrtal", "Kåk", "Liten stege", "Stor stege", 
		"chans", "Yatzy"};
		int score = 0;
		array< int, 5 > dice = {0, 0, 0, 0, 0};

		
};


class Board {
	private:
		
	public:
		int dice[5] = {0, 0, 0, 0, 0};
		bool playing = false;
		
		bool StartGame (){
			bool start_game = true;
			string ready = "n";
			while (start_game){
				cout << "Redo att spela yatzy (j/n): ";
				cin >> ready;
				for (int i = 0; i < ready.length(); i++){
        			ready[i] = tolower(ready[i]);
				}
				if (ready == "n" or ready == "nej"){
					return false;
				}
				else if (ready == "j" or ready == "ja"){
					return true;
				}
			}
			return false;
		}	

		int HandleUserInput (int user_input){
			bool valid_user_input = false;
			while (!valid_user_input)
			{
				if(cin.fail()) 
				{
					cin.clear(); 
					cin.ignore(); 
					cout << "Please enter an Integer only.";
					cin >> user_input;
				}else {
					valid_user_input = true;
				}
			}
			return user_input;
		}

		array< int, 5 > RandomDice(int numbers_to_generate, string name){
			array< int, 5 > random = {0, 0, 0, 0, 0};
			hash<string> name_hash;
			unsigned long int hash = name_hash(name);
			hash %= 1000;
			cout << hash << endl;
			hash *= static_cast<int>(pow(hash, 2));
			for (int i = 0; i < numbers_to_generate; i++){
				auto system_time_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(
        			chrono::system_clock::now().time_since_epoch()
    			).count();
				sleep(0.00001);
				system_time_nanoseconds *= static_cast<int>(pow(hash, 2));
				cout << "yes " << system_time_nanoseconds;
				mt19937 rng(system_time_nanoseconds);
				random[i] = 1 + (rng() % 6);
			}
			return random;
		}
};


int main(){
	Board board;	
	board.playing = board.StartGame();

	if (board.playing == false){
		return 0;
	}

	cout << "Hur många ska spela: " << endl 
	<< "1. En spelare. Du kommer möta datorn" << endl
	<< "2. Två spelare" << endl
	<< "3. Tre spelare" << endl
	<< "4. Fyra spelare";
	int user_input = 0;
	cin >> user_input;

	vector< Player > players;
	string name = "Player";

    for (int i = 0; i < user_input; ++i)
    {
		cout << "Pleas enert player " << i + 1<< " name: "; 
        cin >> name;
        players.push_back( Player{ name = name} );
		cout << "Hej " << players[i].name << endl; 
	}

	while (board.playing){
		for(int i = 0; i < players.size(); i++){
			players[i].dice = board.RandomDice(5, players[i].name);
			for (int index = 0; index < players[i].dice.size(); index++){
				cout << players[i].dice[index] << " ";
			}
			cout << endl;
		}
		
		board.playing = false;
	}

	return 0;
}