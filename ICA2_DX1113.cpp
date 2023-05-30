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

string F1; 

void clearscr() {
    cout << "\033[2J\033[1;1H";
}

void Welcome() {
    string userInputStart;
    string storeMessage[] = { "Welcome to Sudoku!\n", "Please select an option.\n", "1. Play Sudoku\n", "2. How to Play Sudoku\n", "1. Easy\n2. Normal\n3. Hard\n\n" };
    cout << storeMessage[0] << storeMessage[1] << endl << storeMessage[2] << storeMessage[3] << endl;

    cin >> userInputStart; 
    if (userInputStart == "1") {
        clearscr();
        cout << "You chose the play option.\n";
        ::F1 = "1";
    }
    else if (userInputStart == "2") {
        clearscr();
        cout << "You chose tutorial option.\n";
        ::F1 = "2";
    }
    else if (userInputStart == "q") {

    }
    else {
        cout << "Error! Try again.\n";
        Welcome();
    }
}

void tutorial(){
   
}



void puzzleValidation() {
    
}

int puzzleEasyAns[9][9]{ {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, 
                         {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, 
                         {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9} };

int main()
{
   
    while (true) {
        Welcome();



        if (F1 == "1") {
            while (true) {
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
                }
            }
        }

        if (F1 == "q") {
            break;
        }
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
