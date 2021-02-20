#pragma once
namespace Engine
{
	class State // interface to manage game at high level
	{
	public:
		virtual bool init() = 0; //return true if init is succesful
		virtual void handleInput() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw(float deltaTime) = 0; //deltaTime will be used to make gamespeed fps independent (probably irrelevant for sudoku..)

		virtual void pause() {}
		virtual void resume() {}
	};

}
