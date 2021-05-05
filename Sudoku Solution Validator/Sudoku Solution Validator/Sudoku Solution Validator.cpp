/** \file Sudoku Solution Validator.cpp
*   \brief A Sudoku Solution Validation application
*   \details A multithreaded application that determines whether the solution to a Sudoku puzzle is valid, with threads checking rows, columns and 3x3 subgrids
*   \author Michalis Papallis
*   \version 1.0
*   \date 04/05/2021
*   \copyright University of Nicosia
*/

#include <iostream>
#include <thread>

// Constants for total rows and columns
const int MAX_ROW = 9;
const int MAX_COL = 9;

// Constant 2D array for the Sudoku solution to be checked
const int sudoku[MAX_ROW][MAX_COL] = {  {6, 2, 4, 5, 3, 9, 1, 8, 7},
										{5, 1, 9, 7, 2, 8, 6, 3, 4},
										{8, 3, 7, 6, 1, 4, 2, 9, 5},
										{1, 4, 3, 8, 6, 5, 7, 2, 9},
										{9, 5, 8, 2, 4, 7, 3, 6, 1},
										{7, 6, 2, 3, 9, 1, 4, 5, 8},
										{3, 7, 1, 9, 5, 6, 8, 4, 2},
										{4, 9, 6, 1, 8, 2, 5, 7, 3},
										{2, 8, 5, 4, 7, 3, 9, 1, 6} };

// Function to check rows for validation
void rowCheck(int);
// Function to check columns for validation
void colCheck(int);
// Function to check 3x3 subgrids for validation
void subgridCheck(int, int);

/**
*  Function <code>main</code> is the main entry point of the application
*  <BR>
*  @return Returns 0 if it is completed successfully, otherwise it returns a non 0 integer value
*/
int main()
{
	return 0;
}

void rowCheck(int)
{
}

void colCheck(int)
{
}

void subgridCheck(int, int)
{
}
