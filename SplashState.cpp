#include "SplashState.h"
#include<iostream>
#include<sstream>
#include<memory>
#include"constants.h"
#include"utility.h"
#include"MainMenu.h"

SplashState::SplashState(Engine::gameDataPtr gameData) : m_gameData{ gameData } //remember that those are shared pointers
{
}

bool SplashState::init()
{
	//set background color to a default and display a welcome message
	m_gameData->window.clear(sf::Color::Magenta);
	//load default font
	m_gameData->resourceMan.loadFont("defaultFont", gameConstants::defaultFont);
	//define a user text (remmeber that getFont can throw!)
	try
	{
		m_welcomeText.setFont(m_gameData->resourceMan.getFont("defaultFont"));
	}
	catch (int)
	{
		std::cerr << "ERROR!! FONT COULD NOT BE RETRIEVED!\n";
	}
	m_welcomeText.setCharacterSize(40);
	m_welcomeText.setString("Welcome!\nVersion " + gameConstants::currentVersion);
	//m_welcomeText.setPosition(m_gameData->window.getSize().x / 2.0f + (m_welcomeText.getGlobalBounds().width / 2.0f), m_gameData->window.getSize().y / 2.0f + (m_welcomeText.getGlobalBounds().height / 2.0f));
	m_welcomeText.setPosition(utility::centralPosition(m_welcomeText, m_gameData->window));
	//test if previous line can be replaced by utility function!
	m_welcomeText.setFillColor(sf::Color::Black);

	return true;
}

void SplashState::handleInput()
{
	sf::Event event;
	while (m_gameData->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_gameData->window.close();
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			m_gameData->window.close();
	}
}

void SplashState::update(float deltaTime)
{
	//change welcome text after some time
	if (m_clock.getElapsedTime().asSeconds() > gameConstants::splash_welcome_time)
	{
		m_welcomeText.setString("Entering main menu");
		m_welcomeText.setPosition(utility::centralPosition(m_welcomeText, m_gameData->window)); //recalculate center pos
	}
	if (m_clock.getElapsedTime().asSeconds() > 2 * gameConstants::splash_welcome_time)
	{
		//enter main menu, clean up etc..
		m_gameData->machine.addState(std::make_unique<MainMenuState>(m_gameData), true);
	}
}

void SplashState::draw(float deltaTime)
{
	m_gameData->window.clear(sf::Color::Magenta);
	m_gameData->window.draw(m_welcomeText);
	m_gameData->window.display();
}
