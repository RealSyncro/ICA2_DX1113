// ICA2_DX1113.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
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
int winPuzzle; int GraceCounter; int error;


/****************************************************************************/
////////                      Sudoku Puzzles                        //////////
/****************************************************************************/

//Answer Arrays

int puzzleInitEA1[9][9]{ {2,0,5,0,0,9,0,0,4},
                         {0,0,0,0,0,0,3,0,7},
                         {7,0,0,8,5,6,0,1,0},
                         {4,5,0,7,0,0,0,0,0},
                         {0,0,9,0,0,0,1,0,0},
                         {0,0,0,0,0,2,0,8,5},
                         {0,2,0,4,1,8,0,0,6},
                         {6,0,8,0,0,0,0,0,0},
                         {1,0,0,2,0,0,7,0,8} };

int puzzleInitEA2[9][9]{ {0,0,6,0,9,0,2,0,0},
                         {0,0,0,7,0,2,0,0,0},
                         {0,9,0,5,0,8,0,7,0},
                         {9,0,0,0,3,0,0,0,6},
                         {7,5,0,0,0,0,0,1,9},
                         {1,0,0,0,4,0,0,0,5},
                         {0,1,0,3,0,9,0,8,0},
                         {0,0,0,2,0,1,0,0,0},
                         {0,0,9,0,8,0,1,0,0} };

int puzzleInitEA3[9][9]{{0,0,0,8,0,0,0,0,0},
                        {7,8,9,0,1,0,0,0,6},
                        {0,0,0,0,0,6,1,0,0},
                        {0,0,7,0,0,0,0,5,0},
                        {5,0,8,7,0,9,3,0,4},
                        {0,4,0,0,0,0,2,0,0},
                        {0,0,3,2,0,0,0,0,0},
                        {8,0,0,0,7,0,4,3,9},
                        {0,0,0,0,0,1,0,0,0} };

//Copied Arrays
char userGrid[9][9];

int  solveIntPuzzle[9][9];
int  IntAnsGrid[9][9];
char CharAnsGrid[9][9];



/****************************************************************************/
/****************************************************************************/
////////                        Functions                           //////////
/****************************************************************************/
/****************************************************************************/
void copyIntArr(int unsolvedPuzzle[9][9], int PuzzleCopy[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            PuzzleCopy[row][col] = unsolvedPuzzle[row][col];
        }
    }
}

//Convert Int Grid to Char Grid
//Used for initialising and answer grid
void convertIntToCharGrid(const int IntGrid[9][9], char CharGrid[9][9]) {
        const int numCheck[10] = { 0,1,2,3,4,5,6,7,8,9 };
        const char convertNum[10] = { '-','1','2','3','4','5','6','7','8','9' };

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                for (int numIt = 0; numIt < 10; numIt++) {
                    if (IntGrid[r][c] == numCheck[numIt]) {
                        CharGrid[r][c] = convertNum[numIt];
                    }
                }
            }
        }
}

/****************************************************************************/
////////                    Decision Functions                      //////////
/****************************************************************************/
void clearscr() {
    cout << "\033[2J\033[1;1H";
}

//Upon Booting Up
void Welcome() {
    string In;
    string option[] = { "Welcome to Sudoku!\n", "[Enter 'q' to exit the program.]\n", "Please select an option.\n\n" , "1. Play Sudoku\n", "2. How to Play Sudoku\n" };
    for (int i = 0; i < sizeof(option) / sizeof(string); i++) {
        cout << option[i];
    }

    cout << endl;
    cin >> In;

    //Check User Selected Option
    if (In == "1") { //Play Sudoku
        clearscr();
        ::F1 = In;
    }
    else if (In == "2") { //How to Play Sudoku
        clearscr();
        cout << "[Enter any input to go back to main menu.]\n";
        ::F1 = In;
    }
    else if (In == "q") {//Exit Program
        ::F1 = In;
        cout << "\n> You have exited the program.\n";
    }
    else {
        clearscr();
        cout << "Error 1: Invalid User Input\n[Please enter in one of the available options.]\n\n";
        Welcome();
    }
}

//Tutorial Section
void tutorial() {
    string exit;
    string instructions[] = { "\nIn Sudoku, the objective is to fill a 9 � 9 grid with digits so that each column, each row," , 
                              "\n(also called 'boxes', 'blocks', or 'regions') contain all of the digits from 1 to 9." , 
                              "\nOnce all the grid has been filled in correctly, you win the game.\n",
                              "\nHow to play Sudoku: ",
                              "\n1. Navigate through the grids by entering [W,A,S,D] keys into the screen.",
                              "\n2. Enter [I] to insert a value into the selected grid.",
                              "\n3. Enter a number into the selected grid.",
                              "\n4. Repeat step 1-3 until all grids are filled.",
                              "\n5. Enter [C] to confirm your answers."
                              "\n6. Try not to make as much mistakes as possible! You have only 3 grace counts in total.\n\n" };
                               

    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i];
    }

    cin >> exit;
    clearscr();
}



