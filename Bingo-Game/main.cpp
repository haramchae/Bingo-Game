#include <iostream>
#include <time.h>

using namespace std;

int numArray[25] = {};
int bingo = 0;

void shuffle();
void changeNum(int index);
void bingoCheck();

int main() {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 25; i++) {
		numArray[i] = i + 1;
	}

	shuffle();

	while (true)
	{
		system("cls");

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (numArray[i * 5 + j] == INT_MIN) {
					cout << "*\t";
				}
				else {
					cout << numArray[i * 5 + j] << "\t";
				}

			}
			cout << "\n";
		}

		cout << "Bingo line: " << bingo << "\n";
		if (bingo >= 5) break;
		cout << "EXIT(Enter 0)" << "\n";
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
		changeNum(num);
		bingo = 0;
		bingoCheck();
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
	}
}

void changeNum(int num) {
	for (int i = 0; i < 25; i++) {
		if (numArray[i] == num) numArray[i] = INT_MIN;

	}
}

void bingoCheck() {
	int check1 = 0, check2 = 0;
	for (int i = 0; i < 5; i++) {
		check1 = 0, check2 = 0;
		for (int j = 0; j < 5; j++) {
			if (numArray[i * 5 + j] == INT_MIN) check1++;
			if (numArray[j * 5 + i] == INT_MIN) check2++;
		}
		if (check1 == 5) bingo++;
		if (check2 == 5) bingo++;
	}

	check1 = 0, check2 = 0;
	for (int i = 0, j = 4; i < 25; i += 6, j += 4) {
		if (numArray[i] == INT_MIN) check1++;
		if (numArray[j] == INT_MIN) check2++;
	}
	if (check1 == 5) bingo++;
	if (check2 == 5) bingo++;
}

