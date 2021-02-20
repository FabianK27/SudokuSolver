#include "MainMenu.h"
#include"constants.h"
#include"utility.h"
#include"SudokuBoard.h"
#include"SudokuSolver.h"
MainMenuState::MainMenuState(Engine::gameDataPtr gameData) : m_gameData{ gameData }, m_board(0, { 0, 0 })
{

}

bool MainMenuState::init()
{
	//load textures
	m_gameData->resourceMan.loadTexture("background", gameConstants::defaultBackgroundTexture);
	m_gameData->resourceMan.loadTexture("defaultButton", gameConstants::defaultButtonTexture);

	//set sprites
	try
	{
		m_backgroundSprite.setTexture(m_gameData->resourceMan.getTexture("background"));
		m_button_solve.setTexture(m_gameData->resourceMan.getTexture("defaultButton"));
		m_button_manual.setTexture(m_gameData->resourceMan.getTexture("defaultButton"));
	}
	catch (int)
	{
		std::cerr << "ERROR WHILE RETRIEVING TEXTURE!\n";
	}

	//resize sprites
	m_backgroundSprite.setScale(utility::resizeRelToWindow<sf::Sprite>(m_backgroundSprite, m_gameData->window, 1.0f, 1.0f));
	m_button_manual.setScale(utility::resizeRelToWindow<sf::Sprite>(m_button_manual, m_gameData->window, 0.2, 0.15));
	m_button_solve.setScale(utility::resizeRelToWindow<sf::Sprite>(m_button_solve, m_gameData->window, 0.2, 0.15));

	//postion buttons
	m_button_solve.setPosition(m_gameData->window.getSize().x - m_button_solve.getGlobalBounds().width * 1.05f, m_button_solve.getGlobalBounds().height * 0.2f);
	m_button_manual.setPosition(m_gameData->window.getSize().x - m_button_manual.getGlobalBounds().width * 1.05f, m_button_manual.getGlobalBounds().height * 1.5f);

	//attach text to buttons
	try
	{
		m_text_button_solve.setFont(m_gameData->resourceMan.getFont("defaultFont"));
		m_text_button_manual.setFont(m_gameData->resourceMan.getFont("defaultFont"));
	}
	catch (int)
	{
		std::cerr << "ERROR!! FONT COULD NOT BE RETRIEVED!\n";
	}
	m_text_button_solve.setCharacterSize(40);
	m_text_button_solve.setString("Solve");
	m_text_button_solve.setPosition(utility::centralPosRelativeTo<sf::Text, sf::Sprite>(m_text_button_solve, m_button_solve));
	m_text_button_solve.setFillColor(sf::Color::Black);

	m_text_button_manual.setCharacterSize(40);
	m_text_button_manual.setString("Manual");
	m_text_button_manual.setPosition(utility::centralPosRelativeTo<sf::Text, sf::Sprite>(m_text_button_manual, m_button_manual));
	m_text_button_manual.setFillColor(sf::Color::Black);

	//set tile value font
	m_board.setFont(m_gameData->resourceMan.getFont("defaultFont"));
	//get tile size and reinit the board
	m_board.reInitBoard(utility::tileSizeConstraint<sf::Sprite>(m_button_solve, m_gameData->window), { 1.0f, 1.0f });
	return true;

}