/****************************************************************************/
////////                    Sub Puzzle Functions                    //////////
/****************************************************************************/
void resetPuzzleVar() {
    extern int curRow, curCol, winPuzzle, GraceCounter, error;
    curRow = 0; curCol = 0; winPuzzle = 0; GraceCounter = 3, error = 0;
}

void prtGrid(char Grid9x9[9][9]) {
    for (int row = 0; row < 9; row++) {
        if (row == 3 || row == 6) {
            cout << "---------------------" << endl;
        }
        for (int col = 0; col < 9; col++) {
            if (col == 2 || col == 5) {
                cout << Grid9x9[row][col] << " | ";
            }
            else {
                cout << Grid9x9[row][col] << " ";
            }

        }
        cout << endl;
    }
    cout << endl;
}

void errorDetection() {
    if (error == 1) {//User Answer does not match Puzzle Answer
        cout << "Wrong Answer! Please Try Again.\n\n";
        error = 0;
    }
    else if (error == 2) { //User Enters in invalid input during instruction
        cout << "Error 1: Invalid input! - Please enter in the available options.\n\n";
        error = 0;
    }
    else if (error == 3) { //User Enters in invalid character
        cout << "Error 2: Invalid character type! - Please enter in a valid integer.\n\n";
        error = 0;
    }
    else if (error == 4) { //Grid already occupied.
        cout << "Error 3: Grid is already occupied.\n\n";
        error = 0;
    }
}


/****************************************************************************/
////////                Auto Sudoku Solver Functions                     /////
/****************************************************************************/

//1. Keep Track of Numbers Used in Row, Column and Cell (Store 1-9)
//2. Loop through Rows and Cols (9 * 9) until it finds a non-0. 
//3. Prompt Algorithm which number is already used up. 
//4. Pass off the information to Main Recursive Sudoku Function
//5. Find a way to tell Algorithm that before curRow & curCol already solved and move forward
//6. Find a way to tell when a row & col is a blank. Else next row/col
//7. Check if num not used. Put Unused num on board and marked as used.
//8. Check if everything is solved. If not, reset. 
//9. If really cannot succeed, reset location and fail the function.
//10. Stop recursive function after solving all cells.

bool canPlace9x9(int puzzleInit[9][9], int row, int col, int n){
    //Returns false if curRow and curCol is filled.
    if (puzzleInit[row][col] != 0) return false;

    bool CanPlace = true;
    int gridx = (col / 3) * 3; 
    int gridy = (row / 3) * 3;

    //Check in its rows, cols, and cells if int number is used.
    for (int i = 0; i < 9; i++) {
        if (puzzleInit[row][i] == n) 
        { CanPlace = false; break; }
        if (puzzleInit[i][col] == n) 
        { CanPlace = false; break; }
        if (puzzleInit[gridy + i / 3][gridx + i % 3] == n) 
        { CanPlace = false; break; }
    }
    return CanPlace;
}

//Find next empty rol, col cell.
void nextEmptyCell(int puzzleInit[9][9], int row, int col, int& rowNext, int& colNext){

    int indexNext = 9 * 9 + 1;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
        if (puzzleInit[i / 9][i % 9] == 0) {

            indexNext = i;
            break;
        }
    }
    rowNext = indexNext / 9;
    colNext = indexNext % 9;
    //cout << row << "," << col << "|" << rowNext << "," << colNext << endl;
}

//Stores Integers that could be placed.
std::vector<int> findPlaceables(int puzzleInit[9][9], int row, int col) {
    std::vector<int> placebles = {};
    //Updates the set if integer is not used in its unique row, col & cell.
    for (int n = 1; n <= 9; n++)
        if (canPlace9x9(puzzleInit, row, col, n)) placebles.push_back(n);
    return placebles;
}

bool solveSudoku9x9(int puzzleInit[9][9], int row, int col)
{
    //system("cls");
    //printSudoku9x9(puzzleInit);

    if (row > 8) return true; //Stops the function after solving the last row.

    //Check if current row and col cell is filled up.
    if (puzzleInit[row][col] != 0) {
        int rowNext, colNext;
        nextEmptyCell(puzzleInit, row, col, rowNext, colNext); //Moves on to next empty cell
        return solveSudoku9x9(puzzleInit, rowNext, colNext); //Recurses the SolveSudoku function to find the correct number possibility.
    }

    //Get unused integers
    std::vector<int> placebles = findPlaceables(puzzleInit, row, col);

    //Immediately return false if there are no unused integers.
    if (placebles.size() == 0) {

        return false;

    };

    bool status = false;
    
    //Bruteforcing through num probability tree exploration
    for (int i = 0; i < placebles.size(); i++) {
        int n = placebles[i];
        int arrCpy[9][9];
        copyIntArr(puzzleInit, arrCpy);
        //cout << "(" << row << "," << col << ") =>" << n << endl;
        arrCpy[row][col] = n;
        int rowNext = row;
        int colNext = col;
        nextEmptyCell(arrCpy, row, col, rowNext, colNext);

        //If all the cells in its rows and col are unique, considered solved and returns true.
        if (solveSudoku9x9(arrCpy, rowNext, colNext)) {
            copyIntArr(arrCpy, puzzleInit);
            status = true;
            break;
        }
    }
    return status;
}



