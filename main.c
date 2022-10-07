/**
 * Author: Wei-Hsiang Chang
 * Date: June 7 2022
 * Description:
 * Implement the logic of validate the Sudoku according to the rule, prompt user to
 * input the correct values, and validate the solution of Sudoku.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define GRIDCOL 9
void validateRowLength(int row, int custGrid[][GRIDCOL]);
void validateRowDuplicateOrOutRange(int row, int custGrid[][GRIDCOL]);
void printSudoku(int gridcol, int custGrid[][GRIDCOL] );
void printRestRandomRow(int custGrid[][GRIDCOL]);
int validateSudoku(int grid[][GRIDCOL]);
int main() {
    int custGrid[][GRIDCOL]={0};
    int testGrid[ ][ GRIDCOL ] = {{5,3,4,6,7,8,9,1,2}, {6,7,2,1,9,5,3,4,8},{1,9,8,3,4,2,5,6,7},
                            {8,5,9,7,6,1,4,2,3},{4,2,6,8,5,3,7,9,1},{7,1,3,9,2,4,8,5,6},
                            {9,6,1,5,3,7,2,8,4},{2,8,7,4,1,9,6,3,5},{3,4,5,2,8,6,1,7,9}};
    printSudoku(GRIDCOL, testGrid);
    switch(validateSudoku(testGrid)) {
        case 0:
            puts("Given Sudoku grid is invalid\n");
            break;
        case 1:
            puts("Given Sudoku grid is valid\n");
            break;
    }
    puts("Enter row 1 of the Sudoku grid.\nUse Space/tab key to enter the next values,\nand press 'Return' after entering distinct nine integers from 1 -9\n");
    validateRowLength(0, custGrid);
    validateRowDuplicateOrOutRange(0, custGrid);
    puts("Enter row 2 of the Sudoku grid.\nUse Space/tab key to enter the next values,\nand press 'Return' after entering distinct nine integers from 1 -9\n");
    validateRowLength(1, custGrid);
    validateRowDuplicateOrOutRange(1, custGrid);
    srand(time(NULL));
    printRestRandomRow(custGrid);
    printSudoku(GRIDCOL, custGrid);
    switch(validateSudoku(custGrid)) {
        case 0:
            puts("Given Sudoku grid  is invalid");
            break;
        case 1:
            puts("Given Sudoku grid  is valid");
            break;
    }
    return 0;
}

/*
 * Given the row number of the 2D arrays and prompts user if not exactly 9 integers input
 * */
void validateRowLength(int row, int custGrid[][GRIDCOL]) {
    char buffer[SIZE];
    int countRows = 0;
    fgets(buffer, sizeof(buffer), stdin);
    countRows = sscanf(buffer, "%d%d%d%d%d%d%d%d%d", &custGrid[row][0], &custGrid[row][1], &custGrid[row][2], &custGrid[row][3], &custGrid[row][4], &custGrid[row][5], &custGrid[row][6], &custGrid[row][7], &custGrid[row][8]);
    while(countRows != 9) { // keeps prompting user if not exactly 9 integers
        puts("Please enter exactly 9 integers, seperated by Space/tab key,\nand press 'Return' after entering distinct nine integers from 1 -9\n");
        fgets(buffer, sizeof(buffer), stdin);
        countRows = sscanf(buffer, "%d%d%d%d%d%d%d%d%d", &custGrid[row][0], &custGrid[row][1], &custGrid[row][2], &custGrid[row][3], &custGrid[row][4], &custGrid[row][5], &custGrid[row][6], &custGrid[row][7], &custGrid[row][8]);
    }
}

/*
 * Given the row number of the 2D arrays and prompts user if the input has integers duplicated or out of range
 * */
