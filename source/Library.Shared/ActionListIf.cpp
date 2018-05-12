#include "pch.h"
#include "ActionListIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListIf)

	ActionListIf::ActionListIf(const std::string& name) : ActionList::ActionList(name)
	{
		InitializeAttributes();
	}




	ActionListIf::ActionListIf(const ActionListIf& other) : ActionList::ActionList(other), mCondition(other.mCondition), mThen(other.mThen), mElse(other.mElse)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionListIf::ActionListIf(ActionListIf&& other) : ActionList::ActionList(std::move(other)), mCondition(std::move(other.mCondition)), mThen(std::move(other.mThen)), mElse(std::move(other.mElse))
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionListIf& ActionListIf::operator=(const ActionListIf& other)
	{
		if (this != &other)
		{
			ActionList::operator=(other);
			mCondition = other.mCondition;
			mThen = other.mThen;
			mElse = other.mElse;
			SetName(other.Name());
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionListIf& ActionListIf::operator=(ActionListIf&& other)
	{
		if (this != &other)
		{
			ActionList::operator=(std::move(other));
			mCondition = std::move(other.mCondition);
			mThen = std::move(other.mThen);
			mElse = std::move(other.mElse);
			SetName(std::move(other.Name()));
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Action& ActionListIf::CreateAction(const std::string& actionClassName, const std::string& actionInstanceName, const std::string& branchName)
	{
		Action* action = (Factory<Action>::Create(actionClassName))->As<Action>();
		if (action == nullptr)
		{
			throw std::exception("Unable to create action!");
		}
		action->SetName(actionInstanceName);
		Adopt(*action, branchName);
		return *action;
	}




	void ActionListIf::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;

		mCondition = Find("Condition")->Get<std::int32_t>();

		if (mCondition == 1)
		{
			mThen = Find("Then")->Get<Scope*>();
			if (mThen == nullptr)
			{
				throw std::exception("Invalid Action List If.");
			}
			mThen->As<Action>()->Update(worldState);
		}
		else if (mCondition == 0)
		{
			mElse = Find("Else")->Get<Scope*>();
			if (mElse == nullptr)
			{
				throw std::exception("Invalid Action List If.");
			}
			mElse->As<Action>()->Update(worldState);
		}
	}




	Scope* ActionListIf::Clone()
	{
		return new ActionListIf(*this);
	}




	void ActionListIf::InitializeAttributes()
	{
		Append("Then");
		Append("Else");
		AddToPrescribedAttributes("Then");
		AddToPrescribedAttributes("Else");
		AddExternalPrescribedAttribute("Condition", &mCondition, 1);
	}




	void ActionListIf::UpdatePrescribedAttributes()
	{
		(*this)["Condition"].SetStorage(&mCondition, 1);
		Find("Then")->Get<Scope*>() = mThen;
		Find("Else")->Get<Scope*>() = mElse;
	}
}