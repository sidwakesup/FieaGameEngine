#include "pch.h"
#include "World.h"
#include "ActionDestroyer.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(World)



	World::World(const std::string& name) : mName(name), mWorldState(), mEventQueue()
	{
		InitializeAttributes();
	}




	World::World(const World& other) : Attributed::Attributed(other), mName(other.mName), mSectors(other.mSectors), mReactions(other.mReactions)
	{
		UpdatePrescribedAttributes();
	}




	World::World(World&& other) : Attributed::Attributed(std::move(other)), mName(std::move(other.mName)), mSectors(std::move(other.mSectors)), mReactions(std::move(other.mReactions))
	{
		UpdatePrescribedAttributes();
	}




	World& World::operator=(const World& other)
	{
		if (this != &other)
		{
			Attributed::operator=(other);
			mName = other.mName;
			mSectors = other.mSectors;
			mReactions = other.mReactions;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	World& World::operator=(World&& other)
	{
		if (this != &other)
		{
			Attributed::operator=(std::move(other));
			mName = std::move(other.mName);
			mSectors = std::move(other.mSectors);
			mReactions = std::move(other.mReactions);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	const std::string& World::Name() const
	{
		return mName;
	}




	void World::SetName(const std::string& name)
	{
		mName = name;
	}




	const Datum* World::Sectors() const
	{
		return Find("Sectors");
	}




	const Datum* World::Reactions() const
	{
		return Find("Reactions");
	}




	WorldState& World::GetWorldState()
	{
		return mWorldState;
	}




	EventQueue& World::GetEventQueue()
	{
		return mEventQueue;
	}




	Sector& World::CreateSector(const std::string& sectorName)
	{
		Sector* sector = new Sector(sectorName);
		sector->SetWorld(this);
		return *sector;
	}




	Reaction& World::CreateReaction(const std::string& reactionClassName, const std::string& reactionInstanceName)
	{
		reactionClassName;
		reactionInstanceName;
		Reaction* reaction = (Factory<Reaction>::Create(reactionClassName));
		if (reaction == nullptr)
		{
			throw std::exception("Unable to create reaction.");
		}
		reaction->SetName(reactionInstanceName);
		Adopt(*reaction, "Reactions");
		return *reaction;
	}




	void World::Update()
	{
		mWorldState.CurrentWorld = this;

		mSectors = Find("Sectors");
		assert(mSectors != nullptr);
		for (std::uint32_t i = 0; i < mSectors->Size(); ++i)
		{
			assert((*mSectors)[i].Is(Sector::TypeIdClass()));
			(*mSectors)[i].As<Sector>()->Update(mWorldState);
		}

		mEventQueue.Update(mWorldState.GetGameTime());

		ActionDestroyer::Cleanup();

	}




	Scope* World::Clone()
	{
		return new World(*this);
	}




	void World::InitializeAttributes()
	{
		mSectors = &Append("Sectors");
		AddToPrescribedAttributes("Sectors");
		mReactions = &Append("Reactions");
		AddToPrescribedAttributes("Reactions");
		AddExternalPrescribedAttribute("Name", &mName, 1);
	}




	void World::UpdatePrescribedAttributes()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		*Find("Sectors") = *mSectors;
		*Find("Reactions") = *mReactions;
	}

}