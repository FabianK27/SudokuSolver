#include "SudokuTile.h"
#include"utility.h"
#include<iostream>

SudokuTile::SudokuTile(const sf::Vector2f& pos, float tileDim, int val) : m_value{ val }
{
	//init tile
	m_tile.setSize({ tileDim, tileDim });
	m_tile.setPosition(pos);
	m_tile.setFillColor(sf::Color::White);
	m_tile.setOutlineThickness(-1);
	m_tile.setOutlineColor(sf::Color::Black);

	//init text
	m_text_value.setCharacterSize((int)0.8 * tileDim);
	m_text_value.setFillColor(sf::Color::Black);
	m_text_value.setString(std::to_string(m_value));
	m_text_value.setPosition(utility::centralPosRelativeTo<sf::Text, sf::RectangleShape>(m_text_value, m_tile));

}

const void SudokuTile::setValue(int val)
{
	m_value = val;
	m_text_value.setString(std::to_string(val));
}

void SudokuTile::setPosition(const sf::Vector2f& pos)
{
	m_tile.setPosition(pos);
	m_text_value.setPosition(utility::centralPosRelativeTo<sf::Text, sf::RectangleShape>(m_text_value, m_tile));
	
}

void SudokuTile::setSize(float size)
{
	m_tile.setSize({ size, size });
	m_text_value.setCharacterSize(static_cast<int>(0.8 * m_tile.getSize().x));
}

void SudokuTile::drawTile(sf::RenderWindow& window) const
{
	window.draw(m_tile);
	if (m_value != 0)
	{
		window.draw(m_text_value);
		//std::cout << "number position: " << m_text_value.getPosition().x << ", " << m_text_value.getPosition().y <<'\n';
		//std::cout << "charSize: " << m_text_value.getCharacterSize() << '\n';
	}
}
