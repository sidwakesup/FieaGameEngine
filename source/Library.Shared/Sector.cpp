#include "pch.h"
#include "Sector.h"
#include "World.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Sector)


	

	Sector::Sector(const std::string& name) : mName(name)
	{
		InitializeAttributes();
	}




	Sector::Sector(const Sector& other) : Attributed::Attributed(other), mName(other.mName), mEntities(other.mEntities)
	{
		UpdatePrescribedAttributes();
	}




	Sector::Sector(Sector&& other) : Attributed::Attributed(std::move(other)), mName(std::move(other.mName)), mEntities(std::move(other.mEntities))
	{
		UpdatePrescribedAttributes();
	}




	Sector& Sector::operator=(const Sector& other)
	{
		if (this != &other)
		{
			Attributed::operator=(other);
			mName = other.mName;
			mEntities = other.mEntities;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Sector& Sector::operator=(Sector&& other)
	{
		if (this != &other)
		{
			Attributed::operator=(std::move(other));
			mName = std::move(other.mName);
			mEntities = std::move(other.mEntities);
			UpdatePrescribedAttributes();
		}

		return *this;
	}
		
		
		
		
	const std::string& Sector::Name() const
	{
		return mName;
	}




	void Sector::SetName(const std::string& name)
	{
		mName = name;
	}




	const Datum* Sector::Entities() const
	{
		return Find("Entities");
	}




	Entity& Sector::CreateEntity(const std::string& entityClassName, const std::string& entityInstanceName)
	{
		Entity* entity = (Factory<Entity>::Create(entityClassName))->As<Entity>();
		if (entity == nullptr)
		{
			throw std::exception("Unable to create entity!");
		}
		entity->SetName(entityInstanceName);
		entity->SetSector(this);
		return *entity;
	}




	void Sector::SetWorld(World* world)
	{
		if (GetParent() != nullptr || world == nullptr)
		{
			GetParent()->OrphanChild(*this);
		}
		if (world != nullptr)
		{
			world->Adopt(*this, "Sectors");
		}
	}




	World const* Sector::GetWorld() const
	{
		assert(GetParent() != nullptr);
		assert(GetParent()->Is(World::TypeIdClass()));
		return GetParent()->As<World>();
	}




	void Sector::Update(WorldState& worldState)
	{
		worldState.CurrentSector = this;

		mEntities = Find("Entities");
		for (std::uint32_t i = 0; i < mEntities->Size(); ++i)
		{
			assert((*mEntities)[i].Is(Entity::TypeIdClass()));
			(*mEntities)[i].As<Entity>()->Update(worldState);
		}
	}




	Scope* Sector::Clone()
	{
		return new Sector(*this);
	}




	void Sector::InitializeAttributes()
	{
		mEntities = &Append("Entities");
		AddToPrescribedAttributes("Entities");
		AddExternalPrescribedAttribute("Name", &mName, 1);
	}




	void Sector::UpdatePrescribedAttributes()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		*Find("Entities") = *mEntities;
	}

}