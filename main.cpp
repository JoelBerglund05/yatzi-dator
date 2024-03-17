#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class MasterPlayer {
protected:
  vector<string> combination_left;
  int score;

public:
  MasterPlayer() {
    combination_left = {"Ettor", "Tvåor",       "Treor",      "Fyror", "Femmor",
                        "Sexor", "Ett par",     "Två par",    "Triss", "Fyrtal",
                        "Kåk",   "Liten stege", "Stor stege", "chans", "Yatzy"};
    score = 0;
  }
  vector<string> GetCombinationsLeft() { return combination_left; }
};
class Player : public MasterPlayer {
private:
  string name;

public:
  Player() { name = "Player"; }

  string GetPlayerName() { return name; }

  void RemoveCombination(string combination) {
    for (int i = 0; i < combination_left.size(); i++) {
      if (combination_left[i] == combination)
        combination_left.erase(combination_left.begin() + i);
    }
  }

  void AddScore(int total_value, string combination) {
    score += total_value;
    RemoveCombination(combination);
    cout << "Du har " << score << " poäng" << endl
         << "Men din totala value är " << total_value << endl;
    sleep(2);
  }
};

class Dice {
private:
  array<int, 5> dice;
  int count_dice[6];
  vector<string> starting_combination;
  vector<string> possible_combinations;

  void SortDiceArray() { std::sort(dice.begin(), dice.end()); }

  void ClearCountDiceVariable() {
    for (int i = 0; i < 6; i++) {
      count_dice[i] = 0;
    }
  }

  void NumberCounter() {
    int current_die_number = 1;

    ClearCountDiceVariable();

    for (int i = 0; i < 6; i++) {
      for (int current_index = 0; current_index < 6; current_index++) {
        if (dice[current_index] == current_die_number) {
          count_dice[i] += 1;
        }
      }
      current_die_number += 1;
    }
  }

  bool CheckIfDiceCombinationIsYatzy() {
    for (int i = 0; i < (dice.size() - 1); i++) {
      if (dice[0] != dice[i]) {
        return false;
      }
    }
    return true;
  }

