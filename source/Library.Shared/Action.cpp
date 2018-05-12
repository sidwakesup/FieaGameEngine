#include "pch.h"
#include "Action.h"
#include "Entity.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Action)


	Action::Action(const std::string& name) : mName(name)
	{
		InitializeAttributes();
	}




	Action::Action(const Action& other) : Attributed::Attributed(other), mName(other.mName)
	{
		UpdatePrescribedAttributes();
	}




	Action::Action(Action&& other) : Attributed::Attributed(std::move(other)), mName(std::move(other.mName))
	{
		UpdatePrescribedAttributes();
	}




	Action& Action::operator=(const Action& other)
	{
		if (this != &other)
		{
			Attributed::operator=(other);
			mName = other.mName;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Action& Action::operator=(Action&& other)
	{
		if (this != &other)
		{
			Attributed::operator=(std::move(other));
			mName = std::move(other.mName);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	const std::string& Action::Name() const
	{
		return mName;
	}




	void Action::SetName(const std::string& name)
	{
		mName = name;
	}




	void Action::InitializeAttributes()
	{
		AddExternalPrescribedAttribute("Name", &mName, 1);
	}




	void Action::UpdatePrescribedAttributes()
	{
		(*this)["Name"].SetStorage(&mName, 1);
	}

}