#pragma once
#include"State.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"GameLoop.h"
#include"SudokuBoard.h"


class MainMenuState : public Engine::State
{
private:
	Engine::gameDataPtr m_gameData;
	sf::Clock m_clock;
	sf::Sprite m_backgroundSprite;
	sf::Sprite m_button_solve;
	sf::Sprite m_button_manual;

	sf::Text m_text_button_solve;
	sf::Text m_text_button_manual;
	sf::Text m_text_sudokuPrint;

	std::string m_input;


	SudokuBoard m_board;


public:
	MainMenuState(Engine::gameDataPtr gameData);

	virtual bool init() override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw(float deltaTime) override;

	void manualInput();

};


