#include<cmath>
#include <iostream>
#include<string>
#include<cstdlib>
using namespace std;

int RandomNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}

enum enQuestionlevel {Easy = 1 , Middle = 2 , Hard = 3 , Mix = 4};

enum enOperationType {Add = 1 , Sub = 2 , Mult = 3 , Div = 4 , MixOp = 5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionlevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionlevel QuestionLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool IsPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;
    do
    {
        cout << "How Many Questions Do You Want To Answer ?" << endl;
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionlevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Select Questions Level : [1]: Easy , [2]: Middle , [3]: Hard , [4]: Mix ?" << endl;
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel >4);

    return (enQuestionlevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OperationType = 0;
    do
    {
        cout << "Please Choose An Operation Type : [1]:Add , [2]:Sub , [3]:Mult , [4]:Div , [5]:Mix ? " << endl;
        cin >> OperationType;

    } while (OperationType < 1 || OperationType > 5);

    return (enOperationType)OperationType;
}

enOperationType GenerateOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionlevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionlevel::Mix)
    {
        QuestionLevel = (enQuestionlevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GenerateOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionlevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionlevel::Middle:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionlevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    }

    return Question;
}

string GetOpSymbol(enOperationType OpType)
{
    string symbols[5] = { "+", "-", "*", "/", "Mix" };
    return symbols[OpType - 1];
}

string GetQuestionLevelText(enQuestionlevel QuestionLevel)
{
    string arrQuestionlevel[4] = {"Easy" , "Middle" , "Hard" , "Mix"};
    return arrQuestionlevel[QuestionLevel - 1];
}

void GenerateQuizQuestions(stQuiz& Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
    cout << endl;
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "] \n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpSymbol(Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n----------" << endl;
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :/ " << endl;
        cout << "The Right Answer is : ";
        cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
        system("color 4F");
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;
        cout << "Right Answer :) " << endl;
        system("color 2F");
    }
    cout << endl;


}

void AskAndCorrectQuestionListAnswer(stQuiz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);

        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.IsPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool Pass)
{
    if (Pass)
        return "Pass :)";
    else
        return "Fail :/";
}

void PrintQuizResult(stQuiz Quiz)
{
    cout << endl;
    cout << "\n______________________________\n\n";
    cout << " Final Result Is " << GetFinalResultText(Quiz.IsPass);
    cout << "\n______________________________\n\n";
    cout << "Number Of Questions : " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level     : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << "OpType              : " << GetOpSymbol(Quiz.OpType) << endl;
    cout << "Right Answers       : " << Quiz.NumberOfRightAnswers << endl;
    cout << "Wrong Answers       : " << Quiz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n\n";
}

void PlayMathGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadQuestionsLevel();
    Quiz.OpType = ReadOpType();

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswer(Quiz);
    PrintQuizResult(Quiz);
}

void ResetSecreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetSecreen();
        PlayMathGame();
        cout << "Do You Want To Play Again ? Y/N ?" << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}

