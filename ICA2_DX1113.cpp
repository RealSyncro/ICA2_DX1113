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
int winPuzzle; int GraceCounter; int errorConfirmation;


/****************************************************************************/
////////                      Sudoku Puzzles                        //////////
/****************************************************************************/

//Answer Arrays
const char puzzleEA1[9][9]{ {'2','1','5','3','7','9','8','6','4'},
                            {'9','8','6','1','2','4','3','5','7'},
                            {'7','3','4','8','5','6','2','1','9'},
                            {'4','5','2','7','8','1','6','9','3'},
                            {'8','6','9','5','4','3','1','7','2'},
                            {'3','7','1','6','9','2','4','8','5'},
                            {'5','2','7','4','1','8','9','3','6'},
                            {'6','4','8','9','3','7','5','2','1'},
                            {'1','9','3','2','6','5','7','4','8'} };

const char puzzleEA2[9][9]{ {'8','7','6','4','9','3','2','5','1'},
                            {'3','4','5','7','1','2','9','6','8'},
                            {'2','9','1','5','6','8','4','7','3'},
                            {'9','8','2','1','3','5','7','4','6'},
                            {'7','5','4','8','2','6','3','1','9'},
                            {'1','6','3','9','4','7','8','2','5'},
                            {'4','1','7','3','5','9','6','8','2'},
                            {'6','3','8','2','7','1','5','9','4'},
                            {'5','2','9','6','8','4','1','3','7'} };

const char puzzleEA3[9][9]{ {'1','6','5','8','4','7','9','2','3'},
                            {'7','8','9','3','1','2','5','4','6'},
                            {'4','3','2','5','9','6','1','7','8'},
                            {'2','9','7','4','6','3','8','5','1'},
                            {'5','1','8','7','2','9','3','6','4'},
                            {'3','4','6','1','5','8','2','9','7'},
                            {'9','7','3','2','8','4','6','1','5'},
                            {'8','2','1','6','7','5','4','3','9'},
                            {'6','5','4','9','3','1','7','8','2'} };

//Initialise Arrays
const char userAnsNo1init[9][9]{ {'2','-','5','3','7','9','8','6','4'},
                                 {'9','8','6','1','2','4','3','5','7'},
                                 {'7','3','4','8','5','6','2','1','9'},
                                 {'4','5','2','7','8','1','6','9','3'},
                                 {'8','6','9','5','4','3','1','7','2'},
                                 {'3','7','1','6','9','2','4','8','5'},
                                 {'5','2','7','4','1','8','9','3','6'},
                                 {'6','4','8','9','3','7','5','2','1'},
                                 {'1','9','3','2','6','5','7','4','8'} };

const char userAnsNo2init[9][9]{ {'-','-','6','-','9','-','2','-','-'},
                                 {'-','-','-','7','-','2','-','-','-'},
                                 {'-','9','-','5','-','8','-','7','-'},
                                 {'9','-','-','-','3','-','-','-','6'},
                                 {'7','5','-','-','-','-','-','1','9'},
                                 {'1','-','-','-','4','-','-','-','5'},
                                 {'-','1','-','3','-','9','-','8','-'},
                                 {'-','-','-','2','-','1','-','-','-'},
                                 {'-','-','9','-','8','-','1','-','-'} };

//const char userAnsNo2init[9][9]{ {'8','7','-','4','9','3','2','5','1'},
//                                 {'3','-','5','7','1','2','9','6','8'},
//                                 {'2','9','1','5','6','8','4','7','3'},
//                                 {'9','8','2','1','3','5','7','4','6'},
//                                 {'7','5','4','8','2','6','3','1','9'},
//                                 {'1','6','3','9','4','7','8','2','5'},
//                                 {'4','1','7','3','5','9','6','8','2'},
//                                 {'6','3','8','2','7','1','5','9','4'},
//                                 {'5','2','9','6','8','4','1','3','7'} };



