#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unistd.h>
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::ws;

class Combination {
private:
  string name;
  bool exist;
  int score;

public:
  Combination(string name) {
    this->name = name;
    exist = true;
    score = 0;
  }

  void RemoveCombination() { exist = false; }

  bool IsCombinationLeft() { return exist; }

  string GetName() { return name; }

  int GetScore() { return score; }

  void AddScore(int score) { this->score = score; }
};
class MasterPlayer {
protected:
  vector<string> *combination_left;
  int score;
  vector<Combination> combinations;

public:
  MasterPlayer() {
    combination_left = new vector<string>;
    *combination_left = {"Ettor",      "Tvåor",  "Treor",   "Fyror",
                         "Femmor",     "Sexor",  "Ett par", "Två par",
                         "Triss",      "Fyrtal", "Kåk",     "Liten stege",
                         "Stor stege", "chans",  "Yatzy"};
    score = 0;
    for (int i = 0; i < (*combination_left).size(); i++)
      combinations.push_back(Combination((*combination_left)[i]));
    delete combination_left;
  }

  vector<string> GetCombinationsNameLeft() {
    vector<string> combinations_left;
    for (int i = 0; i < combinations.size(); i++)
      if (combinations[i].IsCombinationLeft() == true)
        combinations_left.push_back(combinations[i].GetName());
    return combinations_left;
  }

  string GetSpecificCombination(int index) {
    return combinations[index].GetName();
  }

  vector<string> GetAllCombinations() {
    vector<string> combinations;
    for (int i = 0; i < this->combinations.size(); i++)
      combinations.push_back(this->combinations[i].GetName());
    return combinations;
  }

  vector<bool> DoesCombinationsExist() {
    vector<bool> all_combinations;
    for (int i = 0; i < combinations.size(); i++)
      all_combinations.push_back(combinations[i].IsCombinationLeft());
    return all_combinations;
  }

  void UpdateScoreBoard(int score, int choice, vector<string> name) {
    int total_score = 0;
    // TODO: Fixa så logiken är rätt
    for (int i = 0; i < combinations.size(); i++) {
      if (GetAllCombinations()[i] == name[choice]) {
        cout << name[choice] << " " << i << " " << GetAllCombinations()[i]
             << endl;
        combinations[i].AddScore(score);
        combinations[i].RemoveCombination();
      }
      total_score += combinations[i].GetScore();
    }

    cout << "Du har " << total_score << " poäng" << endl;
    sleep(2);
  }
};
class Player : public MasterPlayer {
private:
  string name;

public:
  Player(string name) {
    MasterPlayer();
    this->name = name;
  }

  string GetPlayerName() { return name; }
};

class Dice {
private:
  array<int, 5> dice;
  array<int, 6> count_dice;

  void SortDiceArray() { std::sort(dice.begin(), dice.end()); }

