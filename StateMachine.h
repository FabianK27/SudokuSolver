#pragma once
#include "State.h"

#include<stack>
#include<memory> //for smart pointer std::unique_ptr

namespace Engine
{
	using statePtr = std::unique_ptr<State>;

	class StateMachine //this will handle our different states that are to be implemented from interface State
	{
	private:
		std::stack<statePtr> m_stateStack; //use a stack container because only the top state should be processed 
		statePtr m_newState;

		bool m_isAdding{ false };
		bool m_isRemoving{ false };
		bool m_isReplacing{ false }; //these bools keep track of what we're doing per update

	public:
		StateMachine() {}
		~StateMachine() {}

		void addState(statePtr newState, bool replaceCurrentState = true); // use smart pointer to states for convenience, bool decides whether to replace the current state or keep it
		void removeState();

		void processStateChange();

		statePtr& getActiveState();
	};

}