void MainMenuState::handleInput()
{
	sf::Event event;
	while (m_gameData->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_gameData->window.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			m_gameData->window.close();

		//add button click events
		if (m_gameData->inputMan.isSpriteClicked(m_button_solve, sf::Mouse::Button::Left, m_gameData->window))
		{
			std::cout << "Pressed Solve!\n";
			//try to solve the board
			bool success{ SudokuSolver::solveSudokuDyn(m_board) };
			if (success)
			{
				m_board.resyncValtoText();
				std::cout << "SUCCESS!\n";
			}
			else
				std::cout << "FAILED TO SOLVE!\n";
			continue;
		}
		if (m_gameData->inputMan.isSpriteClicked(m_button_manual, sf::Mouse::Button::Left, m_gameData->window))
		{
			manualInput();
			//sf::Thread inpThread(&utility::threadCaller, this);
			//inpThread.launch();
	
			continue;
		}
		//add button hover events
		if (m_gameData->inputMan.isSpriteHovered(m_button_solve, m_gameData->window))
		{
			m_text_button_solve.setFillColor(sf::Color::Red);

			continue;
		}
		else
		{
			m_text_button_solve.setFillColor(sf::Color::Black);

			
		}
		if (m_gameData->inputMan.isSpriteHovered(m_button_manual, m_gameData->window))
		{
			m_text_button_manual.setFillColor(sf::Color::Red);
			continue;
		}
		else
		{
			m_text_button_manual.setFillColor(sf::Color::Black);

			
		}
		//

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0 && event.key.shift)
		{
			m_board.randomFillBoard();
			continue;
		}
		//check if board was clicked
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && m_board.posInside(m_gameData->inputMan.getMousePos(m_gameData->window)))
		{
			sf::Vector2i tileClicked{ m_board.getClickedTile(m_gameData->inputMan.getMousePos(m_gameData->window)) };
			//set active tile to white color
			if (m_board.getActive().x != -1 && m_board.getActive().y != -1)
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color::White);
			//set clicked to active
			m_board.setActive(tileClicked);
			//set tile clicked color to grey
			m_board.accessTiles()[tileClicked.x][tileClicked.y].setColor(sf::Color(232, 236, 241, 255));

			continue;
		}
		// switch for number input
		if (event.type == sf::Event::KeyPressed)
		{
			if (m_board.getActive().x == -1 || m_board.getActive().y == -1) //check if any square selected
				continue;
			switch (event.key.code)
			{
			case sf::Keyboard::Num0:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(0);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num1:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(1);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num2:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(2);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num3:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(3);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num4:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(4);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num5:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(5);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num6:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(6);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num7:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(7);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num8:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(8);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Num9:
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setValue(9);
				m_board.autoMoveAfterInput();
				break;
			case sf::Keyboard::Up:
				if (m_board.getActive().x == 0)
					break;

				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color::White);
				m_board.setActive(m_board.getActive() + sf::Vector2i{-1, 0});
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color(232, 236, 241, 255));
				break;
			case sf::Keyboard::Down:
				if (m_board.getActive().x == gameConstants::GAME_DIM - 1)
					break;

				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color::White);
				m_board.setActive(m_board.getActive() + sf::Vector2i{ 1, 0 });
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color(232, 236, 241, 255));
				break;
			case sf::Keyboard::Left:
				if (m_board.getActive().y == 0)
					break;

				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color::White);
				m_board.setActive(m_board.getActive() + sf::Vector2i{ 0, -1 });
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color(232, 236, 241, 255));
				break;
			case sf::Keyboard::Right:
				if (m_board.getActive().y == gameConstants::GAME_DIM - 1)
					break;

				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color::White);
				m_board.setActive(m_board.getActive() + sf::Vector2i{ 0, 1 });
				m_board.accessTiles()[m_board.getActive().x][m_board.getActive().y].setColor(sf::Color(232, 236, 241, 255));
				break;
			}
		}

	}
}

void MainMenuState::update(float deltaTime)
{

}

void MainMenuState::draw(float deltaTime)
{
	m_gameData->window.clear(sf::Color::White);
	//draw all objects
	m_gameData->window.draw(m_backgroundSprite);
	m_gameData->window.draw(m_button_manual);
	m_gameData->window.draw(m_button_solve);
	m_gameData->window.draw(m_text_button_solve);
	m_gameData->window.draw(m_text_button_manual);



    //draw board

	m_board.drawBoard(m_gameData->window);
	

	m_gameData->window.display();
}

void MainMenuState::manualInput()
{
	do
	{
		std::cout << "Manual Input: Sequence of 81 single digit numbers (rows per row)\n";
		std::getline(std::cin, m_input);
	} while (m_input.length() != gameConstants::GAME_DIM * gameConstants::GAME_DIM);
	int counter{ 0 };
	for (int i{ 0 }; i < gameConstants::GAME_DIM; ++i)
	{
		for (int j{ 0 }; j < gameConstants::GAME_DIM; ++j)
		{
			m_board(i, j) = static_cast<int>(m_input.at(counter++) - '0'); // by subtracting char 0 the cast to int will produce the literal int instead of the ascii int code effectively
		}
	}
	m_board.resyncValtoText();
}