  void ClearCountDiceVariable() {
    for (int i = 0; i < 6; i++) {
      count_dice[i] = 0;
    }
  }

public:
  Dice() {
    dice = {3, 4, 5, 6, 6};
    count_dice = {0, 0, 0, 0, 0, 0};
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
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      if (GetDiceCountFromSpecificIndex(combination_number) > 0)
        return true;
      else
        return false;
      cout << "Got here" << endl;
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

  void NumberCounter() {
    int current_die_number = 1;

    ClearCountDiceVariable();

    array<int, 6> count_dice = {0};

    for (int i = 0; i < 6; i++) {
      for (int current_index = 0; current_index < 6; current_index++) {
        if (dice[current_index] == current_die_number) {
          count_dice[i] += 1;
        }
      }
      current_die_number += 1;
    }

    this->count_dice = count_dice;
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

  int GetDiceCountFromSpecificIndex(int index) { return count_dice[index]; }

  void DisplayDices() {
    for (int i = 0; i < 5; i++)
      cout << dice[i] << " ";
    cout << endl;
  }
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
    getline(cin >> ws, name);

    return name;
  };

  int HandleUserInput(string user_input) {
    bool valid_user_input = false;
    int answer = 0;
    while (!valid_user_input) {
      try {
        answer = std::stoi(user_input);
        valid_user_input = true;
      } catch (const std::invalid_argument &e) {
        cout << "Värdet du lämnade är felaktigt. Svara med ett hel tal: ";
        getline(cin >> ws, user_input);
      }
    }
    return answer;
  }

  int ChooseOption() {
    string choice = " ";
    getline(cin >> ws, choice);
    int answer = HandleUserInput(choice);
    return answer;
  }

  void StartGame() {
    bool if_start_game = true;
    string ready = "n";
    while (if_start_game) {
      cout << "Redo att spela yatzy (j/n): ";
      getline(cin >> ws, ready);
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

  vector<bool> GetPossibleCombinations(int index) {
    vector<bool> combinations_possible;
    combinations_possible = players[index].DoesCombinationsExist();
    dices.NumberCounter();
    for (int i = 0; i < combinations_possible.size(); i++) {
      if (combinations_possible[i] == true)
        combinations_possible[i] = dices.CheckCombinations(i);
    }
    cout << endl;
    return combinations_possible;
  }

  void PrintPosibleCombinations(int index) {
    vector<bool> combinations_possible;
    combinations_possible = GetPossibleCombinations(index);
    if (player_tryes < 3)
      cout << "0. " << print_no_combinations << endl;
    else {
      cout << "0. " << remove_combinations << endl;
      player_tryes = 1;
    }

    int choice_index = 1;
    for (int i = 0; i < combinations_possible.size(); i++)
      if (combinations_possible[i] == true) {
        cout << choice_index << ". " << players[index].GetAllCombinations()[i]
             << endl;
        choice_index += 1;
      }
  }

  vector<Player> AddPlayerCount() {
    vector<Player> players;
    cout << "Hur många ska spela: " << endl
         << "1. En spelare. Du kommer möta datorn" << endl
         << "2. Två spelare" << endl
         << "3. Tre spelare" << endl
         << "4. Fyra spelare ";

    int player_count = ChooseOption();

    for (int i = 0; i < player_count; ++i) {
      players.emplace_back(AddPlayerName(i));
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
    string user_input = "";
    answer = ChooseOption();

    for (int i = 1; i < dices.GetDiceArray().size(); i++) {
      if (answer <= dices.GetDiceArray().size()) {
        cout << "Var det någon mer tärning som ska kasstas om?" << endl;
        answer = ChooseOption();
        if (answer != 0) {
          dice_to_reroll.push_back(answer);
        } else {
          i = dices.GetDiceArray().size();
        }
      } else {
        cout << "Talet är för högt välj ett lägre tal: ";
        answer = ChooseOption();
        i -= 1;
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
    bool good_answer = false;
    while (good_answer == false) {
      if (choice > GetPossibleCombinationsName(index).size()) {
        cout << "Förstort nummer. Välj ett mindre tal: ";
        choice = ChooseOption();
      } else {
        good_answer = true;
      }
    }
    if (choice == 0) {
      // TODO: hantera vilka täningar som ska sparas
      RerollDice();
      player_tryes += 1;
      if (player_tryes < 3) {
        ShowImportantInformationAboutDice(index);
        ChoosingCombination(index);
      } else {
        ShowImportantInformationAboutDice(index);
        choice = ChooseOption();
        if (choice == 0) {
          cout << "Vilken kombination vill du stryka? " << endl;
          vector<string> combinations_left =
              players[index].GetCombinationsNameLeft();
          PrintCombinationsLeft(players[index].GetCombinationsNameLeft());
          choice = ChooseOption();
          choice -= 1;
          int score = 0;
          bool good_answer = false;
          while (good_answer == false) {
            if (choice < combinations_left.size()) {
              players[index].UpdateScoreBoard(score, choice, combinations_left);
              good_answer = true;
            } else {
              cout << "Värdet är för högt. vilken kombination vill du stryka? "
                   << endl;
              choice = ChooseOption();
            }
          }
        }
      }
    } else {
      choice -= 1;
      players[index].UpdateScoreBoard(GetDiceValue(choice, index), choice,
                                      GetPossibleCombinationsName(index));
      player_tryes = 1;
    }
  }

  void ShowImportantInformationAboutDice(int index) {
    cout << "Dina tärningar är: ";
    dices.DisplayDices();
    cout << "Dessa kombinationer har du: " << endl;
    PrintPosibleCombinations(index);
  }

  vector<string> GetPossibleCombinationsName(int player_index) {
    vector<bool> possible_combinations = GetPossibleCombinations(player_index);
    vector<string> name;

    for (int i = 0; i < possible_combinations.size(); i++)
      if (possible_combinations[i] == true) {
        name.push_back(players[player_index].GetSpecificCombination(i));
      }

    return name;
  }

  int GetDiceValue(int choice, int player_index) {
    int value = 0;
    vector<string> name = GetPossibleCombinationsName(player_index);

    for (int i = 0; i < players[player_index].GetAllCombinations().size();
         i++) {
      if (players[player_index].GetAllCombinations()[i] == name[choice]) {
        if (i <= 5) {
          value += (i + 1) * dices.GetDiceCountFromSpecificIndex(i);
        } else if (i == 6) {
          int highest_value = 0;
          for (int index = 0; index < 6; index++)
            if (dices.GetDiceCountFromSpecificIndex(index) == 2)
              highest_value = (index + 1);
          value += highest_value * 2;
        } else if (i == 7) {
          bool vlaue_has_been_set = false;
          for (int first_index = 0; first_index < 6; first_index++)
            for (int second_index = 0; second_index < 6; second_index++)
              if (dices.GetDiceCountFromSpecificIndex(first_index) == 2 and
                  dices.GetDiceCountFromSpecificIndex(second_index) == 2) {
                if (first_index != second_index and
                    vlaue_has_been_set == false) {
                  value +=
                      (first_index + 1) *
                          dices.GetDiceCountFromSpecificIndex(first_index) +
                      (second_index + 1) *
                          dices.GetDiceCountFromSpecificIndex(second_index);
                  vlaue_has_been_set = true;
                }
              }
        } else if (i == 8) {
          for (int index = 0; index < 6; index++)
            if (dices.GetDiceCountFromSpecificIndex(index) == 3)
              value += (index + 1) * dices.GetDiceCountFromSpecificIndex(index);
        } else if (i == 9) {
          for (int index = 0; index < 6; index++)
            if (dices.GetDiceCountFromSpecificIndex(index) == 4)
              value += (index + 1) * dices.GetDiceCountFromSpecificIndex(index);
        } else {
          array<int, 5> dice = dices.GetDiceArray();
          for (int index = 0; index < dice.size(); index++)
            value += dice[index];
        }
        cout << i << endl;
      }
    }
    return value;
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
        ShowImportantInformationAboutDice(i);
        ChoosingCombination(i);

        Player_turn += 1;
      }
      Player_turn = 1;
    }
    return 0;
  }
};

int main() {
  GameMaster game_master;
  game_master.MasterMain();
  return 0;
}