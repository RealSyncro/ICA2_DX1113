// ICA2_DX1113.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <ios> 
#include <limits> 
#include <stdlib.h>
#include <iomanip>

using std::cout;
using std::cin;
using std::string;
using std::endl;

string F1, F2;

void clearscr() {
    cout << "\033[2J\033[1;1H";
}

void Welcome() {
    string userInputStart;
    string storeMessage[] = { "Welcome to Sudoku!\n", "Enter 'q' to exit the program.\n", "Please select an option.\n\n" , "1. Play Sudoku\n", "2. How to Play Sudoku\n" };
    cout << storeMessage[0] << storeMessage[1] << endl << storeMessage[2] << storeMessage[3] << storeMessage[4] << endl;

    cin >> userInputStart; 
    if (userInputStart == "1") {
        clearscr();
        cout << "You chose the play option.\n";
        ::F1 = userInputStart;
    }
    else if (userInputStart == "2") {
        clearscr();
        cout << "You chose tutorial option.\nEnter input to go back to main menu.\n";
        ::F1 = userInputStart;
    }
    else if (userInputStart == "q") {
        ::F1 = userInputStart;
        cout << "\n> You have exited the program.\n";
    }
    else {
        clearscr();
        cout << "Error! Try again.\n\n";
        Welcome();
    }
}

void tutorial() {
    string backToMenu;
    string instructions[] = { "\nIn Sudoku, the objective is to fill a 9 � 9 grid with digits so that each column, each row," , "\n(also called 'boxes', 'blocks', or 'regions') contain all of the digits from 1 to 9." , 
                              "\nOnce all the grid has been filled in correctly, you win the game.\n\n" };
    cout << instructions[0] << instructions[1] << instructions[2];
    cin >> backToMenu;
    clearscr();
}




void puzzleValidation() {
    
}

char puzzleEasyAns[9][9]{ {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'} };


char puzzleEasy[9][9]{ {'x','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'} };


char move;
int curRow = 0;
int curCol = 0;

int main()
{
    while (true) {
        Welcome();

        if (F1 == "1") {
            while (true) {
                string difficultyInput;
                string diffmsg = "\nYou have chosen ";
                string storeDifficulty[] = { "1. Easy", "2. Medium", "3. Hard" };

                cout << "Please select a difficulty.\nEnter 'q' if you wish to go back to main menu.\n\n";
                for (int i = 0; i < 3; i++) {
                    cout << "\n" << storeDifficulty[i];
                }
                cout << "\n\n";

                cin >> difficultyInput;
                clearscr();

                if (difficultyInput == "1") {
                    cout << diffmsg << "\n" << storeDifficulty[0] << "\n\n";
                }
                else if (difficultyInput == "2") {
                    cout << diffmsg << "\n" << storeDifficulty[1] << "\n\n";
                }
                else if (difficultyInput == "3") {
                    cout << diffmsg << "\n" << storeDifficulty[2] << "\n\n";
                }
                else if (difficultyInput == "q") {
                    cout << "Exit Loop";
                    clearscr();
                    break;
                }
                else {
                    cout << "\nError! Wrong Input!\n";
                }
            }
        }

        if (F1 == "2") {
            tutorial();
            
        }

        if (F1 == "q") {
            return 0;
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