const char userAnsNo3init[9][9]{ {'-','6','5','8','4','7','9','2','3'},
                                 {'7','8','9','3','1','-','5','4','6'},
                                 {'4','-','2','5','9','6','1','7','8'},
                                 {'2','9','7','4','6','3','8','5','1'},
                                 {'5','1','8','7','2','9','3','6','4'},
                                 {'3','4','6','1','5','8','2','9','7'},
                                 {'9','7','3','2','8','4','6','1','5'},
                                 {'8','2','1','6','7','5','4','3','9'},
                                 {'6','5','4','9','3','1','7','8','2'} };

//const char userAnsNo1init[9][9]{ {'2','-','5','-','-','9','-','-','4'},
//                                 {'-','-','-','-','-','-','3','-','7'},
//                                 {'7','-','-','8','5','6','-','1','-'},
//                                 {'4','5','-','7','-','-','-','-','-'},
//                                 {'-','-','9','-','-','-','1','-','-'},
//                                 {'-','-','-','-','-','2','-','8','5'},
//                                 {'-','2','-','4','1','8','-','-','6'},
//                                 {'6','-','8','-','-','-','-','-','-'},
//                                 {'1','-','-','2','-','-','7','-','8'} };





//const char userAnsNo3init[9][9]{ {'-','-','-','8','-','-','-','-','-'},
//                                 {'7','8','9','-','1','-','-','-','6'},
//                                 {'-','-','-','-','-','6','1','-','-'},
//                                 {'-','-','7','-','-','-','-','5','-'},
//                                 {'5','-','8','7','-','9','3','-','4'},
//                                 {'-','4','-','-','-','-','2','-','-'},
//                                 {'-','-','3','2','-','-','-','-','-'},
//                                 {'8','-','-','-','7','-','4','3','9'},
//                                 {'-','-','-','-','-','1','-','-','-'} };

char userGrid[9][9];




/****************************************************************************/
/****************************************************************************/
////////                        Functions                           //////////
/****************************************************************************/
/****************************************************************************/

//Print Functions 

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

    cin >> exit;
    clearscr();
}



/****************************************************************************/
////////                    Puzzle Functions                        //////////
/****************************************************************************/
void resetPuzzleVar() {
    extern int curRow, curCol, winPuzzle, GraceCounter, errorConfirmation;
    curRow = 0; curCol = 0; winPuzzle = 0; GraceCounter = 3, errorConfirmation = 0;
}

//Show User Predetermined Map
void displayPuzzle(char userMap[9][9]) {
    extern int winPuzzle, GraceCounter;
    string instructions[] = { "Move Up - [W]", "Move Left - [A]", "Move Down - [S]", "Move Right - [D]", "Insert Number - [I]", "Confirm Answer - [C]"};
    for (int row = 0; row < 9; row++) {
        if (row == 3 || row == 6) {
            cout << "---------------------" << endl;
        }
        for (int col = 0; col < 9; col++) {
            if (col == 2 || col == 5){ 
                cout << userMap[row][col] << " | "; 
            }
            else { 
                cout << userMap[row][col] << " "; 
            }
            
        }
        cout << endl;
    }
    cout << endl;
    
    //Error Types
    if (errorConfirmation == 1) {//User Answer does not match Puzzle Answer
        cout << "Wrong Answer! Please Try Again.\n\n";
        errorConfirmation = 0;
    }
    else if (errorConfirmation == 2) { //User Enters in invalid input during instruction
        cout << "Error 1: Invalid input! - Please enter in the available options.\n\n";
        errorConfirmation = 0;
    }
    else if (errorConfirmation == 3) { //User Enters in invalid character
        cout << "Error 2: Invalid character type! - Please enter in a valid integer.\n\n";
        errorConfirmation = 0;
    }
    else if (errorConfirmation == 4) { //Grid already occupied.
        cout << "Error 3: Grid is already occupied.\n\n";
        errorConfirmation = 0;
    }


    for (int i = 0; i < sizeof(instructions) / sizeof(string); i++) {
        cout << instructions[i] << endl;
    }
    cout << "GraceCount: " << GraceCounter;
    cout << endl;
}

