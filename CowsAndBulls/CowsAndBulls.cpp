/*  This is a little project created by AJ by the idea of
MC Ton4ou and MC Mitkou in order to help us kill some time when we are bored
and develop our programming skills in the process.
*/

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;

const size_t DIGITS = 4;
const bool WITH_REPEATING_DIGITS = false;


typedef bool(*isBullOrCowFunction) (int, size_t, int*);

bool isBull(int digit, size_t position, int* actualNumberDigits);
bool isCow(int digit, size_t position, int* actualNumberDigits);
size_t calculate(isBullOrCowFunction func, int guess, int actual);


int generateRandomNumber(bool withRepeatedDigits = false, size_t digits = DIGITS);

void intToDigitArray(int number, int* digitArray, size_t length = DIGITS, bool reversedOrder = false);
void reverseArray(int* arr, size_t length = DIGITS);
bool arrayHasRepeatingElements(int* arr, size_t length = DIGITS);
bool intHasRepeatingDigits(int num, size_t digitsCount = DIGITS);

bool XOR(bool statement1, bool statement2);


int main()
{
	// Seed the random number generator
	srand(time(NULL));

	// Generates a number to be guessed
	int numberToBeGuessed = generateRandomNumber(WITH_REPEATING_DIGITS, DIGITS);

	// SETUP
	size_t turnCount = 0;

	cout << "Please input numbers while you guess a " << DIGITS << "-digit number " <<
		(WITH_REPEATING_DIGITS ? "with" : "without") << " repeating digits:" <<  endl;

	while (true) { // --------------- GAME LOOP ------------------------
		turnCount++;

		int numberAttempt;

		do {
			cout << turnCount << ") number: "; cin >> numberAttempt;

		} while (numberAttempt < (int)pow(10, DIGITS - 1) || 
			numberAttempt >= (int)pow(10, DIGITS) ||
			XOR(WITH_REPEATING_DIGITS, intHasRepeatingDigits(numberAttempt, DIGITS))
		);
		

		size_t cows = calculate(isCow, numberAttempt, numberToBeGuessed);
		size_t bulls = calculate(isBull, numberAttempt, numberToBeGuessed);


		cout << bulls << " bulls and " << cows << " cows" << endl << endl;

		if (bulls == DIGITS) break;
	} // ---------------------------- END ------------------------------

	cout << "Congratulations! You guessed the number in " << turnCount << " attempts.";

   return 0;

}


int generateRandomNumber(bool withRepeatedDigits, size_t digits) {


	int result = rand() % (int)(9 * pow(10, digits - 1)) + (int)pow(10, digits - 1); //e.g. if digits==4 => result will be between 1000 and 9999

	if (!withRepeatedDigits && intHasRepeatingDigits(result, DIGITS)) {
		result = generateRandomNumber(false, digits);
	}

	return result;
}


void intToDigitArray(int number, int* digitArray, size_t length, bool reversedOrder) {
	for (size_t i = 0; i < length; i++)
	{
		// writing the digits of the number from left to right in the array
		digitArray[i] = (number / (int)pow(10, length - i - 1)) % 10;
	}

	if (reversedOrder) {
		reverseArray(digitArray, length);
	}
}

void reverseArray(int* arr, size_t length) {
	int * arrTemp = new int[length];

	for (size_t i = 0; i < length; i++)
	{
		arrTemp[i] = arr[length - i - 1];
	}

	for (size_t i = 0; i < length; i++)
	{
		arr[i] = arrTemp[i];
	}

	delete arrTemp;
}


bool arrayHasRepeatingElements(int* arr, size_t length) {
	bool result = false;


	for (size_t i = 0; i < length - 1; i++)
	{
		for (size_t j = 1 + i; j < length; j++)
		{
			if (arr[i] == arr[j]) {
				result = true;
				break;
			}
		}

		if (result) break;
	}

	return result;
}

bool intHasRepeatingDigits(int num, size_t digitsCount) {
	int * numDigits = new int[digitsCount];

	intToDigitArray(num, numDigits, digitsCount);
	bool result =  arrayHasRepeatingElements(numDigits, digitsCount);

	delete numDigits;
	return result;
}


bool isCow(int digit, size_t position, int* actualNumberDigits) {
	for (size_t j = 0; j < DIGITS; j++)
	{
		if (digit == actualNumberDigits[j] && position != j) {
			return true;
		}
	}

	return false;
}

bool isBull(int digit, size_t position, int* actualNumberDigits) {
	if (digit == actualNumberDigits[position]) 
		return true;

	return false;
}

size_t calculate(isBullOrCowFunction func, int guess, int actual) {
	int guessDigits[DIGITS];
	int actualDigits[DIGITS];

	intToDigitArray(guess, guessDigits, DIGITS);
	intToDigitArray(actual, actualDigits, DIGITS);

	size_t result = 0;

	for (size_t i = 0; i < DIGITS; i++)
	{
		if (func(guessDigits[i], i, actualDigits))
			result++;
	}

	return result;
}

bool XOR(bool statement1, bool statement2) {
	return ((statement1 || statement2) && !(statement1 && statement2));
}