void validateRowDuplicateOrOutRange(int row, int custGrid[][GRIDCOL]){
    int isDuplicated = 1;
    int isOutRange = 1;

    while(isDuplicated || isOutRange){
        for(int i=0; i<GRIDCOL-1; i++){
            for(int j=i+1; j<GRIDCOL; j++){
                if(custGrid[row][i] == custGrid[row][j]){ // check the 2D array if the row has duplicated value
                    isDuplicated = 1;
                    puts("Please enter 9 distinct integers, no duplicated! seperated by Space/tab key,\nand press 'Return' after entering distinct nine integers from 1 -9\n");
                    validateRowLength(row, custGrid);
                    i = j = GRIDCOL;
                    break;
                }
                else if( custGrid[row][i]<1 || custGrid[row][i]>9 || custGrid[row][j]<1 || custGrid[row][j]>9){ //check the 2D array if the row has value out of 1- 9
                    isOutRange = 1;
                    puts("One or more entries are out of 1-9.\nUse Space/tab key to enter the next values,\nand press 'Return' after entering distinct nine integers from 1 -9\n");
                    validateRowLength(row, custGrid);
                    i = j = GRIDCOL;
                    break;
                }
                else{
                    isOutRange = 0;
                    isDuplicated = 0;
                }
            }
        }
    }
}

/*
 * Given the 2D array and displays the Sudoku
 * */
void printSudoku(int gridcol, int custGrid[][GRIDCOL] ){
    puts("---- Sudoku Grid ----");
    for (int i=0; i<gridcol; i++){
        for (int j=0; j<gridcol; j++){
            printf("%d ",custGrid[i][j]);
        }
        puts("");
    }
}

/*
 * Given the 2D array and generate the random values for the rest of the rows
 * */
void printRestRandomRow(int custGrid[][GRIDCOL]){
    for (int i=2; i<GRIDCOL; i++){
        int range = 9;
        int offset = 0;
        int Num[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j=0; j<GRIDCOL; j++){
            int temp;
            int randNum;
            temp = Num[j];
            randNum = (int)(rand() % range) + offset; //generate random number to swap
            Num[j] = Num[randNum]; //change the order
            Num[randNum] = temp; //swap
            custGrid[i][j] = Num[j];
            range--;//reduce the range
            offset++;//increase the offset
        }
    }
}

/*
 * Given the 2D array and returns 0 if the Sudoku is invalid, returns 1 if the Sudoku is valid
 * */
int validateSudoku(int grid[][GRIDCOL]) {
    int isValid = 1;
    for(int row = 0; row < GRIDCOL; row++) {
        for (int i = 0; i < GRIDCOL - 1; i++) {
            for (int j = i + 1; j < GRIDCOL; j++) {
                if (grid[row][i] == grid[row][j]) { //check every row if there is duplicated value
                    row = i = j = GRIDCOL;
                    isValid = 0;
                    break;
                }
            }
        }
    }
    for(int row = 0; row < GRIDCOL; row++) {
        for (int i = 0; i < GRIDCOL - 1; i++) {
            for (int j = i + 1; j < GRIDCOL; j++) {
                if (grid[i][row] == grid[j][row]) { //check every column if there is duplicated value
                    row = i = j = GRIDCOL;
                    isValid = 0;
                    break;
                }
                //printf("%d",grid[i][row]);
            }
        }
    }
    for(int unit = 0; unit < GRIDCOL; unit++) {
        for (int i = 0; i < GRIDCOL - 1; i++) {
            for (int j = i + 1; j < GRIDCOL; j++){
                int unitColOffset = (unit%3)*3; //increase offset from left to right columns
                int unitRowOffset = (unit/3)*3; //increase offset from top to bottom rows
                if (grid[i/3 + unitRowOffset][i%3 + unitColOffset] == grid[j/3 + unitRowOffset][j%3 + unitColOffset]){ //check 3X3 units if there is duplicated value
                    unit = i = j = GRIDCOL;
                    isValid = 0;
                    break;
                }
                //printf("%d",grid[j/3 + unitRowOffset][j%3 + unitColOffset]);
            }
        }
    }

    return isValid;
}
