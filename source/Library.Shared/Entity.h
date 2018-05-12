#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Action.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	class Sector;		//forward declaration to the Sector class.

	/**
	*	@brief	Entity is just another wrapper for an attributed scope, with the difference
	*			that entity objects automatically populate their tables based on information
	*			known at compile time.
	*/
	class Entity : public Attributed
	{

		RTTI_DECLARATIONS(Entity, Attributed)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the entity
		*	@param	name the name of the entity
		*/
		explicit Entity(const std::string& name = "");

		/**
		*	@brief	The copy constructor copies the attributes of the Entity to be copied
		*			and creates a new Entity
		*	@param	other the Entity to be copied
		*/
		Entity(const Entity& other);

		/**
		*	@brief	The move constructor moves the attributes of the Entity to be moved and
		*			creates a new Entity, leaving the other Entity in a potentially
		*			unusable state, as intended.
		*	@param	other the Entity to be moved
		*/
		Entity(Entity&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the Entity to be copied
		*	@param	other the Entity to be copied
		*	@return	reference to the result Entity
		*/
		Entity& operator=(const Entity& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the Entity to be moved
		*	@param	other the Entity to be moved
		*	@return	reference to the result Entity
		*/
		Entity& operator=(Entity&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		virtual ~Entity() = default;

		/**
		*	@brief	Method that retrieves the name of the entity
		*	@return	string that represents the name of the entity
		*/
		const std::string& Name() const;

		/**
		*	@brief	Method that sets the name of the entity
		*	@param	name the name of the entity
		*/
		void SetName(const std::string& name);

		/**
		*	@brief	Method that returns the list of actions that are in this
		*			entity
		*	@return	Datum pointer corresponding to the actions
		*/
		const Datum* Actions() const;

		/**
		*	@brief	Method to create an action
		*	@param	actionClassName class name of the action
		*	@param	actionInstanceName instance name of the action
		*	@return	reference to the created action
		*/
		Action& CreateAction(const std::string& actionClassName, const std::string& actionInstanceName);

		/**
		*	@brief	Method that gets the sector that contains this entity.
		*	@return	pointer to the sector that contains this entity.
		*/
		Sector const* GetSector() const;

		/**
		*	@brief	Method to change the sector that contains this entity.
		*	@param	sector the new world that will contain this entity
		*/
		void SetSector(Sector* sector);

		/**
		*	@brief	The update method calls the update method in each of its actions
		*	@param	worldState refernce to the WorldState object
		*/
		void Update(WorldState& worldState);

		/**
		*	@brief	Method to return a clone of the current Entity object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created Entity.
		*/
		virtual Scope* Clone() override;

		/**
		*	@brief	Method to initialize the attributes of the class.
		*			Overriden from the Attributed class.
		*/
		virtual void InitializeAttributes() override;

		/**
		*	@brief	Method to update the list of prescribed attributes whenever
		*			the list is reinitialized. Overriden from the Attributed class.
		*/
		virtual void UpdatePrescribedAttributes() override;

	private:

		std::string mName;		/**<	The name of the entity	*/

		Datum* mActions;		/**<	Datum pointer that points to the datum containing the list of actions	*/

	};



	ConcreteFactory(Entity, Entity)

}