//Check User Answers for any errors
void puzzleValidation(char userConfirmAns[9][9], const char puzzleAns[9][9]) {
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
    if (gridCorrect == 81) {
        winPuzzle = 1; 
    }
}

void sudokuAutoSolver(char userConfirmAns[9][9]) {
    extern int winPuzzle; 
    
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {

        }
    }

    //Auto Solve Initial Sudoku Puzzle 
    //Copy answer to Global Array
    //Use it to check against user answer
    
    //Check for unique numbers in 3x3 grid
    //Map[0][0] Map [1][0] Map[2][0]
    //Map[0][1] Map [1][1] Map[2][1]
    //Map[0][2] Map [1][2] Map[2][2]

    //Replicate Unique Test Across 9 3x3 grids;

    //If fail, trip error. Else, Win game. 

}

void userControl(char userDisplay[9][9], const char puzzleInit[9][9], const char puzzleAns[9][9]) {
    extern int curRow, curCol, winPuzzle, GraceCounter, errorConfirmation;
    char userSudokuMap[9][9];
    resetPuzzleVar();

    //Copies Puzzle Initial Array into New Empty Array
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            userSudokuMap[row][col] = puzzleInit[row][col];
            userDisplay[row][col] = userSudokuMap[row][col];
        }
    }

    while (true) {
        string userInput; char userInNum;
        int preRow = curRow; int preCol = curCol;
        userDisplay[curRow][curCol] = 'X';

        if (GraceCounter <= -1) {
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
                        errorConfirmation = 4;
                        break;
                    }
                    else { 
                        userSudokuMap[curRow][curCol] = userInNum;
                        if (userSudokuMap[curRow][curCol] != puzzleAns[curRow][curCol]) { //Checks if User inputs wrong number.
                            userSudokuMap[curRow][curCol] = '-';
                            GraceCounter -= 1;
                            break;
                        }
                    }
                }
                //If Input is NOT integer
                else {
                    errorConfirmation = 3;
                    break;
                }
            }
        }

        //Confirm Answer
        else if (userInput == "c") {
            puzzleValidation(userSudokuMap, puzzleAns);
            if (winPuzzle == 1) {
                clearscr();
                cout << "You Win the Sudoku!\n";
                resetPuzzleVar();
                break;
            }
            else {
                errorConfirmation = 1;
            }
        }
        else {
            errorConfirmation = 2;
        }
        clearscr();
        userDisplay[preRow][preCol] = userSudokuMap[preRow][preCol];
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
                    userControl(userGrid, ::userAnsNo1init, puzzleEA1);
                }
                else if (diffSelect == "2") {
                    cout << msg << "\n" << Difficulty[1] << "\n\n";
                    userControl(userGrid, ::userAnsNo2init, puzzleEA2);
                }
                else if (diffSelect == "3") {
                    cout << msg << "\n" << Difficulty[2] << "\n\n";
                    userControl(userGrid, ::userAnsNo3init, puzzleEA3);
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
//4.1.Use pointers to create new array. [idk if possible?]
//4.2.Find a way to revert array to normal. [idk if possible?]
//5. Add hints feature [Up to 3 tries] 

//BONUS
//1. Randomise Sudoku Puzzle
//2. Randomise Sudoku Predetermined Grids
//3. Servers?
//4. More gamemodes ??

//DONE TASKS
//2. Fix Error Message if wrong answer [DONE]
//3. Fix Error Message if invalid input [DONE]
//4. Implement Reset feature after winning [DONE]
//6. Add mistake grace counter[Up to 5 mistakes]. [DONE]
//6.1 Add instant game over if MGC > 5. [DONE]
//7. Add more puzzles. [DONE]

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

