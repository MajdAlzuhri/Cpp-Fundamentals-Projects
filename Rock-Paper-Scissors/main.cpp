#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResult
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short Rounds;

    do
    {
        cout << "How many rounds do you want to play? ";
        cin >> Rounds;
    } while (Rounds <= 0);

    return Rounds;
}

enGameChoice ReadPlayerChoice()
{
    short Choice;

    do
    {
        cout << "\nEnter your choice [1]: Stone, [2]: Paper, [3]: Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return static_cast<enGameChoice>(Choice);
}

enGameChoice GetComputerChoice()
{
    return static_cast<enGameChoice>(RandomNumber(1, 3));
}

enWinner WhoWonTheRound(const stRoundInfo& RoundInfo)
{
    if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }

    return enWinner::Player;
}

string GetWinnerName(enWinner Winner)
{
    string WinnerNames[3] = { "Player", "Computer", "Draw" };
    return WinnerNames[Winner - 1];
}

string GetChoiceName(enGameChoice Choice)
{
    string ChoiceNames[3] = { "Stone", "Paper", "Scissors" };
    return ChoiceNames[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResult(const stRoundInfo& RoundInfo)
{
    cout << "____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player Choice: " << GetChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << GetChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: [" << RoundInfo.WinnerName << "]\n";
    cout << "________________________________________\n";

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes == ComputerWinTimes)
        return enWinner::Draw;

    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;

    return enWinner::Computer;
}

stGameResult FillGameResult(short Rounds, short PlayerWinTimes,
                            short ComputerWinTimes, short DrawTimes)
{
    stGameResult GameResult;

    GameResult.GameRounds = Rounds;
    GameResult.PlayerWinTimes = PlayerWinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResult.WinnerName = GetWinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResult PlayGame(short Rounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;

    for (short GameRound = 1; GameRound <= Rounds; GameRound++)
    {
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResult(Rounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string Result = "";

    for (short i = 0; i < NumberOfTabs; i++)
        Result += "\t";

    return Result;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "________________________________________________\n\n";
    cout << Tabs(2) << "                    +++ Game Over +++\n";
    cout << Tabs(2) << "________________________________________________\n\n";
}

void ShowFinalGameResults(const stGameResult& GameResult)
{
    cout << Tabs(2) << "_______________ [Game Results] _______________\n\n";
    cout << Tabs(2) << "Game Rounds:        " << GameResult.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times:   " << GameResult.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Won Times: " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times:         " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner:       " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "________________________________________________\n\n";

    SetWinnerScreenColor(GameResult.GameWinner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();

        stGameResult GameResult = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResult);

        cout << "Do you want to play again? Y/N: ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    StartGame();

    return 0;
}
