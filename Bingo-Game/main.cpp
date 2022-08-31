#include <iostream>
#include <time.h>

using namespace std;

int numArray[25] = {};

void shuffle();
void changeNum(int index);

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
		if (numArray[i] == num) {
			numArray[i] = INT_MIN;
		}
	}
}

