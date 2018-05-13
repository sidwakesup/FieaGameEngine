#include "pch.h"
#include "WorldState.h"

namespace FieaGameEngine
{

	WorldState::WorldState() : mGameTime(), CurrentWorld(nullptr), CurrentSector(nullptr), CurrentEntity(nullptr), CurrentAction(nullptr)
	{
	}




	const GameTime& WorldState::GetGameTime() const
	{
		return mGameTime;
	}




	void WorldState::SetGameTime(const GameTime& newGameTimeObject)
	{
		mGameTime = newGameTimeObject;
	}

}