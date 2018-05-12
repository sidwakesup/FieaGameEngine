#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Entity)


	Entity::Entity(const std::string& name) : mName(name)
	{
		InitializeAttributes();
	}




	Entity::Entity(const Entity& other) : Attributed::Attributed(other), mName(other.mName), mActions(other.mActions)
	{
		UpdatePrescribedAttributes();
	}




	Entity::Entity(Entity&& other) : Attributed::Attributed(std::move(other)), mName(std::move(other.mName)), mActions(std::move(other.mActions))
	{
		UpdatePrescribedAttributes();
	}




	Entity& Entity::operator=(const Entity& other)
	{
		if (this != &other)
		{
			Attributed::operator=(other);
			mName = other.mName;
			mActions = other.mActions;
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	Entity& Entity::operator=(Entity&& other)
	{
		if (this != &other)
		{
			Attributed::operator=(std::move(other));
			mName = std::move(other.mName);
			mActions = std::move(other.mActions);
			UpdatePrescribedAttributes();
		}

		return *this;
	}




	const std::string& Entity::Name() const
	{
		return mName;
	}




	void Entity::SetName(const std::string& name)
	{
		mName = name;
	}




	Sector const* Entity::GetSector() const
	{
		assert(GetParent() != nullptr);
		assert(GetParent()->Is(Sector::TypeIdClass()));
		return GetParent()->As<Sector>();
	}




	const Datum* Entity::Actions() const
	{
		return Find("Actions");
	}




	Action& Entity::CreateAction(const std::string& actionClassName, const std::string& actionInstanceName)
	{
		Action* action = (Factory<Action>::Create(actionClassName))->As<Action>();
		if (action == nullptr)
		{
			throw std::exception("Unable to create action!");
		}
		action->SetName(actionInstanceName);
		Adopt(*action, "Actions");
		return *action;
	}




	void Entity::SetSector(Sector* sector)
	{
		if (GetParent() != nullptr || sector == nullptr)
		{
			GetParent()->OrphanChild(*this);
		}
		if (sector != nullptr)
		{
			sector->Adopt(*this, "Entities");
		}
	}




	void Entity::Update(WorldState& worldState)
	{
		worldState.CurrentEntity = this;

		mActions = Find("Actions");
		for (std::uint32_t i = 0; i < mActions->Size(); ++i)
		{
			assert((*mActions)[i].Is(Action::TypeIdClass()));
			(*mActions)[i].As<Action>()->Update(worldState);
		}
	}




	Scope* Entity::Clone()
	{
		return new Entity(*this);
	}




	void Entity::InitializeAttributes()
	{
		mActions = &Append("Actions");
		AddToPrescribedAttributes("Actions");
		AddExternalPrescribedAttribute("Name", &mName, 1);
	}




	void Entity::UpdatePrescribedAttributes()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		*Find("Actions") = *mActions;
	}

}