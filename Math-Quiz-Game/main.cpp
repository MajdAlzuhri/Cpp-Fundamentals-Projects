#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Subtract = 2, Multiply = 3, Divide = 4, MixOperation = 5 };

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
    short Number;

    do
    {
        cout << "How many questions do you want? [1 to 100]: ";
        cin >> Number;
    } while (Number < 1 || Number > 100);

    return Number;
}

enQuestionLevel ReadQuestionsLevel()
{
    short Level;

    do
    {
        cout << "Enter question level [1]: Easy, [2]: Medium, [3]: Hard, [4]: Mix: ";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return static_cast<enQuestionLevel>(Level);
}

enOperationType ReadOperationType()
{
    short Operation;

    do
    {
        cout << "Enter operation type [1]: Add, [2]: Subtract, [3]: Multiply, "
                "[4]: Divide, [5]: Mix: ";
        cin >> Operation;
    } while (Operation < 1 || Operation > 5);

    return static_cast<enOperationType>(Operation);
}

enOperationType GetRandomOperationType()
{
    return static_cast<enOperationType>(RandomNumber(1, 4));
}

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Add:
        return Number1 + Number2;

    case enOperationType::Subtract:
        return Number1 - Number2;

    case enOperationType::Multiply:
        return Number1 * Number2;

    case enOperationType::Divide:
        return Number1 / Number2;

    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel,
                            enOperationType OperationType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::MixLevel)
        QuestionLevel = static_cast<enQuestionLevel>(RandomNumber(1, 3));

    if (OperationType == enOperationType::MixOperation)
        OperationType = GetRandomOperationType();

    Question.QuestionLevel = QuestionLevel;
    Question.OperationType = OperationType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;

    case enQuestionLevel::Medium:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;

    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;

    default:
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(
        Question.Number1,
        Question.Number2,
        Question.OperationType);

    return Question;
}

void GenerateQuizQuestions(stQuiz& Quiz)
{
    for (short QuestionNumber = 0;
         QuestionNumber < Quiz.NumberOfQuestions;
         QuestionNumber++)
    {
        Quiz.QuestionList[QuestionNumber] = GenerateQuestion(
            Quiz.QuestionsLevel,
            Quiz.OperationType);
    }
}

string GetOperationTypeSymbol(enOperationType OperationType)
{
    string OperationSymbols[5] = { "+", "-", "*", "/", "Mix" };
    return OperationSymbols[OperationType - 1];
}

void PrintQuestion(const stQuiz& Quiz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/"
         << Quiz.NumberOfQuestions << "]\n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOperationTypeSymbol(
        Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_________\n";
}

int ReadQuestionAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

void CorrectQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;

        cout << "Wrong answer :-(\n";
        cout << "The correct answer is: "
             << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;

        cout << "Right answer :-)\n";
    }
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
    for (short QuestionNumber = 0;
         QuestionNumber < Quiz.NumberOfQuestions;
         QuestionNumber++)
    {
        PrintQuestion(Quiz, QuestionNumber);

        Quiz.QuestionList[QuestionNumber].PlayerAnswer =
            ReadQuestionAnswer();

        CorrectQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.IsPass =
        (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool IsPass)
{
    return IsPass ? "Pass :-)" : "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string LevelNames[4] = { "Easy", "Medium", "Hard", "Mix" };
    return LevelNames[QuestionLevel - 1];
}

void PrintQuizResult(const stQuiz& Quiz)
{
    cout << "\n_______________________________________________\n\n";
    cout << "Final result: " << GetFinalResultText(Quiz.IsPass) << endl;
    cout << "_______________________________________________\n\n";
    cout << "Number of questions: " << Quiz.NumberOfQuestions << endl;
    cout << "Question level: "
         << GetQuestionLevelText(Quiz.QuestionsLevel) << endl;
    cout << "Operation type: "
         << GetOperationTypeSymbol(Quiz.OperationType) << endl;
    cout << "Right answers: " << Quiz.NumberOfRightAnswers << endl;
    cout << "Wrong answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "_______________________________________________\n";
}

void PlayMathGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionsLevel = ReadQuestionsLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResult(Quiz);
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
        PlayMathGame();

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
