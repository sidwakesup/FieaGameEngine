#include "pch.h"
#include "ActionPrint.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionPrint)


	ActionPrint::ActionPrint(const std::string& name) : Action::Action(name)
	{
		InitializeAttributes();
	}




	ActionPrint::ActionPrint(const ActionPrint& other) : Action::Action(other), mLog(other.mLog)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionPrint::ActionPrint(ActionPrint&& other) : Action::Action(std::move(other)), mLog(std::move(other.mLog))
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionPrint& ActionPrint::operator=(const ActionPrint& other)
	{
		if (this != &other)
		{
			Action::operator=(other);
			SetName(other.Name());
			mLog = other.mLog;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionPrint& ActionPrint::operator=(ActionPrint&& other)
	{
		if (this != &other)
		{
			Action::operator=(std::move(other));
			SetName(std::move(other.Name()));
			mLog = std::move(other.mLog);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	void ActionPrint::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;

		mLog = Find("Log")->Get<std::string>();
		OutputDebugStringA(mLog.c_str());
	}




	Scope* ActionPrint::Clone()
	{
		return new ActionPrint(*this);
	}




	void ActionPrint::InitializeAttributes()
	{
		AddExternalPrescribedAttribute("Log", &mLog, 1);
	}




	void ActionPrint::UpdatePrescribedAttributes()
	{
		(*this)["Log"].SetStorage(&mLog, 1);
	}

}