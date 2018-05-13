#include "pch.h"
#include "Reaction.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Reaction)

	Reaction::Reaction(const std::string& name) : ActionList::ActionList(name)
	{
	}




	Reaction::Reaction(const Reaction& other) : ActionList::ActionList(other)
	{
		SetName(other.Name());
	}




	Reaction::Reaction(Reaction&& other) : ActionList::ActionList(std::move(other))
	{
		SetName(other.Name());
	}




	Reaction& Reaction::operator=(const Reaction& other)
	{
		if (this != &other)
		{
			ActionList::operator=(other);
			SetName(other.Name());
		}

		return *this;
	}




	Reaction& Reaction::operator=(Reaction&& other)
	{
		if (this != &other)
		{
			ActionList::operator=(std::move(other));
			SetName(std::move(other.Name()));
		}

		return *this;
	}

}