  bool CheckIfDiceCombinationIsLargeStraight() {
    if (dice[0] == 2) {
      if (dice[1] == 3) {
        if (dice[2] == 4) {
          if (dice[3] == 5) {
            if (dice[4] == 6) {
              return true;
            } else {
              return false;
            }
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  bool CheckIfDiceCombinationIsSmallStraight() {
    if (dice[0] == 1) {
      if (dice[1] == 2) {
        if (dice[2] == 3) {
          if (dice[3] == 4) {
            if (dice[4] == 5) {
              return true;
            } else {
              return false;
            }
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  bool CheckIfDiceCombinationIsFullHouse() {
    /* Checks dice one and two if they are equal
    then checks if the rest are equal to each other.
    we only need to check the dice with one in the between because they are
    sorted. check example:
    Can't happened
    2 2 6 5 6
    would become
    2 2 5 6 6
        ^   ^
        |   |
    these isn't equal to each other so it can't be a full house.
    */
    if (dice[0] == dice[2]) {
      if (dice[3] == dice[4]) {
        if (dice[0] != dice[4])
          return true;
      } else
        return false;
    } else if (dice[0] == dice[1]) {
      if (dice[2] == dice[4]) {
        if (dice[0] != dice[4])
          return true;
      } else
        return false;
    } else
      return false;
    return false;
  }

  bool CheckIfDiceCombinationIsFourOfAKind() {
    if (dice[0] == dice[3])
      return true;
    else if (dice[1] == dice[4])
      return true;
    else
      return false;
  }

  bool CheckIfDiceCombinationIsThreeOfAKind() {
    if (dice[0] == dice[2])
      return true;
    else if (dice[1] == dice[3])
      return true;
    else if (dice[2] == dice[4])
      return true;
    else
      return false;
  }

  bool CheckIfDiceCombinationIsOnePair() {
    if (dice[0] == dice[1])
      return true;
    else if (dice[1] == dice[2])
      return true;
    else if (dice[2] == dice[3])
      return true;
    else if (dice[3] == dice[4])
      return true;
    else
      return false;
  }

  bool CheckIfDiceCombinationIsTwoPair() {
    if (dice[0] == dice[1]) {
      if (dice[2] == dice[3] or dice[3] == dice[4]) {
        if (dice[0] != dice[3])
          return true;
      }
    } else if (dice[1] == dice[2]) {
      if (dice[3] == dice[4]) {
        if (dice[1] != dice[3])
          return true;
      }
    } else
      return false;
    return false;
  }

  bool CheckIfDiceCombinationIsOneOfTheSixNumbers() {
    // TODO: NumberCounter() metoden är svår läst
    int current_die_number = 0;
    NumberCounter();
    for (int i = 0; i < 6; i++) {
      if (count_dice[i] > 0)
        return true;
    }
    return false;
  }

  bool CheckCombinations(int combination_number) {
    bool chance = true;
    switch (combination_number) {
    case 6:
      return CheckIfDiceCombinationIsOnePair();
    case 7:
      return CheckIfDiceCombinationIsTwoPair();
    case 8:
      return CheckIfDiceCombinationIsThreeOfAKind();
    case 9:
      return CheckIfDiceCombinationIsFourOfAKind();
    case 10:
      return CheckIfDiceCombinationIsFullHouse();
    case 11:
      return CheckIfDiceCombinationIsSmallStraight();
    case 12:
      return CheckIfDiceCombinationIsLargeStraight();
    case 13:
      return chance;
    case 14:
      return CheckIfDiceCombinationIsYatzy();
    default:
      return false;
    }
  }

public:
  Dice() {
    dice = {1, 4, 5, 5, 5};
    for (int i = 0; i < 6; i++)
      count_dice[i] = 0;
    starting_combination = {"Ettor",      "Tvåor",  "Treor",   "Fyror",
                            "Femmor",     "Sexor",  "Ett par", "Två par",
                            "Triss",      "Fyrtal", "Kåk",     "Liten stege",
                            "Stor stege", "chans",  "Yatzy"};
    possible_combinations = {"..."};
  }

  void FullRandomDiceArray() {
    sleep(0.00001);
    auto system_time_nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::mt19937 rng(system_time_nanoseconds);
    for (int i = 0; i < 5; i++) {
      dice[i] = 1 + (rng() % 6);
    }
    SortDiceArray();
    DisplayDices();
  }

  void RandomNumberToReroll(vector<int> dice_to_reroll) {
    auto system_time_nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::mt19937 rng(system_time_nanoseconds);
    int index_to_reroll = 0;
    for (int i = 0; i < dice_to_reroll.size(); i++) {
      index_to_reroll = dice_to_reroll[i] - 1;
      dice[index_to_reroll] = 1 + (rng() % 6);
    }
    SortDiceArray();
  }

  array<int, 5> GetDiceArray() { return dice; }

  vector<string> GetPossibleCombinations() { return possible_combinations; }

  void DisplayDices() {
    for (int i = 0; i < 5; i++)
      cout << dice[i] << " ";
    cout << endl;
  }

  void PrintPosibleCombinations(vector<string> combination_left,
                                string print_no_combinations) {
    bool count_dice_number_bool[15] = {false, false, false, false, false,
                                       false, false, false, false, false,
                                       false, false, false, false, false};

    if (CheckIfDiceCombinationIsOneOfTheSixNumbers() == true) {
      for (int i = 0; i < 6; i++) {
        if (count_dice[i] > 0)
          count_dice_number_bool[i] = true;
      }
    }

    auto if_combination_left =
        std::find(combination_left.begin(), combination_left.end(),
                  starting_combination[0]);
    bool found_chance = false;
    for (int i = 0; i < starting_combination.size(); i++) {
      if_combination_left =
          std::find(combination_left.begin(), combination_left.end(),
                    starting_combination[i]);
      if (if_combination_left != combination_left.end() and i >= 6) {
        count_dice_number_bool[i] = CheckCombinations(i);
      }
    }

    bool combinations_possible[15] = {
        count_dice_number_bool[0],  count_dice_number_bool[1],
        count_dice_number_bool[2],  count_dice_number_bool[3],
        count_dice_number_bool[4],  count_dice_number_bool[5],
        count_dice_number_bool[6],  count_dice_number_bool[7],
        count_dice_number_bool[8],  count_dice_number_bool[9],
        count_dice_number_bool[10], count_dice_number_bool[11],
        count_dice_number_bool[12], count_dice_number_bool[13],
        count_dice_number_bool[14]};

    int size = sizeof(combinations_possible) / sizeof(combinations_possible[0]);
    cout << "0. " << print_no_combinations << endl;
    int choice_index = 1;
    possible_combinations.clear();
    for (int i = 0; i < size; i++) {
      if (combinations_possible[i] == true) {
        cout << choice_index << ". " << combination_left[i] << endl;
        possible_combinations.push_back(combination_left[i]);
        choice_index += 1;
      }
    }
  }

  string Getspecificcombination(int index) {
    return possible_combinations[index];
  }

  int GetDiceValue(int choice) {
    string combination = Getspecificcombination(choice);

    int value = 0;
    for (int i = 0; i < starting_combination.size(); i++) {
      if (starting_combination[i] == combination) {
        if (i <= 5)
          value += (i + 1) * count_dice[i];
        else if (i == 6) {
          int highest_value = 0;
          for (int index = 0; index < 6; index++)
            if (count_dice[index] == 2)
              highest_value = (index + 1);
          value += highest_value * 2;
        } else if (i == 7) {
          for (int first_index = 0; first_index < 6; first_index++)
            for (int second_index = 0; second_index < 6; second_index++)
              if (count_dice[first_index] == 2 and count_dice[second_index])
                value += (first_index + 1) * count_dice[first_index];
        } else if (i == 8) {
          for (int index = 0; index < 6; index++)
            if (count_dice[index] == 3)
              value += (index + 1) * count_dice[index];
        } else if (i == 9) {
          for (int index = 0; index < 6; index++)
            if (count_dice[index] == 4)
              value += (index + 1) * count_dice[index];
        } else
          for (int index = 0; index < dice.size(); index++)
            value += dice[index];
      }
    }
    return value;
  }
};

class Scoreboard {
private:
};

class Computer : public MasterPlayer {};

class GameMaster {
private:
  vector<Player> players;
  Dice dices;

  bool playing;
  int Player_turn = 1;
  int player_tryes = 1;
  string const print_no_combinations = "Ingen av kombinationerna ";
  string const remove_combinations = "Stryk en kombination ";

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

  int ChooseOption() {
    int choice = 0;
    cin >> choice;
    choice = HandleUserInput(choice);
    return choice;
  }

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

  void RerollDice() {
    cout << "Dina tärningar är: ";
    dices.DisplayDices();
    cout << endl
         << "Vilka Täningar vill du byta ut? Svara med nummret på platsen av "
            "tärningen men bara en tärning i taget. "
         << endl
         << "Skriv 0 när du valde dem "
            "du ville slå om."
         << endl;
    vector<int> dice_to_reroll;
    int answer = 0;
    for (int i = 1; i < dices.GetDiceArray().size(); i++) {
      // TODO: Hantera hur man ska svara att man är nöjd med vilka som ska bytas
      // TODO: ut
      /*0 = bryt ut ur loopen*/

      cin >> answer;
      cout << "Var det någon mer tärning som ska kasstas om?" << endl;
      if (answer != 0) {
        answer = HandleUserInput(answer);
        dice_to_reroll.push_back(answer);
      } else {
        i = dices.GetDiceArray().size();
      }
    }
    dices.RandomNumberToReroll(dice_to_reroll);
  }

  void PrintCombinationsLeft(vector<string> combination_left) {
    int choice_index = 1;
    for (int i = 0; i < combination_left.size(); i++) {
      cout << choice_index << ". " << combination_left[i] << endl;
      choice_index += 1;
    }
  }

  void ChoosingCombination(int index) {

    int choice = ChooseOption();
    if (choice == 0) {
      // TODO: hantera vilka täningar som ska sparas
      RerollDice();
      player_tryes += 1;
      if (player_tryes < 3) {
        ShowImportantInformationAboutDice(index, print_no_combinations);
        ChoosingCombination(index);
      } else {
        ShowImportantInformationAboutDice(index, remove_combinations);
        choice = ChooseOption();
        if (choice == 0) {
          cout << "Vilken kombination vill du stryka? " << endl;
          vector<string> combinations_left =
              players[index].GetCombinationsLeft();
          PrintCombinationsLeft(combinations_left);
          cin >> choice;
          choice -= 1;
          players[index].RemoveCombination(combinations_left[choice]);
        } else {
          choice -= 1;
          players[index].AddScore(dices.GetDiceValue(choice),
                                  dices.Getspecificcombination(choice));
          player_tryes = 1;
        }
      }
    } else {
      choice -= 1;
      players[index].AddScore(dices.GetDiceValue(choice),
                              dices.Getspecificcombination(choice));
      player_tryes = 1;
    }
  }

  void ShowImportantInformationAboutDice(int index,
                                         string print_no_combinations) {
    cout << "Dina tärningar är: ";
    dices.DisplayDices();
    cout << "Dessa kombinationer har du: " << endl;
    dices.PrintPosibleCombinations(players[index].GetCombinationsLeft(),
                                   print_no_combinations);
  }

public:
  GameMaster() { playing = false; }

  int MasterMain() {

    StartGame();
    if (GetPlaying() == false) {
      return 0;
    }

    players = AddPlayerCount();

    while (GetPlaying()) {

      for (int i = 0; i < players.size(); i++) {
        dices.FullRandomDiceArray();
        cout << "Spelare " << Player_turn << " tur. ";
        ShowImportantInformationAboutDice(i, print_no_combinations);
        ChoosingCombination(i);

        Player_turn += 1;
      }

      return 0;
    }
    return 0;
  }
};

int main() {
  GameMaster game_master;
  return game_master.MasterMain();
}