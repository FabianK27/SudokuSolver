#include "SudokuSolver.h"

std::mt19937 SudokuSolver::mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

bool SudokuSolver::success{ false };

int SudokuSolver::getRandomInt(int min, int max)
{
	std::uniform_int_distribution<int>dist(min, max);
	return dist(mt);
}

bool SudokuSolver::isSafeBlock(SudokuBoard& board, int row, int col, int val) 
{
	//get starting row and col
	int row_start{ row - (row % gameConstants::BLOCK) };
	int col_start{ col - (col % gameConstants::BLOCK) };
	// loop over block
	for (int row{ row_start }; row < row_start + gameConstants::BLOCK; ++row)
	{
		for (int col{ col_start }; col < col_start + gameConstants::BLOCK; ++col)
		{
			if (board(row, col) == val)
				return false;
		}
	}
	return true;
}

bool SudokuSolver::getMostConstrainedIndex(SudokuBoard& board, int& row, int& col, std::vector<int>& safeVals)
{
	int currPos{ 0 };
	int maxPos{ 10 }; //set to a value that cant be reached to check if there is any empty index

	safeVals.clear();

	for (int loopRow{ 0 }; loopRow < gameConstants::GAME_DIM; ++loopRow)
	{
		for (int loopCol{ 0 }; loopCol < gameConstants::GAME_DIM; ++loopCol)
		{
			if (board(loopRow, loopCol) == 0)
			{
				currPos = 0;
				for (int val{ 1 }; val < 10; ++val)
				{
					if (isSafe(board, loopRow, loopCol, val))
						++currPos; // count how many possibilites unassigned spot has
				}
				if (currPos < maxPos)
				{
					maxPos = currPos;
					row = loopRow;
					col = loopCol;
				}
			}
		}
	}

	if (maxPos == 10) // arr == 0 never encountered
		return false;

	for (int val{ 1 }; val < 10; ++val) //actually fill in the possible values
	{
		if (isSafe(board, row, col, val))
			safeVals.push_back(val);
	}
	return true;
}

bool SudokuSolver::isSafe(SudokuBoard& board, int row, int col, int val) 
{
	return (isSafeVert(board, row, col, val) && isSafeHor(board, row, col, val) && isSafeBlock(board, row, col, val));
}

bool SudokuSolver::isSafeVert(SudokuBoard& board, int row, int col, int val) 
{
	for (int run{ 0 }; run < gameConstants::GAME_DIM; ++run)
	{
		if (board(run, col) == val)
			return false;
	}
	return true;
}

bool SudokuSolver::isSafeHor(SudokuBoard& board, int row, int col, int val) 
{
	for (int run{ 0 }; run < gameConstants::GAME_DIM; ++run)
	{
		if (board(row, run) == val)
			return false;
	}
	return true;
}

bool SudokuSolver::solveSudokuDyn(SudokuBoard& board)
{
	int m_col{ 0 };
	int m_row{ 0 };
	std::vector<int> safeVals{};
	//check if sudoku is solved, if so return true (1.st recursion break)
	if (!getMostConstrainedIndex(board, m_row, m_col, safeVals))
	{
		//printSudoku(); // print end result
		return true;
	}
	// loop over all safe values
	for (auto val : safeVals) //try safe numbers
	{
		board(m_row, m_col) = val; //insert current number attempt
		success = solveSudokuDyn(board); //recursively call function
		if (success)
		{
			return true;
		}

	}
	board(m_row, m_col) = 0; // undo inserts if no save value was found (is this necessary??)
	return false; //current path is false
}
