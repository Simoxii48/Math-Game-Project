#include <iostream>
#include <limits>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;

enum enGameLevel
{
	Easy = 1,
	Med = 2,
	Hard = 3,
	MixLevel = 4
};

enum enOppTypes
{
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	MixOpp = 5
};

struct stGame
{
	short numberOfQuestions = 0;
	enGameLevel gameLevel{};
	enOppTypes oppType{};
	short numberOfCorrectAnswers = 0;
	short numberOfWrongAnswers = 0;
	bool isPassed = false;
};

struct stRound
{
	short rightAnswer = 0;
	short userAnswer = 0;
	enOppTypes oppChoosed{};
};

short readQuestionsNumber()
{
	short qNumbers = 0;

	cout << "\tHow many questions do you want to answer : ";

	while (!(cin >> qNumbers))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\n\tInvalid Datatype, Please enter a number : ";
	}

	return qNumbers;
}

short readValidateInput(short from, short to)
{
	short input = 0;

	while (!(cin >> input) || input<from || input>to)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\n\tInvalid range or Invalid datatype, please enter a number format from " << from << " To " <<  to << " : ";
	}

	return input;
}

enGameLevel readGameLevel()
{
	cout << "\n\tEnter Questions Level, [1] Easy, [2] Med, [3] Hard, [4] Mix. : ";

	return static_cast<enGameLevel>(readValidateInput(1, 4));
}

enOppTypes readOppTypes()
{
	cout << "\n\tEnter Opperation Type, [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix : ";

	return static_cast<enOppTypes>(readValidateInput(1, 5));
}

short randomNumber(short from, short to)
{
	return rand() % (to - from + 1) + from;
}

short generateNumber(enGameLevel& gameLevel)
{
	switch (gameLevel)
	{
	case Easy:
		return randomNumber(0, 10);
	case Med:
		return randomNumber(10, 50);
	case Hard:
		return randomNumber(50, 100);
	case MixLevel:
	{
		enGameLevel random = (enGameLevel)randomNumber(1, 3);
		switch (random)
		{
		case Easy:
			return randomNumber(0, 10);
		case Med:
			return randomNumber(10, 50);
		case Hard:
			return randomNumber(50, 100);
		default:
			return -32000;
		}
	}
	default:
		return -32000;
	}
}

bool checkIsCorrectAnswer(short answer, short rightAnswer)
{
	return (answer == rightAnswer);
}

string oppTypeToPrint(enOppTypes& oppType)
{
	switch (oppType)
	{
	case Add:
		return "+";
	case Div:
		return "/";
	case Mul:
		return "*";
	case Sub:
		return "-";
	default:
		return "";
	}
}

void printQuestion(enOppTypes& oppType, short& num1, short& num2)
{
	cout << "\t" << num1 << endl;
	cout << "\t" << num2;
	cout << "\t" << oppTypeToPrint(oppType);
	cout << "\n\t_____________________________ \n \t= ";
}

short calculateCorrectAnswer(enOppTypes& opp, stRound& R,const short& num1,short& num2)
{
	switch (opp)
	{
	case Add:
		R.rightAnswer = num1 + num2;
		break;
	case Div:
	{
		if (num2 == 0)
			num2 = 1;

		R.rightAnswer = num1 / num2;
		break;
	}
	case Mul:
		R.rightAnswer = num1 * num2;
		break;
	case Sub:
		R.rightAnswer = num1 - num2;
		break;
	case MixOpp:
	{
		enOppTypes oppType = (enOppTypes)randomNumber(1, 4);
		switch (oppType)
		{
		case Add:
			R.rightAnswer = num1 + num2;
			break;
		case Div:
		{
			if (num2 == 0)
				num2 = 1;

			R.rightAnswer = num1 / num2;
			break;
		}
		case Mul:
			R.rightAnswer = num1 * num2;
			break;
		case Sub:
			R.rightAnswer = num1 - num2;
			break;
		}
	}
	}

	return R.rightAnswer;
}

string gameLevelTostring(const enGameLevel& gameLvl)
{
	switch (gameLvl)
	{
	case Easy:
		return "Easy";
	case Med:
		return "Med";
	case Hard:
		return "Hard";
	case MixLevel:
		return "Mix";
	default:
		return "";
	}
}

string oppTypeToString(const enOppTypes& oppType)
{
	switch (oppType)
	{
	case Add:
		return "Add";
	case Mul:
		return "Mul";
	case Div:
		return "Div";
	case Sub:
		return "Sub";
	case MixOpp:
		return "Mix";
	default:
		return "";
	}
}

void printFinalGameResult(const stGame& G)
{
	cout << "\n\n\t################################################\n";
	cout << "\t	Final results is " << (G.isPassed ? "Pass :)" : "Fail :(");
	cout << "\n\t################################################\n";

	cout << "\n\tNumber of questions : " << G.numberOfQuestions << "\n";
	cout << "\tQuestion Level		 : " << gameLevelTostring(G.gameLevel) << "\n";
	cout << "\tOpperation Type		 : " << oppTypeToString(G.oppType) << "\n";
	cout << "\tNumber Of correct Answers : " << G.numberOfCorrectAnswers << "\n";
	cout << "\tNumber Of wrong Answers   : " << G.numberOfWrongAnswers << endl;
}

