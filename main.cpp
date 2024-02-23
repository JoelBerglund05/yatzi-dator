#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <unistd.h>
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::hash;
using std::string;
using std::vector;

class Player {
private:
  string name = "Player";

protected:
  int score = 0;
  array<int, 5> dice = {0, 0, 0, 0, 0};

public:
  array<int, 5> GetDiceArray() { return dice; }

  void DisplayDices() {
    for (int i = 0; i < 5; i++)
      cout << dice[i] << " ";
  }

  string GetPlayerName() { return name; }
};

class Rule {};

class Dice {
public:
  array<int, 5> RandomDice(int numbers_to_generate) {
    array<int, 5> random = {0, 0, 0, 0, 0};
    sleep(0.00001);
    auto system_time_nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::mt19937 rng(system_time_nanoseconds);
    for (int i = 0; i < numbers_to_generate; i++) {
      random[i] = 1 + (rng() % 6);
    }
    return random;
  }
};

class Scoreboard {
private:
  vector<Player> players;
  string combination_left[15] = {
      "Ettor", "Tvåor",       "Treor",      "Fyror", "Femmor",
      "Sexor", "Ett par",     "Två par",    "Triss", "Fyrtal",
      "Kåk",   "Liten stege", "Stor stege", "chans", "Yatzy"};
};

class UserInput {
private:
  bool playing = false;

  string AddPlayerName(int index) {
    string name = "Player";
    cout << "spelare " << index + 1 << " name: ";
    cin >> name;

    return name;
  };

  int HandleUserInput(int user_input) {
    bool valid_user_input = false;
    while (!valid_user_input) {
      if (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Please enter an Integer only.";
        cin >> user_input;
      } else {
        valid_user_input = true;
      }
    }
    return user_input;
  }

public:
  void StartGame() {
    bool if_start_game = true;
    string ready = "n";
    while (if_start_game) {
      cout << "Redo att spela yatzy (j/n): ";
      cin >> ready;
      for (int i = 0; i < ready.length(); i++) {
        ready[i] = tolower(ready[i]);
      }
      if (ready == "n" or ready == "nej") {
        if_start_game = false;
      } else if (ready == "j" or ready == "ja") {
        playing = true;
        if_start_game = false;
      }
    }
  }

  bool GetPlaying() { return playing; }

  vector<Player> AddPlayerCount() {
    vector<Player> players;
    cout << "Hur många ska spela: " << endl
         << "1. En spelare. Du kommer möta datorn" << endl
         << "2. Två spelare" << endl
         << "3. Tre spelare" << endl
         << "4. Fyra spelare ";
    int player_count = 0;
    cin >> player_count;
    player_count = HandleUserInput(player_count);

    for (int i = 0; i < player_count; ++i) {
      players.push_back(Player{});
      AddPlayerName(i);
    }
    return players;
  }
};

class Computer : protected Player {};

int main() {
  UserInput user_inputs;
  Dice dices;

  user_inputs.StartGame();

  if (user_inputs.GetPlaying() == false) {
    return 0;
  }

  vector<Player> players = user_inputs.AddPlayerCount();

  while (user_inputs.GetPlaying()) {

    for (int i = 0; i < players.size(); i++) {
      players[i].GetDiceArray() = dices.RandomDice(5);
    }

    return 0;
  }

  return 0;
}