/****************************************************************************/
////////                    Main Puzzle Functions                    /////////
/****************************************************************************/
void displayPuzzle() {
    extern int winPuzzle, GraceCounter;
    prtGrid(::userGrid);
    errorDetection();
    string instructions[] = { "Move Up - [W]", "Move Left - [A]", "Move Down - [S]", "Move Right - [D]", "Insert Number - [I]", "Confirm Answer - [C]" };
    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i] << endl;
    }
    cout << "GraceCount: " << GraceCounter;
    cout << endl;
}

//Check User Answers for any errors
void puzzleValidation(char userConfirmAns[9][9], char puzzleAns[9][9]) {
    extern int winPuzzle; 
    int gridCorrect = 0;

    //Traverse through all elements in an array
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            //Check if the element player inputted matches the sudoku element answer
            if (userConfirmAns[row][col] == puzzleAns[row][col]) {
                gridCorrect++;
                continue;
            }
            else {
                break;
            }
        };
    };

    //Display victory message if all elements matches sudoku array
    if (gridCorrect == 9 * 9) {
        winPuzzle = 1; 
    }
}

void userControl(char Grid9x9[9][9], int InitialisePuzzle[9][9]) {
    extern int curRow, curCol, winPuzzle, GraceCounter, error;
    char userSudokuMap[9][9];

    convertIntToCharGrid(InitialisePuzzle, userSudokuMap);
    resetPuzzleVar();

    //Copies Puzzle Initial Array into New Empty Array
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Grid9x9[row][col] = userSudokuMap[row][col];
        }
    }


    //Find and solve sudoku answer in real time
    copyIntArr(InitialisePuzzle, solveIntPuzzle);
    solveSudoku9x9(solveIntPuzzle, 0, 0);
    copyIntArr(solveIntPuzzle, IntAnsGrid);
    convertIntToCharGrid(IntAnsGrid, CharAnsGrid);


    while (true) {
        string userInput; char userInNum;
        int preRow = curRow; int preCol = curCol;
        Grid9x9[curRow][curCol] = 'X';

        if (GraceCounter <= -1) {
            winPuzzle = -1;
            clearscr();
            cout << "You lost the Sudoku!\n";
            resetPuzzleVar();
            break;
        }

        displayPuzzle();

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
            while (true) {
                bool isValid = false;
                const char numCheck[9]{ '1','2','3','4','5','6','7','8','9'};
                for (int i = 0; i < 9; i++) { //Check if input is integer.
                    if (numCheck[i] == userInNum) {
                        isValid = true;
                    }
                }

                //If Input is Integer
                if (isValid) {
                    if (userSudokuMap[curRow][curCol] != '-') { //Check if grid is already occupied.
                        error = 4;
                        break;
                    }
                    else { 
                        userSudokuMap[curRow][curCol] = userInNum;
                        if (userSudokuMap[curRow][curCol] != CharAnsGrid[curRow][curCol]) { //Checks if User inputs wrong number.
                            userSudokuMap[curRow][curCol] = '-';
                            GraceCounter -= 1;
                            break;
                        }
                    }
                }
                //If Input is NOT integer
                else {
                    error = 3;
                    break;
                }
            }
        }

        //Confirm Answer
        else if (userInput == "c") {
            puzzleValidation(userSudokuMap, CharAnsGrid);
            if (winPuzzle == 1) {
                clearscr();
                cout << "You Win the Sudoku!\n";
                resetPuzzleVar();
                break;
            }
            else {
                error = 1;
            }
        }
        else {
            error = 2;
        }
        clearscr();
        Grid9x9[preRow][preCol] = userSudokuMap[preRow][preCol];
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
                string diffSelect;
                string msg = "You have chosen ";
                string Difficulty[] = { "1. Easy", "2. Medium", "3. Hard" };

                cout << "Please select a difficulty.\n[Enter 'q' if you wish to go back to main menu.]\n";
                for (int i = 0; i < sizeof(Difficulty) / sizeof(string); i++) {
                    cout << "\n" << Difficulty[i];
                }
                cout << "\n\n";

                cin >> diffSelect;
                clearscr();

                //Check Difficulty Selection
                if (diffSelect == "1") {
                    cout << msg << "\n" << Difficulty[0] << "\n\n";
                    userControl(userGrid, puzzleInitEA1);
                }
                else if (diffSelect == "2") {
                    cout << msg << "\n" << Difficulty[1] << "\n\n";
                    userControl(userGrid, puzzleInitEA2);
                }
                else if (diffSelect == "3") {
                    cout << msg << "\n" << Difficulty[2] << "\n\n";
                    userControl(userGrid, puzzleInitEA3);
                }
                else if (diffSelect == "q") {
                    cout << "Exit Loop";
                    clearscr();
                    break;
                }
                else {
                    cout << "Error 1: Invalid User Input\n[Please enter in one of the available options.]\n\n";
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

//1. Organise and Clean Junk Code
//5. Add hints feature [Up to 3 tries] 




