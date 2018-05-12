#include "pch.h"
#include "ActionList.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList(const std::string& name) : Action::Action(name)
	{
		InitializeAttributes();
	}




	ActionList::ActionList(const ActionList& other) : Action::Action(other), mActions(other.mActions)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionList::ActionList(ActionList&& other) : Action::Action(std::move(other)), mActions(std::move(other.mActions))
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionList& ActionList::operator=(const ActionList& other)
	{
		if (this != &other)
		{
			Action::operator=(other);
			mActions = other.mActions;
			SetName(other.Name());
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionList& ActionList::operator=(ActionList&& other)
	{
		if (this != &other)
		{
			Action::operator=(std::move(other));
			mActions = std::move(other.mActions);
			SetName(std::move(other.Name()));
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Action& ActionList::CreateAction(const std::string& actionClassName, const std::string& actionInstanceName)
	{
		Action* action = (Factory<Action>::Create(actionClassName));
		if (action == nullptr)
		{
			throw std::exception("Unable to create action!");
		}
		action->SetName(actionInstanceName);
		Adopt(*action, "Actions");
		return *action;
	}




	const Datum* ActionList::Actions() const
	{
		return Find("Actions");
	}




	void ActionList::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;
		
		mActions = Find("Actions");
		for (std::uint32_t i = 0; i < mActions->Size(); ++i)
		{
			assert((*mActions)[i].Is(Action::TypeIdClass()));
			(*mActions)[i].As<Action>()->Update(worldState);
		}
	}




	Scope* ActionList::Clone()
	{
		return new ActionList(*this);
	}




	void ActionList::InitializeAttributes()
	{
		mActions = &Append("Actions");
		AddToPrescribedAttributes("Actions");
	}




	void ActionList::UpdatePrescribedAttributes()
	{
		*Find("Actions") = *mActions;
	}

}