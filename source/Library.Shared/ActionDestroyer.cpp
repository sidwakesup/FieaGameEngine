#include "pch.h"
#include "ActionDestroyer.h"
#include "Action.h"


namespace FieaGameEngine
{

	Vector<Action*> ActionDestroyer::mActionsToBeDestroyed;


	void ActionDestroyer::AddToListOfActionsToBeDestroyed(Action* actionToBeDestroyed)
	{
		mActionsToBeDestroyed.PushBack(actionToBeDestroyed);
	}




	void ActionDestroyer::Cleanup()
	{
		for (std::uint32_t i = 0; i < mActionsToBeDestroyed.Size(); ++i)
		{
			delete mActionsToBeDestroyed[i];
		}
		mActionsToBeDestroyed.Clear();
	}
}