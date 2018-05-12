#include "pch.h"
#include "ActionEvent.h"
#include "Event.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionEvent)


	ActionEvent::ActionEvent(const std::string& name, const std::string& subType, const std::int32_t& delay) : Action::Action(name), mSubType(subType), mDelay(delay)
	{
		InitializeAttributes();
	}




	ActionEvent::ActionEvent(const ActionEvent& other) : Action::Action(other), mSubType(other.mSubType), mDelay(other.mDelay)
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionEvent::ActionEvent(ActionEvent&& other) : Action::Action(std::move(other)), mSubType(std::move(other.mSubType)), mDelay(std::move(other.mDelay))
	{
		SetName(other.Name());
		UpdatePrescribedAttributes();
	}




	ActionEvent& ActionEvent::operator=(const ActionEvent& other)
	{
		if (this != &other)
		{
			Action::operator=(other);
			mSubType = other.mSubType;
			mDelay = other.mDelay;
			SetName(other.Name());
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ActionEvent& ActionEvent::operator=(ActionEvent&& other)
	{
		if (this != &other)
		{
			Action::operator=(std::move(other));
			mSubType = std::move(other.mSubType);
			mDelay = std::move(other.mDelay);
			SetName(std::move(other.Name()));
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	std::string ActionEvent::GetSubType() const
	{
		return mSubType;
	}




	void ActionEvent::SetSubType(const std::string& subType)
	{
		mSubType = subType;
		UpdatePrescribedAttributes();
	}




	std::int32_t ActionEvent::GetDelay() const
	{
		return mDelay;
	}




	void ActionEvent::SetDelay(const std::int32_t& delay)
	{
		mDelay = delay;
		UpdatePrescribedAttributes();
	}




	void ActionEvent::Update(WorldState& worldState)
	{
		worldState.CurrentAction = this;
		auto& world = worldState.CurrentWorld;
		EventMessageAttributed ema(mSubType, worldState.CurrentWorld);

		auto Attributes = GetAttributes();

		for (auto& Attribute : Attributes)
		{
			if (!IsPrescribedAttribute(Attribute->first))
			{
				ema.AppendAuxiliaryAttribute(Attribute->first) = Attribute->second;
			}
		}

		std::shared_ptr<Event<EventMessageAttributed>> emaEvent = std::make_shared<Event<EventMessageAttributed>>(ema);
		world->GetEventQueue().Enqueue(emaEvent, worldState.GetGameTime(), std::chrono::milliseconds(mDelay));
	}




	Scope* ActionEvent::Clone()
	{
		return new ActionEvent(*this);
	}




	void ActionEvent::InitializeAttributes()
	{
		AddToPrescribedAttributes("Name");
		AddExternalPrescribedAttribute("SubType", &mSubType, 1);
		AddExternalPrescribedAttribute("Delay", &mDelay, 1);
		Append("this") = static_cast<RTTI*>(this);
		AddToPrescribedAttributes("this");
	}




	void ActionEvent::UpdatePrescribedAttributes()
	{
		(*this)["SubType"].SetStorage(&mSubType, 1);
		(*this)["Delay"].SetStorage(&mDelay, 1);
	}


}