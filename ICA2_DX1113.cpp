// ICA2_DX1113.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <ios> [Stream 10]
#include <limits> [Get Numeric Limits]
#include <stdlib.h>
#include <iomanip>


using std::cout;
using std::cin;
using std::string;
using std::endl;

void prtMessage() {
    cout << "Hello World!\n";
}

void Welcome() {
    string storeMessage[] = { "Welcome to Sudoku!\n", "What difficulty would you like to select?\n", "1. Easy\n2. Normal\n3. Hard\n\n" };
    cout << storeMessage[0] << storeMessage[1] << storeMessage[2];
}

void DifficultySelector() {
    string difficultyInput; 
    string storeDifficulty[] = { "\nEasy\n", "\nMedium\n", "\nHard\n" };

    cout << "Please select a difficulty.\n";
    cin >> difficultyInput;
    if (difficultyInput == "1") {
        cout << storeDifficulty[0];
    }
    else if (difficultyInput == "2") {
        cout << storeDifficulty[1];
    }
    else if (difficultyInput == "3") {
        cout << storeDifficulty[2];
    }
    else {
        cout << "\nError! Wrong Input!\n";
        DifficultySelector();
    }
}



int main()
{

    while (true) {
        Welcome();
        DifficultySelector();

    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
