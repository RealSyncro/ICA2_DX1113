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

/****************************************************************************/
////////                     Global Variables                          ///////
/****************************************************************************/

//Decision Control Variable
string F1, F2;

//Player Movement Variable
char move;
int curRow = 0;
int curCol = 0;


/****************************************************************************/
////////                      Sudoku Puzzles                        //////////
/****************************************************************************/
const char puzzleEasyAns[9][9]{ {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'},
                                {'1','2','3','4','5','6','7','8','9'} };


char puzzleEasy[9][9]{ {'X','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'},
                       {'-','-','-','-','-','-','-','-','-'} };

char puzzleEasyTest[9][9]{{'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'},
                          {'1','2','3','4','5','6','7','8','9'} };

/****************************************************************************/
////////                        Functions                           //////////
/****************************************************************************/

void clearscr() {
    cout << "\033[2J\033[1;1H";
}

void Welcome() {
    string optionIn;
    string storeMessage[] = { "Welcome to Sudoku!\n", "[Enter 'q' to exit the program.]\n", "Please select an option.\n\n" , "1. Play Sudoku\n", "2. How to Play Sudoku\n" };
    for (int i = 0; i < sizeof(storeMessage) / sizeof(string); i++) {
        cout << storeMessage[i];
    }

    cout << endl;
    cin >> optionIn;

    //Check User Selected Option
    if (optionIn == "1") {
        clearscr();
        cout << "You chose the play option.\n";
        ::F1 = optionIn;
    }
    else if (optionIn == "2") {
        clearscr();
        cout << "You chose tutorial option.\n[Enter any input to go back to main menu.]\n";
        ::F1 = optionIn;
    }
    else if (optionIn == "q") {
        ::F1 = optionIn;
        cout << "\n> You have exited the program.\n";
    }
    else {
        clearscr();
        cout << "Error! Try again.\n\n";
        Welcome();
    }
}

void tutorial() {
    string menu;
    string instructions[] = { "\nIn Sudoku, the objective is to fill a 9 × 9 grid with digits so that each column, each row," , 
                              "\n(also called 'boxes', 'blocks', or 'regions') contain all of the digits from 1 to 9." , 
                              "\nOnce all the grid has been filled in correctly, you win the game.\n",
                              "\nHow to play Sudoku: ",
                              "\n1. Navigate through the grids through entering [W,A,S,D] keys into the screen.",
                              "\n2. Enter [I] to insert a value into the selected grid.",
                              "\n3. Enter a number into the selected grid.",
                              "\n4. Repeat step 1-3 until all grids are filled.\n\n",};

    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i];
    }
    cin >> menu;
    clearscr();
}


void puzzleValidation(char userMap[9][9]) {
    int gridCorrect = 0;

    //Traverse through all elements in an array
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            //Check if the element player inputted matches the sudoku element answer
            if (userMap[row][col] == ::puzzleEasyAns[row][col]) {
                gridCorrect++;
                continue;
            }
            else {
                cout << "\nWrong Answer! Please Try Again.\n";
                break;
            }
        };
    };

    //Display victory message if all elements matches sudoku array
    if (gridCorrect == 81) {
        cout << "\nYou Win the Sudoku!\n";
    }
}

void displayPuzzle(char userMap[9][9]) {
    string instructions[] = { "Move Up - [W]", "Move Left - [A]", "Move Down - [S]", "Move Right - [D]", "Insert Number - [I]"};
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << userMap[row][col] << " , ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i] << endl;
    }
    cout << endl;
}

void userControl(char userMap[9][9]) {
    while (true) {
        string userInput;
        string userInNum;

        extern int curRow, curCol;
        int preRow = curRow;
        int preCol = curCol;
        userMap[curRow][curCol] = 'X';
        displayPuzzle(puzzleEasy);
        cout << "You are currently at row: " << curRow << ", col : " << curCol << endl;
        cout << "Input : ";
        cin >> userInput;
        

        //Move Up
        if (userInput == "w") { 
            curRow--;
            if (curRow < 0)
                curRow = 8;
        }
        //Move Left
        else if (userInput == "a") {
            curCol--;
            if (curCol < 0)
                curCol = 8;
        }
        //Move Down
        else if (userInput == "s") {
            curRow++;
            if (curRow > 8)
            curRow = 0;
        }
        //Move Right
        else if (userInput == "d") {
            curCol++;
                curCol %= 9;
        }
        else if (userInput == "I") {
            cout << endl << "Please Insert a number: ";
            cin >> userInNum;
        }
        else {
            cout << "Error Input!";
        }
        clearscr();
        userMap[preRow][preCol] = ' - '; //clear
    };
}


/****************************************************************************/
////////                       Main Program                          /////////
/****************************************************************************/
int main()
{
    //Loop Jump Starts the Program
    while (true) {
        Welcome();

        if (F1 == "1") {
            while (true) {
                string difficultyInput;
                string diffmsg = "You have chosen ";
                string storeDifficulty[] = { "1. Easy", "2. Medium", "3. Hard" };

                cout << "Please select a difficulty.\n[Enter 'q' if you wish to go back to main menu.]\n";
                for (int i = 0; i < sizeof(storeDifficulty) / sizeof(string); i++) {
                    cout << "\n" << storeDifficulty[i];
                }
                cout << "\n\n";

                cin >> difficultyInput;
                clearscr();

                //Check Difficulty Selection
                if (difficultyInput == "1") {
                    cout << diffmsg << "\n" << storeDifficulty[0] << "\n\n";
                    puzzleValidation(puzzleEasyTest);
                }
                else if (difficultyInput == "2") {
                    int L1 = 1;
                    cout << diffmsg << "\n" << storeDifficulty[1] << "\n\n";
                    userControl(puzzleEasy);
                   

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

        //Tutorial on How to Play Sudoku
        if (F1 == "2") {
            tutorial();
        }

        //Quit Program
        if (F1 == "q") {
            return 0;
        }
    }
    //Loop End
}

//1. Explain Tutorial
//2. Display Puzzle - Key Inputs, Grace Mistake Indicators
//3. Player Movement
//4. Player Input Blank
//5. Option to confirm


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
