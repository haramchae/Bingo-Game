#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

enum AI_MODE {
	EASY_MODE = 1,
	HARD_MODE
};

enum LINE_NUMBER {
	D_NUM1 = 10,
	D_NUM2
};

int numArray[25] = {};
int AIArray[25] = {};
int bingo = 0;
int playerBingo = 0;
int AIBingo = 0;
int AIModeNum;
int AINum;
vector<int> check;

void shuffle();
void printBingo(int Array[]);
void changeNum(int index);
void AISelectNum();
void bingoCheck(int TArray[]);
void hardSelect();

int main() {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 25; i++) {
		numArray[i] = i + 1;
		AIArray[i] = i + 1;
	}

	shuffle();

	while (true) {
		//system("cls");
		cout << "Choose the mode you want to play" << "\n";
		cout << "1. ESAY mode" << "\n";
		cout << "2. HARD mode" << "\n";
		cin >> AIModeNum;
		if (AIModeNum >= EASY_MODE && AIModeNum <= HARD_MODE) break;
	}

	int AICheckNum = 0;

	while (true)
	{
		system("cls");

		cout << "Player bingo***********************" << "\n";
		printBingo(numArray);
		cout << "Player Bingo line: " << playerBingo << "\n";

		cout << "AI bingo***************************" << "\n";
		switch (AIModeNum) {
		case EASY_MODE:
			cout << "EASY mode" << "\n";
			break;

		case HARD_MODE:
			cout << "Hard mode" << "\n";
			break;
		}
		printBingo(AIArray);
		cout << "AI Bingo line: " << AIBingo << "\n";

		if (playerBingo >= 5 && AIBingo < playerBingo) {
			cout << "Player win!!" << "\n";
			break;
		}
		else if (AIBingo >= 5 && AIBingo > playerBingo) {
			cout << "AI win!!" << "\n";
			break;
		}
		else if (playerBingo == 5 && AIBingo == 5) {
			cout << "Draw!!" << "\n";
			break;
		}
		cout << "EXIT(Enter 0)" << "\n";
		if (AICheckNum++ > 0) {
			cout << "AI select: " << AINum << "\n";
		}
		cout << "Enter the number: ";

		int num;
		cin >> num;

		if (num == 0) {
			cout << "Game Exit!\n";
			break;
		}

		if (num < 0 || num>25) {
			continue;
		}
		if (find(check.begin(), check.end(), num) == check.end()) {
			check.push_back(num);
			changeNum(num);
			AISelectNum();
			bingo = 0;
			bingoCheck(numArray);
			playerBingo = bingo;
			bingo = 0;
			bingoCheck(AIArray);
			AIBingo = bingo;
		}
	}
	return 0;
}

void shuffle() {
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = numArray[idx1];
		numArray[idx1] = numArray[idx2];
		numArray[idx2] = temp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = AIArray[idx1];
		AIArray[idx1] = AIArray[idx2];
		AIArray[idx2] = temp;
	}
}

void printBingo(int Array[]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (Array[i * 5 + j] == INT_MIN) {
				cout << "*\t";
			}
			else {
				cout << Array[i * 5 + j] << "\t";
			}

		}
		cout << "\n";
	}
}

void changeNum(int num) {
	for (int i = 0; i < 25; i++) {
		if (numArray[i] == num) numArray[i] = INT_MIN;
		if (AIArray[i] == num) {
			AIArray[i] = INT_MIN;
		}
	}
}

void AISelectNum() {
	int randomIndex;
	vector<int> indexV;
	switch (AIModeNum)
	{
	case EASY_MODE:
		for (int i = 0; i < 25; i++) {
			if (AIArray[i] != INT_MIN) {
				indexV.push_back(i);
			}
		}
		randomIndex = indexV[rand() % indexV.size()];	
		AINum = AIArray[randomIndex];
		changeNum(AIArray[randomIndex]);
		break;
	case HARD_MODE:
		hardSelect();
		break;
	default:
		break;
	}
}

void bingoCheck(int TArray[]) {
	int check1 = 0, check2 = 0;
	for (int i = 0; i < 5; i++) {
		check1 = 0, check2 = 0;
		for (int j = 0; j < 5; j++) {
			if (TArray[i * 5 + j] == INT_MIN) check1++;
			if (TArray[j * 5 + i] == INT_MIN) check2++;
		}
		if (check1 == 5) bingo++;
		if (check2 == 5) bingo++;
	}

	check1 = 0, check2 = 0;
	for (int i = 0, j = 4; i < 25; i += 6, j += 4) {
		if (TArray[i] == INT_MIN) check1++;
		if (TArray[j] == INT_MIN) check2++;
	}
	if (check1 == 5) bingo++;
	if (check2 == 5) bingo++;
}

void hardSelect() {
	int line = 0;
	int tempCount = 0;
	int StarCount1 = 0;
	int StarCount2 = 0;

	for (int i = 0; i < 5; i++) {
		StarCount1 = 0, StarCount2 = 0;
		for (int j = 0; j < 5; j++) {
			if (AIArray[i * 5 + j] == INT_MIN) StarCount1++;
			if (AIArray[j * 5 + i] == INT_MIN) StarCount2++;
		}
		if (StarCount1 < 5 && tempCount < StarCount1) {
			line = i;
			tempCount = StarCount1;
		}
		else if (StarCount2 < 5 && tempCount < StarCount2) {
			line = i + 5;
			tempCount = StarCount2;
		}
	}

	StarCount1 = 0, StarCount2 = 0;
	for (int i = 0, j = 4; i < 25; i += 6, j += 4) {
		if (AIArray[i] == INT_MIN) StarCount1++;
		if (AIArray[j] == INT_MIN) StarCount2++;
	}
	if (StarCount1 < 5 && tempCount < StarCount1) {
		line = D_NUM1;
		tempCount = StarCount1;
	}
	else if (StarCount2 < 5 && tempCount < StarCount2) {
		line = D_NUM2;
		tempCount = StarCount2;
	}
	if (line == D_NUM1) {
		for (int i = 0; i < 25; i += 6) {
			if (AIArray[i] != INT_MIN) {
				AINum = AIArray[i];
				changeNum(AIArray[i]);
				break;
			}
		}
	}
	else if (line == D_NUM2) {
		for (int i = 5; i <= 20; i += 4) {
			if (AIArray[i] != INT_MIN) {
				AINum = AIArray[i];
				changeNum(AIArray[i]);
				break;
			}
		}
	}
	else if (line <= 4) {
		for (int i = 0; i < 5; i++) {
			if (AIArray[line * 5 + i] != INT_MIN) {
				AINum = AIArray[line * 5 + i];
				changeNum(AIArray[line * 5 + i]);
				break;
			}
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			if (AIArray[i*5 + (line-5)] != INT_MIN) {
				AINum = AIArray[i * 5 + (line - 5)];
				changeNum(AIArray[i * 5 + (line - 5)]);
				break;
			}
		}
	}
}

