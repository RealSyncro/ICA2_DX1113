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
int curRow = 0;  int curCol = 0;

//Win Condition Variable
int winPuzzle; int GraceCount; int wrongConfirmation;


/****************************************************************************/
////////                      Sudoku Puzzles                        //////////
/****************************************************************************/
const char puzzleEA1[9][9]{ {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'},
                            {'1','2','3','4','5','6','7','8','9'} };

char userGrid[9][9];

char userAnsNoX[9][9]{ {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','9'},
                       {'1','2','3','4','5','6','7','8','8'} };




/****************************************************************************/
/****************************************************************************/
////////                        Functions                           //////////
/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
////////                    Decision Functions                      //////////
/****************************************************************************/
void clearscr() {
    cout << "\033[2J\033[1;1H";
}

//Upon Booting Up
void Welcome() {
    string * In; In = new string;
    string option[] = { "Welcome to Sudoku!\n", "[Enter 'q' to exit the program.]\n", "Please select an option.\n\n" , "1. Play Sudoku\n", "2. How to Play Sudoku\n" };
    for (int i = 0; i < sizeof(option) / sizeof(string); i++) {
        cout << option[i];
    }

    cout << endl;
    cin >> *In;

    //Check User Selected Option
    if (*In == "1") { //Play Sudoku
        clearscr();
        ::F1 = *In;
    }
    else if (*In == "2") { //How to Play Sudoku
        clearscr();
        cout << "[Enter any input to go back to main menu.]\n";
        ::F1 = *In;
    }
    else if (*In == "q") {//Exit Program
        ::F1 = *In;
        cout << "\n> You have exited the program.\n";
    }
    else {
        clearscr();
        cout << "Error 1: Invalid User Input\n[Please enter in one of the available options.]\n\n";
        Welcome();
    }
    delete In;
}

//Tutorial Section
void tutorial() {
    string * exit; exit = new string;
    string instructions[] = { "\nIn Sudoku, the objective is to fill a 9 × 9 grid with digits so that each column, each row," , 
                              "\n(also called 'boxes', 'blocks', or 'regions') contain all of the digits from 1 to 9." , 
                              "\nOnce all the grid has been filled in correctly, you win the game.\n",
                              "\nHow to play Sudoku: ",
                              "\n1. Navigate through the grids by entering [W,A,S,D] keys into the screen.",
                              "\n2. Enter [I] to insert a value into the selected grid.",
                              "\n3. Enter a number into the selected grid.",
                              "\n4. Repeat step 1-3 until all grids are filled.\n\n",};

    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i];
    }
    cin >> *exit;
    clearscr();
    delete exit;
}



/****************************************************************************/
////////                    Puzzle Functions                        //////////
/****************************************************************************/
void resetPuzzleVar() {
    extern int curRow, curCol, winPuzzle, GraceCount, wrongConfirmation;
    curRow = 0; curCol = 0; winPuzzle = 0; GraceCount = 3, wrongConfirmation;
}

//Show User Predetermined Map
void displayPuzzle(char userMap[9][9]) {
    extern int winPuzzle, GraceCount;
    string instructions[] = { "Move Up - [W]", "Move Left - [A]", "Move Down - [S]", "Move Right - [D]", "Insert Number - [I]", "Confirm Answer - [C]"};
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << userMap[row][col] << " , ";
        }
        cout << endl;
    }
    cout << endl;
    
    if (wrongConfirmation == 1) {
        cout << "Wrong Answer! Please Try Again.\n\n";
        wrongConfirmation = 0;
    }

    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i] << endl;
    }
    cout << "GraceCount: " << GraceCount;
    cout << endl;
}

//Check User Answers for any errors
void puzzleValidation(char userMap[9][9], const char puzzleAns[9][9]) {
    extern int winPuzzle; 
    int gridCorrect = 0;

    //Traverse through all elements in an array
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            //Check if the element player inputted matches the sudoku element answer
            if (userMap[row][col] == puzzleAns[row][col]) {
                gridCorrect++;
                continue;
            }
            else {
                break;
            }
        };
    };

    //Display victory message if all elements matches sudoku array
    if (gridCorrect == 81) {
        winPuzzle = 1; 
    }
}

void userControl(char userMap[9][9], char userAns[9][9], const char puzzleAns[9][9]) {
    extern int curRow, curCol, winPuzzle, GraceCount, wrongConfirmation;
    resetPuzzleVar();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            userMap[row][col] = userAns[row][col];
        }
    }

    while (true) {
        string userInput; char userInNum;
        int preRow = curRow; int preCol = curCol;
        userMap[curRow][curCol] = 'X';

        if (GraceCount == 0) {
            winPuzzle = -1;
            clearscr();
            cout << "You lost the Sudoku!\n";
            resetPuzzleVar();
            break;
        }

        displayPuzzle(userGrid);
        cout << "You are currently at row: " << curRow << ", col : " << curCol << endl << "Input : ";
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
        //Insert Number into Grid
        else if (userInput == "i") {
            cout << endl << "Please Insert a number: ";
            cin >> userInNum;
            userAns[curRow][curCol] = userInNum;
            if (userAns[curRow][curCol] != puzzleAns[curRow][curCol]) {
                GraceCount -= 1;
            }
        }
        //Confirm Answer
        else if (userInput == "c") {
            puzzleValidation(userAnsNoX, ::puzzleEA1);
            if (winPuzzle == 1) {
                clearscr();
                cout << "You Win the Sudoku!\n";
                resetPuzzleVar();
                break;
            }
            else {
                wrongConfirmation = 1;
            }
        }
        else {
            cout << "Error Input!";
        }
        clearscr();
        userMap[preRow][preCol] = userAns[preRow][preCol]; 
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
                string* diffSelect; diffSelect = new string;
                string msg = "You have chosen ";
                string Difficulty[] = { "1. Easy", "2. Medium", "3. Hard" };

                cout << "Please select a difficulty.\n[Enter 'q' if you wish to go back to main menu.]\n";
                for (int i = 0; i < sizeof(Difficulty) / sizeof(string); i++) {
                    cout << "\n" << Difficulty[i];
                }
                cout << "\n\n";

                cin >> *diffSelect;
                clearscr();

                //Check Difficulty Selection
                if (*diffSelect == "1") {
                    cout << msg << "\n" << Difficulty[0] << "\n\n";
                    userControl(userGrid, ::userAnsNoX, puzzleEA1);
                }
                else if (*diffSelect == "2") {
                    cout << msg << "\n" << Difficulty[1] << "\n\n";
                }
                else if (*diffSelect == "3") {
                    cout << msg << "\n" << Difficulty[2] << "\n\n";
                }
                else if (*diffSelect == "q") {
                    cout << "Exit Loop";
                    clearscr();
                    break;
                }
                else {
                    cout << "Error 1: Invalid User Input\n[Please enter in one of the available options.]\n\n";
                }
                delete diffSelect;
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

//1. Organise and Clean Junk Code
//2. Fix Error Message if wrong answer
//3. Fix Error Message if invalid input
//4. Implement Reset feature after winning
//4.1.Use pointers to create new array.
//4.2.Find a way to revert array to normal.
//5. Add hints feature[Up to 3 tries]
//6. Add mistake grace counter[Up to 5 mistakes].
//6.1 Add instant game over if MGC > 5.
//7. Add more puzzles.


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
