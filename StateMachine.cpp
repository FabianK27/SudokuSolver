#include "StateMachine.h"

namespace Engine
{
	void StateMachine::addState(statePtr newState, bool replaceCurrentState)
	{
		// set add to true
		m_isAdding = true;
		m_isReplacing = replaceCurrentState;

		m_newState = std::move(newState); // member smart pointer gets control / ownership of newState (std::move triggers move assignment)
	}

	void StateMachine::removeState()
	{
		m_isRemoving = true;
	}

	void StateMachine::processStateChange()
	{
		if (m_isRemoving && !m_stateStack.empty()) //check if we want to remove a stack and if there are any states to begin with
		{
			m_stateStack.pop(); //remove top state
			if (!m_stateStack.empty()) //..and if there is a state left, make it active
				m_stateStack.top()->resume();
			m_isRemoving = false; // done removing state
		}

		if (m_isAdding)
		{
			if (!m_stateStack.empty())
			{
				if (m_isReplacing) //if there is a state and we want to replace it add new state on top
				{
					m_stateStack.pop();
				}
				else
				{
					m_stateStack.top()->pause(); //if not replace then pause
				}
			}

			m_stateStack.push(std::move(m_newState)); // assing control of new state to stateStack
			m_stateStack.top()->init(); // initialize the new state
			m_isAdding = false;
		}
	}

	statePtr& StateMachine::getActiveState()
	{
		return m_stateStack.top();
	}

}