void setScreenColor(bool isPassed)
{
	isPassed ? system("color 2F") : system("color 4F");
}

enOppTypes oppChoosed()
{
	return (enOppTypes)randomNumber(1, 4);
}

void simulate(short numberOfquestions)
{
	stGame game{};
	stRound round{};

	game.numberOfQuestions = numberOfquestions;
	game.gameLevel = readGameLevel();
	game.oppType = readOppTypes();



	for (short i = 0;i < numberOfquestions;i++)
	{
		short num1 = generateNumber(game.gameLevel);
		short num2 = generateNumber(game.gameLevel);

		cout << "\n	Question [" << i + 1 << "/" << numberOfquestions << "]" << endl;
		round.oppChoosed = (game.oppType == enOppTypes::MixOpp ? oppChoosed() : game.oppType);
		
		round.rightAnswer = calculateCorrectAnswer(round.oppChoosed, round, num1, num2);

		printQuestion(round.oppChoosed, num1, num2);
		round.userAnswer = readValidateInput(-32000, 32000);

		if (checkIsCorrectAnswer(round.userAnswer, round.rightAnswer))
		{
			system("color 2F");
			game.numberOfCorrectAnswers++;
			cout << "\n\tCorrect Answer :)\n";
		}
		else
		{
			system("color 4F");
			game.numberOfWrongAnswers++;
			cout << "\n\tWrong Answer :(\n\t";
			cout << "Correct answer is " << round.rightAnswer << endl;
		}
	}

	game.isPassed = (game.numberOfCorrectAnswers >= game.numberOfWrongAnswers);
	setScreenColor(game.isPassed);
	printFinalGameResult(game);
}

void playGame()
{
	char playMore = 'y';

	do
	{
		system("cls");
		system("color 0F");

		simulate(readQuestionsNumber());

		cout << "\n\tDo you want to play more, [Y,y] Yes, [N,n] No : ";
		cin >> playMore;
	} while (toupper(playMore) == 'Y');
}


//	Prof Version To Look Later
/*

#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration: enQuestionsLevel
// Purpose: Defines the difficulty levels available for quiz questions.
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

// Enumeration: enOperationType
// Purpose: Defines the types of arithmetic operations used in the quiz.
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
// Parameters:
//   - From: Lower bound of the random range.
//   - To: Upper bound of the random range.
// Returns: A random integer between From and To.
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

// Function: GetOpTypeSymbol
// Purpose: Converts an operation type to its corresponding symbol.
// Parameters:
//   - OpType: The arithmetic operation type.
// Returns: A string representation of the operator.
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

// Function: GetRandomOperationType
// Purpose: Generates a random arithmetic operation type.
// Returns: A random enOperationType value.
enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

// Function: GetQuestionLevelText
// Purpose: Converts an enQuestionsLevel enum to a string representation.
// Parameters:
//   - QuestionLevel: The selected difficulty level.
// Returns: A string representation of the difficulty level.
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

// Function: SetScreenColor
// Purpose: Changes the console screen color based on answer correctness.
// Parameters:
//   - Right: Boolean value indicating if the answer is correct.
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

// Function: SimpleCalculator
// Purpose: Performs the selected arithmetic operation on two numbers.
// Parameters:
//   - Number1: First operand.
//   - Number2: Second operand.
//   - OpType: The operation type (Add, Sub, Mult, or Div).
// Returns: The result of the operation.
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
		return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
	default:
		return Number1 + Number2;
	}
}

// Structure: stQuestion
// Purpose: Stores information for a single quiz question.
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

// Structure: stQuizz
// Purpose: Stores details of the entire quiz session.
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

// Function: GenerateQuestion
// Purpose: Creates a random math question based on difficulty and operation type.
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QuestionLevel;

	return Question;
}

// Function: AskAndCorrectQuestionListAnswers
// Purpose: Iterates through quiz questions, evaluates answers, and provides feedback.
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
		cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
			<< GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
			<< Quizz.QuestionList[QuestionNumber].Number2 << " = ";

		cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

		if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
		{
			cout << "Correct!\n";
			Quizz.NumberOfRightAnswers++;
		}
		else
		{
			cout << "Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
			Quizz.NumberOfWrongAnswers++;
		}
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

// Function: PlayMathGame
// Purpose: Initializes the quiz, generates questions, and manages the quiz flow.
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = 5;  // Set a fixed number of questions.
	Quizz.QuestionsLevel = enQuestionsLevel::EasyLevel;
	Quizz.OpType = enOperationType::MixOp;

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}

	AskAndCorrectQuestionListAnswers(Quizz);

	cout << "\nQuiz Completed! Right Answers: " << Quizz.NumberOfRightAnswers
		<< ", Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";

	cout << (Quizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
}

// Main Function
int main()
{
	srand((unsigned)time(NULL));  // Seed the random number generator.
	PlayMathGame();  // Start the quiz game.
	return 0;  // Exit the program successfully.
}
*/

int main()
{
	srand((unsigned)time(NULL));

	playGame();
	return 0;
}