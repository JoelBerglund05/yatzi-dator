# Loggbok

## Vecka 17

## Vecka 16

denna veckan har jag debuggat min kod. Jag har fått massor av felräkningar men inga error medalande.

    for (int i = 0; i < players[player_index].GetAllCombinations().size();
         i++) 

denna koden hade jag tidigare på detta sättet

    for (int i = 0; i < players[player_index].GetAllCombinations()[1].size();
         i++) 

vilket gjorde att den tittade på hur mång är stringen Ettor och inte hur lång vectorn är.

## Vecka 15

Jag har bestämt mig för att för a en lite gul lösning efter som att jag har får spöknummer när jag använder mig av classens variabel.

    int current_die_number = 1; 
    ClearCountDiceVariable(); 
    // TODO: Fatta vad fan som gör att listan count_dice fuckar upp im jag inte
    // TODO: init i metoden.  
    array<int, 6> count_dice = {0};
    for (int i = 0; i < 6; ++i) {
      cout << count_dice[i] << ",";
    }
    cout << endl; 
    for (int i = 0; i < 6; i++) {
      for (int current_index = 0; current_index < 6; current_index++) {
        if (dice[current_index] == current_die_number) {
          count_dice[i] += 1;
        }
      }
      current_die_number += 1;
      cout << count_dice[i] << " ";
    }
    cout << endl; 
    this->count_dice = count_dice;
    for (int i = 0; i < 6; ++i) {
      cout << this->count_dice[i] << ",";
    }
    cout << endl;

count_dice är alltså redan skapad av classen men min "fula" lösning är att skapa den igen i metoden för att sen sätta den till det värde igen.

## Vecka 11

Jag har ändrat ännu en gång på min struktur. Jag tittade på ditt Black Jack repositorie och tog lite insperation på hur jag skulle kunna tänka. Jag ändrade så att Rule classen nu är Master classen medans Dice klassen styr över alla kombinationer. Jag har också gjort att det går att kassta om tärningarna två gågner och sen kunna välja en kombination eller stryka och få poängen som man ska ha.

Ingen av koden jag skrev var svår att skriva det gälled bara att hitta ett sätt som inte är över kombliserad. Men jag har insett att mitt sätt att kolla vilka kombinationer är möjliga att välja är inte så bra eftersom att jag har en NumberCounter metod som jag använder göt att spara poäng och då kan jag använda den för logiken för att ta reda på vilka kombinationer jag kan välja.

Här kommer koden som räknar poäng:

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

Jag är inte säker om detta är endresultatet av denna koden eller om jag vill göra det på något annat sätt. men just nu så fungerar koden så att den tittar på vart mitt val ligger i start kombinations listan och sedan räknar den tärningarna som den ska räkna ihop.

## Vecka 10

Denna veckan har jag gjort min kod lite mer läsbar och
flyttaT två for loopar in i NumberCounter metoden.
så nu kallar jag NumberCounter en gågn och den gör lite
mer arbete. Detta valde jag göra för att underlätta
läsningen av koden. Sen löste jag så koden skrev ut att
jag kunde välja valer Ettor eftersom att den inte visade
de innan. det jag hade lyckats göra var att for loopen
började på 1.

## Vecka 9

Jag missade denna veckan och jag kommer inte ihåg vad jag gjorde.

## Vecka 8

