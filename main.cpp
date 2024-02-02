#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;


class Player {
	public:
		string name = "Player";
		string combination_left[15] = {"Ettor", "Tvåor", "Treor", "Fyror", "Femmor", "Sexor", 
		"Ett par", "Två par", "Triss", "Fyrtal", "Kåk", "Liten stege", "Stor stege", 
		"chans", "Yatzy"};
		int score = 0;
};


class Board {
	private:
		bool start_game = true;
		string ready = "n";
	public:
		int dice[5] = {0, 0, 0, 0, 0};
		int random_int = 0;
		bool playing = false;
		
		bool StartGame (){
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
};


int main(){
	Board board;
	board.playing = board.StartGame();

	if (board.playing == false){
		return 0;
	}

	cout << "japowjd" << endl;

	return 0;
}