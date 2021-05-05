/** \file Sudoku Solution Validator.cpp
*   \brief A Sudoku Solution Validation application
*   \details A multithreaded application that determines whether the solution to a Sudoku puzzle is valid, with threads checking rows, columns and 3x3 subgrids
*   \author Michalis Papallis
*   \version 1.0
*   \date 04/05/2021
*   \copyright University of Nicosia
*/

#include <iostream>
#include <cassert>
#include <thread>

// Constants for total rows and total columns
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
*	Function <code>main</code> is the main entry point of the application
*	<BR>
*	@return		Returns 0 if it is completed successfully, otherwise it returns a non 0 integer value
*/
int main()
{
	std::thread t1(subgridCheck, 0, 0);
	t1.join();
	return 0;
}

/**
*	Function <code>rowCheck</code> checks if a Sudoku row is valid
*	<BR>
*	@param row		The row index to be checked
*	@return			Returns <code>true</code> if the row is valid
*/
void rowCheck(int row)
{
	// Testing pre-conditions
	assert(row >= 0);
	assert(row < MAX_ROW);

	// Array to hold the count of each number appearing in the row to be checked
	int numberCount[MAX_ROW] = {0, 0, 0, 0, 0, 0, 0 ,0, 0};

	// For-loop to get the count of each number appearing in the row to be checked
	for (int i = 0; i < MAX_COL; i++)
	{
		numberCount[sudoku[row][i] - 1]++;
	}
}

/**
*	Function <code>colCheck</code> checks if a Sudoku column is valid
*	<BR>
*	@param column	The column index to be checked
*	@return			Returns <code>true</code> if the column is valid
*/
void colCheck(int column)
{
	// Testing pre-conditions
	assert(column >= 0);
	assert(column < MAX_COL);

	// Array to hold the count of each number appearing in the column to be checked
	int numberCount[MAX_ROW] = { 0, 0, 0, 0, 0, 0, 0 ,0, 0 };

	// For-loop to get the count of each number appearing in the column to be checked
	for (int i = 0; i < MAX_COL; i++)
	{
		numberCount[sudoku[i][column] - 1]++;
	}
}

/**
*	Function <code>subgridCheck</code> checks if a Sudoku 3x3 subgrid is valid
*	<BR>
*	@param row		The row index of the subgrid to be checked
*	@param column	The column index of the subgrid to be checked
*	@return			Returns <code>true</code> if the subgrid is valid
*/
void subgridCheck(int row, int column)
{
	// Testing pre-conditions
	assert(row >= 0);
	assert(row < MAX_ROW);
	assert(column >= 0);
	assert(column < MAX_COL);

	// Array to hold the count of each number appearing in the subgrid to be checked
	int numberCount[MAX_ROW] = { 0, 0, 0, 0, 0, 0, 0 ,0, 0 };

	// For-loop to get the count of each number appearing in the subgrid to be checked
	for (int i = row; i < row + 3; i++)
	{
		for (int j = column; j < column + 3; j++)
		{
			numberCount[sudoku[i][j] - 1]++;
		}
	}
}
