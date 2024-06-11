//My Solution With No Edits
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <Windows.h>

using namespace std;

enum enPlayerChoice {Stone = 1, Paper = 2, Scissor = 3};
enum enWinner {Player1 = 1, Computer = 2, Draw = 3};

struct stGameResults {
    int GameRounds = 0;
    int Player1WonTimes = 0;
    int CoumputerWonTimes = 0;
    int DrawTimes = 0;
    enWinner GameWinner;
    string FinalWinner;
};

struct stRoundInfo {
    short RoundNumber = 0;
    enPlayerChoice Player1Choice;
    enPlayerChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};


int RandomChoice(int From, int To) {
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

enPlayerChoice PlayerChoice() {
    short PlayerChoice;
    do {
    cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors: " << endl;
    cin >> PlayerChoice;
    } while (PlayerChoice > 3 || PlayerChoice < 1);

    if (PlayerChoice == 1)
        return enPlayerChoice::Stone;
    else if (PlayerChoice == 2)
        return enPlayerChoice::Paper;
    else
        return enPlayerChoice::Scissor;
}

enPlayerChoice ComputerChoice() {
    short ComputerChoice = RandomChoice(1, 3);

    if (ComputerChoice == 1)
        return enPlayerChoice::Stone;
    else if (ComputerChoice == 2)
        return enPlayerChoice::Paper;
    else
        return enPlayerChoice::Scissor;
}

void SetScreenColor(enWinner Winner) {
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F"); // Turn Screen to Green
        break;
    case enWinner::Computer:
        system("color 4F"); // Turn Screen To Red
        break;
    default:
        system("color 6F"); // Turn Screen To Yellow
        break;
    }
}

short ReadHowManyRounds() {
    short RoundsNumber = 0;
    do {
        cout << "How Many Rounds 1 to 10? \n";
        cin >> RoundsNumber;
        cout << endl;
    } while (RoundsNumber <= 0);
    return RoundsNumber;
}

void ClearTerminal() {
    system("CLS");
    system("color 0F");
}

enWinner RoundWinner(stRoundInfo RoundInfo) {
    if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice) {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice) {
    case enPlayerChoice::Stone:
        if (RoundInfo.ComputerChoice == enPlayerChoice::Paper) {
            return enWinner::Computer;
        }
        break;
    case enPlayerChoice::Paper:
        if (RoundInfo.ComputerChoice == enPlayerChoice::Scissor) {
            return enWinner::Computer;
        }
        break;
    case enPlayerChoice::Scissor:
        if (RoundInfo.ComputerChoice == enPlayerChoice::Stone) {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string ChoiceExchange(enPlayerChoice Choice) {
    if (Choice == 1)
        return "Stone";
    else if (Choice == 2)
        return "Paper";
    else if (Choice == 3)
        return "Scissor";
}

string Tabs(short NumberOfTabs) {
    string t = "";

    for (int i = 1; i < NumberOfTabs; i++) {
        t += "\t";
        cout << t;
    }
    return t;
}


string WinnerName(enWinner Winner) {
    if (Winner == 1)
        return "Player1";
    else if (Winner == 2)
        return "Computer";
    else
        return "Draw";
}

void PrintRoundResults(stRoundInfo RoundInfo) {
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceExchange(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceExchange(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << WinnerName(RoundInfo.Winner) << "] \n";
    cout << "__________________________________\n" << endl;
    SetScreenColor(RoundInfo.Winner);
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults) {
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WonTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.CoumputerWonTimes<< endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.FinalWinner << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetScreenColor(GameResults.GameWinner);
}

enWinner TheGameWinner(short Player1Won, short ComputerWon) {
    if (Player1Won == ComputerWon)
        return enWinner::Draw;
    else if (Player1Won > ComputerWon)
        return enWinner::Player1;
    else
        return enWinner::Computer;
}

stGameResults FillGameResults(int GameRounds, int Player1WinTimes, int ComputerWinTimes, int DrawTime) {
    stGameResults GameResults;
    GameResults.CoumputerWonTimes = ComputerWinTimes;
    GameResults.Player1WonTimes = Player1WinTimes;
    GameResults.DrawTimes = DrawTime;
    GameResults.GameRounds = GameRounds;
    GameResults.GameWinner = TheGameWinner(Player1WinTimes, ComputerWinTimes);
    GameResults.FinalWinner = WinnerName(GameResults.GameWinner);

    return GameResults;
}


stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    int Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins: \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = PlayerChoice();
        RoundInfo.ComputerChoice = ComputerChoice();
        RoundInfo.Winner = RoundWinner(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}


bool PlayAgain() {
    char PlayAgainc = 'Y';
    cout << "Do You Want To Play Again Y/N: ";
    cin >> PlayAgainc;
    if (PlayAgainc == 'y' || PlayAgainc == 'Y') 
        return true;
    else
        return false;

}
void StartGame() {
    
    do {
        ClearTerminal();
        stGameResults GameResutls = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResutls);
    } while (PlayAgain());
}


int main() {
    
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}