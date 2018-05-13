#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ReactionAttributed)

	ReactionAttributed::ReactionAttributed(const std::string& name, const std::string& subType) : Reaction::Reaction(name), mSubType(subType)
	{
		InitializeAttributes();
		Event<EventMessageAttributed>::Subscribe(*this);
	}




	ReactionAttributed::ReactionAttributed(const ReactionAttributed& other) : Reaction::Reaction(other), mSubType(other.mSubType)
	{
		UpdatePrescribedAttributes();
	}




	ReactionAttributed::ReactionAttributed(ReactionAttributed&& other) : Reaction::Reaction(std::move(other)), mSubType(std::move(other.mSubType))
	{
		UpdatePrescribedAttributes();
	}




	ReactionAttributed& ReactionAttributed::operator=(const ReactionAttributed& other)
	{
		if (this != &other)
		{
			Reaction::operator=(other);
			mSubType = other.mSubType;
			UpdatePrescribedAttributes();
		}

		return *this;
	}


	ReactionAttributed& ReactionAttributed::operator=(ReactionAttributed&& other)
	{
		if (this != &other)
		{
			Reaction::operator=(std::move(other));
			mSubType = std::move(other.mSubType);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}




	std::string ReactionAttributed::GetSubType() const
	{
		return mSubType;
	}




	void ReactionAttributed::SetSubType(const std::string& subType)
	{
		mSubType = subType;
		UpdatePrescribedAttributes();
	}




	void ReactionAttributed::Update(WorldState& worldState)
	{
		ActionList::Update(worldState);
	}




	Scope* ReactionAttributed::Clone()
	{
		return new ReactionAttributed(*this);
	}




	void ReactionAttributed::Notify(const IEventPublisher& publisher)
	{
		assert(publisher.Is(FieaGameEngine::Event<EventMessageAttributed>::TypeIdClass()));
		auto& mMessage = (&publisher)->As<Event<EventMessageAttributed>>()->Message();

		auto Attributes = mMessage.GetAttributes();

		for (auto& attribute : Attributes)
		{
			if (!mMessage.IsPrescribedAttribute(attribute->first))
			{
				auto& datum = Append(attribute->first);
				datum = attribute->second;
			}
		}

		if (mMessage.GetSubType() == mSubType)
		{
			Update(mMessage.GetWorld()->GetWorldState());
		}
	}




	void ReactionAttributed::InitializeAttributes()
	{
		AddToPrescribedAttributes("Name");
		AddExternalPrescribedAttribute("SubType", &mSubType, 1);
		Append("this") = static_cast<RTTI*>(this);
		AddToPrescribedAttributes("this");
	}




	void ReactionAttributed::UpdatePrescribedAttributes()
	{
		(*this)["SubType"].SetStorage(&mSubType, 1);
	}

}