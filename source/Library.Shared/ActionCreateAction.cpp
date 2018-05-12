#include "pch.h"
#include "ActionCreateAction.h"
#include "Entity.h"
#include "ActionList.h"


namespace FieaGameEngine
{


	RTTI_DEFINITIONS(ActionCreateAction)


	ActionCreateAction::ActionCreateAction(const std::string& name) : Action::Action(name)
	{
		InitializeAttributes();
	}




	ActionCreateAction::ActionCreateAction(const ActionCreateAction& other) : Action::Action(other), mClassName(other.mClassName), mInstanceName(other.mInstanceName)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionCreateAction::ActionCreateAction(ActionCreateAction&& other) : Action::Action(std::move(other)), mClassName(std::move(other.mClassName)), mInstanceName(std::move(other.mInstanceName))
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionCreateAction& ActionCreateAction::operator=(const ActionCreateAction& other)
	{
		if (this != &other)
		{
			Action::operator=(other);
			mClassName = other.mClassName;
			mInstanceName = other.mInstanceName;
			SetName(other.Name());
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionCreateAction& ActionCreateAction::operator=(ActionCreateAction&& other)
	{
		if (this != &other)
		{
			Action::operator=(std::move(other));
			mClassName = std::move(other.mClassName);
			mInstanceName = std::move(other.mInstanceName);
			SetName(std::move(other.Name()));
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	void ActionCreateAction::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;

		auto parent = GetParent();
		if (parent->Is(Entity::TypeIdClass()))
		{
			parent->As<Entity>()->CreateAction(Find("ClassName")->Get<std::string>(0), Find("InstanceName")->Get<std::string>(0));
		}
		else if (parent->Is(ActionList::TypeIdClass()))
		{
			parent->As<ActionList>()->CreateAction(Find("ClassName")->Get<std::string>(0), Find("InstanceName")->Get<std::string>(0));
		}
	}




	Scope* ActionCreateAction::Clone()
	{
		return new ActionCreateAction(*this);
	}




	void ActionCreateAction::InitializeAttributes()
	{
		AddExternalPrescribedAttribute("ClassName", &mClassName, 1);
		AddExternalPrescribedAttribute("InstanceName", &mInstanceName, 1);
	}




	void ActionCreateAction::UpdatePrescribedAttributes()
	{
		(*this)["ClassName"].SetStorage(&mClassName, 1);
		(*this)["InstanceName"].SetStorage(&mInstanceName, 1);
	}


}