#include "pch.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(EventMessageAttributed)

	EventMessageAttributed::EventMessageAttributed(const std::string& subType, World* world) : mSubType(subType), mWorld(world)
	{
		InitializeAttributes();
	}




	EventMessageAttributed::EventMessageAttributed(const EventMessageAttributed& other) : Attributed::Attributed(other), mSubType(other.mSubType), mWorld(other.mWorld)
	{
		UpdatePrescribedAttributes();
	}




	EventMessageAttributed::EventMessageAttributed(EventMessageAttributed&& other) : Attributed::Attributed(std::move(other)), mSubType(std::move(other.mSubType)), mWorld(std::move(other.mWorld))
	{
		UpdatePrescribedAttributes();
	}




	EventMessageAttributed& EventMessageAttributed::operator=(const EventMessageAttributed& other)
	{
		if (this != &other)
		{
			Attributed::operator=(other);
			mSubType = other.mSubType;
			mWorld = other.mWorld;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	EventMessageAttributed& EventMessageAttributed::operator=(EventMessageAttributed&& other)
	{
		if (this != &other)
		{
			Attributed::operator=(std::move(other));
			mSubType = std::move(other.mSubType);
			mWorld = std::move(other.mWorld);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Scope* EventMessageAttributed::Clone()
	{
		return new EventMessageAttributed(*this);
	}




	const std::string& EventMessageAttributed::GetSubType() const
	{
		return mSubType;
	}




	void EventMessageAttributed::SetSubType(const std::string& subType)
	{
		mSubType = subType;
	}




	World* EventMessageAttributed::GetWorld() const
	{
		return mWorld;
	}




	void EventMessageAttributed::SetWorld(World* world)
	{
		mWorld = world;
	}




	void EventMessageAttributed::InitializeAttributes()
	{
		AddToPrescribedAttributes("Name");
		AddExternalPrescribedAttribute("SubType", &mSubType, 1);
		Append("this") = static_cast<RTTI*>(this);
		AddToPrescribedAttributes("this");
	}




	void EventMessageAttributed::UpdatePrescribedAttributes()
	{
		(*this)["SubType"].SetStorage(&mSubType, 1);
	}

}