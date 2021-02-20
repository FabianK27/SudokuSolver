#pragma once
#include"SFML/Graphics.hpp"
#include<array>
#include"SudokuTile.h"
#include"constants.h"
#include"ResourceManager.h"
#include"SudokuSolver.h"

class SudokuBoard
{
private:
	//SudokuTile m_board[gameConstants::GAME_DIM][gameConstants::GAME_DIM];
	SudokuTile** m_board;
	int** m_value_arr;
	sf::Vector2i m_isActive{-1, -1};

public:
	SudokuBoard(float tileDim, sf::Vector2f startPos );
	~SudokuBoard();

	void reInitBoard(float tileDim, sf::Vector2f startPos);
	void drawBoard(sf::RenderWindow& window) const;

	void setFont(const sf::Font& font);
	SudokuTile** accessTiles() { return m_board; }

	void randomFillBoard();
	
	bool posInside(sf::Vector2i pos) const;

	sf::Vector2i getClickedTile(sf::Vector2i pos) const;

	void updateBoardToInt();
	void updateIntToBoard();

	void setActive(const sf::Vector2i& pos) { m_isActive = pos; }
	sf::Vector2i getActive() const { return m_isActive; }

	//overload operator ()
	int& operator()(int row, int col);

	void resyncValtoText();

	void autoMoveAfterInput();
};

