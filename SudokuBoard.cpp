#include "SudokuBoard.h"

SudokuBoard::SudokuBoard(float tileDim, sf::Vector2f startPos)
{
	//allocate dynamic memorey for board
	m_board = new SudokuTile* [gameConstants::GAME_DIM];
	for (int i{ 0 }; i < gameConstants::GAME_DIM; ++i)
	{
		m_board[i] = new SudokuTile[gameConstants::GAME_DIM];
	}

	// and similar for int array
	m_value_arr = new int* [gameConstants::GAME_DIM];
	for (int i{ 0 }; i < gameConstants::GAME_DIM; ++i)
	{
		m_value_arr[i] = new int[gameConstants::GAME_DIM]{};
	}

	//initialize the board by setting positions
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setSize(tileDim);
			m_board[ii][jj].setPosition({ startPos.x + jj * tileDim, startPos.y + ii * tileDim });

		}
	}

}

SudokuBoard::~SudokuBoard()
{
	for (int i{ 0 }; i < gameConstants::GAME_DIM; ++i)
	{
		delete[] m_board[i];
		delete[] m_value_arr[i];
	}
	delete[] m_board;
	delete[] m_value_arr;
}

void SudokuBoard::drawBoard(sf::RenderWindow& window) const
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].drawTile(window);
		}
	}
}

void SudokuBoard::setFont(const sf::Font& font)
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setFont(font);
		}
	}
			
}

void SudokuBoard::randomFillBoard()
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setValue(SudokuSolver::getRandomInt(0, 9));
		}
	}
}

bool SudokuBoard::posInside(sf::Vector2i pos) const
{
	//get "bounding box" for entire board
	float bLeft{ m_board[0][0].getGlobalBounds().left };
	float bTop{ m_board[0][0].getGlobalBounds().top };
	float bRight{ m_board[0][gameConstants::GAME_DIM - 1].getGlobalBounds().left + m_board[0][gameConstants::GAME_DIM - 1].getGlobalBounds().width };
	float bBottom{ m_board[gameConstants::GAME_DIM - 1][gameConstants::GAME_DIM - 1].getGlobalBounds().top + m_board[gameConstants::GAME_DIM-1][gameConstants::GAME_DIM - 1].getGlobalBounds().height };

	if (pos.x > bLeft && pos.x < bRight && pos.y > bTop && pos.y < bBottom)
	{
		return true;
	}
	return false;
}

sf::Vector2i SudokuBoard::getClickedTile(sf::Vector2i pos) const
{

	//get tile dim
	float tileDim{ m_board[0][0].getGlobalBounds().width };

	int xTile{ static_cast<int>(pos.x / tileDim) };
	int yTile{ static_cast<int>(pos.y / tileDim) };

	return { yTile, xTile };
}

void SudokuBoard::updateBoardToInt()
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_value_arr[ii][jj] = m_board[ii][jj].getValue();
		}
	}
}

void SudokuBoard::updateIntToBoard()
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setValue(m_value_arr[ii][jj]);
		}
	}
}

int& SudokuBoard::operator()(int row, int col)
{
	return m_board[row][col].m_value;
}

void SudokuBoard::resyncValtoText()
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setValue(m_board[ii][jj].getValue());
		}
	}
}

void SudokuBoard::autoMoveAfterInput()
{

	//check if active tile is last tile
	if (m_isActive == sf::Vector2i{ gameConstants::GAME_DIM - 1, gameConstants::GAME_DIM - 1})
		return;
	//if not active will be moved, set active to white, move active, set new active to grey
	m_board[m_isActive.x][m_isActive.y].setColor(sf::Color::White);
	//if not in last column move to right
	if (m_isActive.y != gameConstants::GAME_DIM - 1)
		++m_isActive.y;
	//else move down
	else
	{
		++m_isActive.x;
		m_isActive.y = 0;
	}
	//set new active tile to grey
	m_board[m_isActive.x][m_isActive.y].setColor(sf::Color(232, 236, 241, 255));
}

void SudokuBoard::reInitBoard(float tileDim, sf::Vector2f startPos)
{
	for (int ii{ 0 }; ii < gameConstants::GAME_DIM; ++ii)
	{
		for (int jj{ 0 }; jj < gameConstants::GAME_DIM; ++jj)
		{
			m_board[ii][jj].setSize(tileDim);
			m_board[ii][jj].setPosition({ startPos.x + jj * tileDim, startPos.y + ii * tileDim });
		}
	}
}
