#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Entity.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	class World;		//forward declaration for the World class.

	/**
	*	@brief	This class facilitates segmenting the world into chunks, useful for
	*			managing assets. This lets us cluster the data together so that we can
	*			load and unload the chunks as a module.
	*/
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the sector
		*	@param	name the name of the sector
		*/
		explicit Sector(const std::string& name = "");

		/**
		*	@brief	The copy constructor copies the attributes of the Sector to be copied
		*			and creates a new Sector
		*	@param	other the Sector to be copied
		*/
		Sector(const Sector& other);

		/**
		*	@brief	The move constructor moves the attributes of the Sector to be moved and
		*			creates a new Sector, leaving the other Sector in a potentially
		*			unusable state, as intended.
		*	@param	other the Sector to be moved
		*/
		Sector(Sector&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the Sector to be copied
		*	@param	other the Sector to be copied
		*	@return	reference to the result Sector
		*/
		Sector& operator=(const Sector& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the Sector to be moved
		*	@param	other the Sector to be moved
		*	@return	reference to the result Sector
		*/
		Sector& operator=(Sector&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~Sector() = default;

		/**
		*	@brief	Method that retrieves the name of the sector
		*	@return	string that represents the name of the sector
		*/
		const std::string& Name() const;

		/**
		*	@brief	Method that sets the name of the sector
		*	@param	name the name of the sector
		*/
		void SetName(const std::string& name);

		/**
		*	@brief	Method that retrieves all the entities contained in this sector
		*	@return	a datum pointer pointing to the list of entities
		*/
		const Datum* Entities() const;

		/**
		*	@brief	Method to create a new entity that will be contained in this sector
		*	@param	entityClassName the name of the entity class to be created
		*	@param	entityInstanceName name of the created entity instance
		*	@return	reference to the created entity
		*/
		Entity& CreateEntity(const std::string& entityClassName, const std::string& entityInstanceName);

		/**
		*	@brief	Method to change the world that contains this sector.
		*	@param	world the new world that will contain this sector
		*/
		void SetWorld(World* world);

		/**
		*	@brief	Method that gets the world that contains this sector.
		*	@return	pointer to the world that contains this sector.
		*/
		World const* GetWorld() const;

		/**
		*	@brief	The update method calls the update method in each of its contained entities
		*	@param	worldState the WorldState object reference
		*/
		void Update(WorldState& worldState);

		/**
		*	@brief	Method to return a clone of the current Sector object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created Sector.
		*/
		virtual Scope* Clone() override;

		/**
		*	@brief	Method to initialize the attributes of the class.
		*			Overriden from the Attributed class.
		*/
		void InitializeAttributes() override;

		/**
		*	@brief	Method to update the list of prescribed attributes whenever
		*			the list is reinitialized. Overriden from the Attributed class.
		*/
		void UpdatePrescribedAttributes() override;

	private:

		std::string mName;			/**<	The name of the sector.	*/

		Datum* mEntities;			/**<	Datum pointer pointing to the datum containing the list of entities	*/

	};

}