Denna veckan har jag arbetat ganska mycket. jag har arbetat med hur jag ska hantera data alltså strukturen jag ska ha på dokumentet. Tidigare hade jag en Player och Board class men det skapade massor av problem mellan vad som skulle ha vad så jag komfram till att det är bättre med fler classer. Nu har jag Player, Rule, Dice, Scoreboard, UserInput och Computer. Computer Inherits Player attributes. Denna strukturen gjorde det mycket lättare att hantera datan. Efter jag satte upp strukturen så började jag med reglerna och jag lyckades sätta upp alla möjliga kombinationer så det inte är möjligt att fuska så man får yatzy utan att man har det. den mest komplexa kombinationen att sätta reglerna va kåk.

	bool CheckIfDiceCombinationIsFullHouse(array<int, 5> dice) {
    /* Checks dice one and two if they are equal
    then checks if the rest are equal to each other.
    we only need to check the dice with one in the between because they are
    sorted. check example:
    Can't happend
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

Det var inte svårt att komma fram till hur man skulle göra det. de ända man behöver tänka på är vilket mönster finns i kåk och hur förklarar jag för datorn hur mönstret fungerar. För att underlätta för mig själv sorterar jag listan innan jag kollan kombinationerna. Jag valde också att inte använda and och istället nesta för att göra koden mer läsbar.

## Vecka 7

Denna veckan har jag inte gjort speciellt mycket jag har ändrat strukturen på min kod men strukturen kommer inte funka, eftersom jag har satt en vector i min Board class som innnehåller Player obejecten men jag kommer inte åt spelar obejecterna på de sättet. Jag kom framåt litegranna genom att jag testade min random metod lite mer och jag insåg att den ger ganska lika tal varje gång så jag ändrade den till att brara innehålla system tid upphöjt i tre.

	array<int, 5> RandomDice(int numbers_to_generate) {
    array<int, 5> random = {0, 0, 0, 0, 0};
    sleep(0.00001);
    auto system_time_nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    cout << system_time_nanoseconds << endl;

    std::mt19937 rng(system_time_nanoseconds);
    cout << system_time_nanoseconds << endl;
    for (int i = 0; i < numbers_to_generate; i++) {
      random[i] = 1 + (rng() % 6);
      cout << random[i] << " ";
    }
    cout << endl;
    return random;
  }

Jag har också skaffat lite extensions för vs code så nu formateras min kod när jag sparar.
videon jag hitta på [youtube](https://www.youtube.com/watch?v=q2IVvPGjiaU) visade några riktit bra extensions.

## vecka 6

Denna veckan gjorde jag ganska mycket jag började med att fixa så man kunde bestämma hur många spelare som ska
kunna spela, Jag satte en gräns på fyra men igentligen är inte det pogrammets limmit utan jag skrev in att man
kunnde köra fyra för att göra det enkelt i början men jag ska lägga till så man kan välja ett eget alternativ.
jag fortsatte med att fixa så du kunnde sätta namn på varje spelare. allt detta ver änkelt att skapa. det
senaste jag gjorde var en random metod vilket var mycket svårare. Jag försökte först använda mig av **rand()**
funktionen, men den kunnde inte kombineras med en system time function så jag valde att använda **rng()**
vilket kan annvända sig av system time. Jag valde att hämta system time i millisekunder från början efter som
jag förvänta mig att den skulle vara snabb nog, men när jag skapade en lista med fem täningar i sig för alla
spelare fick jag samma "random" tal. jag satte därför en for loop som lopa typ en miljon gågner för att kika om
det var för kort tid vilket jag insåg var problemet. här kommer koden:

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

Som du ser bytte jag till nanosekunder. **(Jag borde nämna att det var Alex ide att använda system time men
köra system time upphöjt till två)**
Men Bings chat bot spottade ut rng() koden, alltså denna koden:

	auto system_time_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(
        			chrono::system_clock::now().time_since_epoch()
    			).count();
	mt19937 rng(system_time_nanoseconds);
	random[i] = 1 + (rng() % 6);

### **Varför behövs system time?**

det är eftersom en dator kan inte skapa random tal utan det är **pseudo random**. pseudo random betyder att det
inte är random men ser random ut. allt detta gör att man måste bestämma ett **seed** som bestämmer vart ifrån
datorn du ska ta dina pseudo random tal från. Men använder jag bara mig av ststem time kan det bli ganska lätt
att förutspå vilket tal som kommer de förra så jag valde att implementera en hash av nammnet av spelaren. utan
att förklara varje rad kod så gör jag lite matte för att sen gångra nanosekunderna med den om vandlade hashen
upphöjt till två.

### **Om sleep()**

sist tänkte jag skriva lite snabbt om mitt val att implementera en **sleep()**. Det är eftersom jag pratade med

Ronnie och han sa att när man skriver low level programerings språk så är det viktigt att ge rästen av datorns

system att lite tid på den kärnan som ditt pogramm körs på. Men det är inte ända anledningen jag gav speler en
sleep utan jag ville också garantera att ovasett hur snabb eller långsam din dator är ska systemtime hinna
ändras så inte samma det kan bli samma seed.

## vecka 5

Jag har startat projectet och det finns inte mycket och säga. Det finns inget som var speciellt svårt jag har suttit och tittat på syntaxen effter som det var runt ett år sen jag skrev något i c++.
