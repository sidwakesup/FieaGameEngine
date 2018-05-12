#include "pch.h"
#include "Entity.h"
#include "ActionList.h"
#include "ActionDestroyer.h"
#include "ActionDestroyAction.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionDestroyAction)


	ActionDestroyAction::ActionDestroyAction(const std::string& name) : Action::Action(name)
	{
		InitializeAttributes();
	}




	ActionDestroyAction::ActionDestroyAction(const ActionDestroyAction& other) : Action::Action(other), mInstanceName(other.mInstanceName)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionDestroyAction::ActionDestroyAction(ActionDestroyAction&& other) : Action::Action(std::move(other)), mInstanceName(std::move(other.mInstanceName))
	{
		SetName(std::move(other.Name()));
		UpdatePrescribedAttributes();
	}




	ActionDestroyAction& ActionDestroyAction::operator=(const ActionDestroyAction& other)
	{
		if (this != &other)
		{
			Action::operator=(other);
			mInstanceName = other.mInstanceName;
			SetName(other.Name());
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionDestroyAction& ActionDestroyAction::operator=(ActionDestroyAction&& other)
	{
		if (this != &other)
		{
			Action::operator=(std::move(other));
			mInstanceName = std::move(other.mInstanceName);
			SetName(std::move(other.Name()));
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	void ActionDestroyAction::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;

		bool found = false;
		auto parent = GetParent();

		while (found == false)
		{
			auto actions = parent->Search("Actions");

			for (std::uint32_t i = 0; i < actions->Size(); ++i)
			{
				auto action = actions->Get<FieaGameEngine::Scope*>(i)->As<Action>();

				if (action->Find("Name")->Get<std::string>(0) == mInstanceName)
				{
					ActionDestroyer::AddToListOfActionsToBeDestroyed(action);
					found = true;
					break;
				}
			}

			if (found == false)
			{
				parent = GetParent();
				if (parent == nullptr)
				{
					found = true;
				}
			}
		}
	}




	Scope* ActionDestroyAction::Clone()
	{
		return new ActionDestroyAction(*this);
	}




	void ActionDestroyAction::InitializeAttributes()
	{
		AddExternalPrescribedAttribute("InstanceName", &mInstanceName, 1);
	}




	void ActionDestroyAction::UpdatePrescribedAttributes()
	{
		(*this)["InstanceName"].SetStorage(&mInstanceName, 1);
	}



}