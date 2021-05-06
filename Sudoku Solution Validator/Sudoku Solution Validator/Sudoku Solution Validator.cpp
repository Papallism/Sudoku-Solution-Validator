/** \file Sudoku Solution Validator.cpp
*   \brief A Sudoku Solution Validation application
*   \details A multithreaded application that determines whether the solution to a Sudoku puzzle is valid, with threads checking rows, columns and 3x3 sub-grids
*   \author Michalis Papallis - U184N0546
*   \version 1.0
*   \date 04/05/2021
*   \copyright University of Nicosia
*/

#include <iostream>
#include <cassert>
#include <thread>

// Constant for the desired number of threads to be created
const int TOTAL_THREADS = 27;

// Constants for total Sudoku rows and total Sudoku columns
const int MAX_ROW = 9;
const int MAX_COL = 9;

// Constant 2D array representing the Sudoku solution to be checked
// The current solution used is a valid solution
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
void rowCheck(int[], int, int);
// Function to check columns for validation
void colCheck(int[], int, int);
// Function to check 3x3 sub-grids for validation
void subgridCheck(int[], int, int, int);

/**
*	Function <code>main</code> is the main entry point of the application
*	<BR>
*	@return		Returns 0 if it is completed successfully, otherwise it returns a non 0 integer value
*/
int main()
{
	int threadIndex = 0;
	bool isValid = true;
	// Array declaration for storing the result of each thread, will store 0 for non-valid or 1 for valid region
	int threadResults[TOTAL_THREADS];
	// Array initialization of all positions to 1
	for (int i = 0; i < TOTAL_THREADS; i++)
	{
		threadResults[i] = 1;
	}

	// For-loop to create a thread for checking each row
	for (int i = 0; i < MAX_ROW; i++)
	{
		std::thread threadRow(rowCheck, threadResults, threadIndex, i);
		threadIndex++;
		threadRow.join();
	}
	// For-loop to create a thread for checking each column
	for (int i = 0; i < MAX_COL; i++)
	{
		std::thread threadColumn(colCheck, threadResults, threadIndex, i);
		threadIndex++;
		threadColumn.join();
	}
	// For-loop to create a thread for checking each 3x3 subgrid
	for (int i = 0; i < MAX_ROW; i += 3)
	{
		for (int j = 0; j < MAX_COL; j += 3)
		{
			std::thread threadSubgrid(subgridCheck, threadResults, threadIndex, i, j);
			threadIndex++;
			threadSubgrid.join();
		}
	}
	// For-loop to check if any position in the results array is 0, which means solution is not valid
	for (int i = 0; i < TOTAL_THREADS; i++)
	{
		if (threadResults[i] == 0)
		{
			isValid = false;
		}
	}
	(isValid ? std::cout << "\nThis Sudoku solution is valid!\n" : std::cout << "\nThis Sudoku solution is NOT valid!\n");

	return 0;
}

/**
*	Function <code>rowCheck</code> checks if a Sudoku row is valid
*	<BR>
*	@param results[]	The array to store the result of each thread
*	@param threadIndex	The index number of each thread corresponding to its array position
*	@param row			The row index to be checked
*/
void rowCheck(int results[], int threadIndex, int row)
{
	// Testing pre-conditions
	assert(threadIndex >= 0);
	assert(threadIndex < TOTAL_THREADS);
	assert(row >= 0);
	assert(row < MAX_ROW);

	// Array to hold the count of each number appearing in the row to be checked
	int numberCount[MAX_ROW] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// For-loop to count the times each number is appearing in the row to be checked
	for (int i = 0; i < MAX_COL; i++)
	{
		numberCount[sudoku[row][i] - 1]++;
	}

	// For-loop to check the count of each number appearing in the row, sets array element to 0 if they don't appear exactly one time
	for (int i = 0; i < MAX_COL; i++)
	{
		if (numberCount[i] != 1)
		{
			results[threadIndex] = 0;
		}
	}
}

/**
*	Function <code>colCheck</code> checks if a Sudoku column is valid
*	<BR>
*	@param results[]	The array to store the result of each thread
*	@param threadIndex	The index number of each thread corresponding to its array position
*	@param column		The column index to be checked
*/
void colCheck(int results[], int threadIndex, int column)
{
	// Testing pre-conditions
	assert(threadIndex >= 0);
	assert(threadIndex < TOTAL_THREADS);
	assert(column >= 0);
	assert(column < MAX_ROW);

	// Array to hold the count of each number appearing in the column to be checked
	int numberCount[MAX_ROW] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// For-loop to count the times each number is appearing in the column to be checked
	for (int i = 0; i < MAX_ROW; i++)
	{
		numberCount[sudoku[i][column] - 1]++;
	}

	// For-loop to check the count of each number appearing in the column, sets array element to 0 if they don't appear exactly one time
	for (int i = 0; i < MAX_ROW; i++)
	{
		if (numberCount[i] != 1)
		{
			results[threadIndex] = 0;
		}
	}
}

/**
*	Function <code>subgridCheck</code> checks if a Sudoku 3x3 subgrid is valid
*	<BR>
*	@param results[]	The array to store the result of each thread
*	@param threadIndex	The index number of each thread corresponding to its array position
*	@param row			The row index of the subgrid to be checked
*	@param column		The column index of the subgrid to be checked
*/
void subgridCheck(int results[], int threadIndex, int row, int column)
{
	// Testing pre-conditions
	assert(threadIndex >= 0);
	assert(threadIndex < TOTAL_THREADS);
	assert(row >= 0);
	assert(row <= MAX_ROW - 3);
	assert(column >= 0);
	assert(column <= MAX_COL - 3);

	// Array to hold the count of each number appearing in the subgrid to be checked
	int numberCount[MAX_ROW] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Nested for-loop to count how many times each number is appearing in the subgrid to be checked
	for (int i = row; i < row + 3; i++)
	{
		for (int j = column; j < column + 3; j++)
		{
			numberCount[sudoku[i][j] - 1]++;
		}
	}

	// For-loop to check the count of each number appearing in the subgrid, sets array element to 0 if they don't appear exactly one time
	for (int i = 0; i < MAX_ROW; i++)
	{
		if (numberCount[i] != 1)
		{
			results[threadIndex] = 0;
		}
	}
}
