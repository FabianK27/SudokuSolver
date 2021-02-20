#pragma once
#include<random>
#include<ctime>
#include"SudokuBoard.h"
#include<vector>

class SudokuSolver
{
private:
	static std::mt19937 mt;
	//internal variables
	static bool success;


	//internal methods
	static bool getMostConstrainedIndex(SudokuBoard& board, int& row, int& col, std::vector<int>& safeVals);

	static bool isSafe(SudokuBoard& board, int row, int col, int val);

	static bool isSafeVert(SudokuBoard& board, int row, int col, int val);
	
	static bool isSafeHor(SudokuBoard& board, int row, int col, int val);

	static bool isSafeBlock(SudokuBoard& board, int row, int col, int val);


public:
	static int getRandomInt(int min, int max);

	static bool solveSudokuDyn(SudokuBoard& board);
};


