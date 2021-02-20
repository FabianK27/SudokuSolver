#pragma once
#include<SFML/Graphics.hpp>
#include"ResourceManager.h"

class SudokuBoard;

class SudokuTile
{
private:
	int m_value;
	sf::RectangleShape m_tile;
	sf::Text m_text_value;
public:
	SudokuTile(const sf::Vector2f& pos = { 0, 0 }, float tileDim = 0, int val = 0);

	int getValue() { return m_value; } const
	void setValue(int val);

	void setPosition(const sf::Vector2f& pos);
	void setSize(float size);
	void setFont(const sf::Font& font) { m_text_value.setFont(font); }
	void setColor(sf::Color col) { m_tile.setFillColor(col); }

	void drawTile(sf::RenderWindow& window) const;

	sf::FloatRect getGlobalBounds() const { return m_tile.getGlobalBounds(); }

	friend SudokuBoard;

};

