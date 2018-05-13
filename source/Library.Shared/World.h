#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Sector.h"
#include "EventQueue.h"
#include "ReactionAttributed.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	World class is a container for an interactive simulation.
	*			It defines a global scope, contains a list of Sectors and
	*			an event queue. It also contains the WorldState. It derives
	*			from the Attributed interface.
	*/
	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the world
		*	@param	name the name of the world
		*/
		World(const std::string& name = "");

		/**
		*	@brief	The copy constructor copies the attributes of the World to be copied
		*			and creates a new World
		*	@param	other the World to be copied
		*/
		World(const World& other);

		/**
		*	@brief	The move constructor moves the attributes of the World to be moved and
		*			creates a new World, leaving the other World in a potentially
		*			unusable state, as intended.
		*	@param	other the World to be moved
		*/
		World(World&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the World to be copied
		*	@param	other the World to be copied
		*	@return	reference to the result World
		*/
		World& operator=(const World& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the World to be moved
		*	@param	other the World to be moved
		*	@return	reference to the result World
		*/
		World& operator=(World&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~World() = default;

		/**
		*	@brief	Method that retrieves the name of the world
		*	@return	string that represents the name of the world
		*/
		const std::string& Name() const;

		/**
		*	@brief	Method that sets the name of the world
		*	@param	name the name of the world
		*/
		void SetName(const std::string& name);

		/**
		*	@brief	Method that retrieves all the sectors contained in this world
		*	@return	a const datum pointer pointing to the list of sectors
		*/
		const Datum* Sectors() const;

		/**
		*	@brief	Method that retrieves all the reactions contained in this world
		*	@return	a const datum pointer pointing to the list of reactions
		*/
		const Datum* Reactions() const;

		/**
		*	@brief	Method to get the world state
		*	@return	WorldState reference
		*/
		WorldState& GetWorldState();

		/**
		*	@brief	Method to get the event queue
		*	@return	EventQueue reference
		*/
		EventQueue& GetEventQueue();

		/**
		*	@brief	Method to create a new sector that will be contained in this world
		*	@param	sectorName the name of the sector to be created
		*	@return	reference to the created sector
		*/
		Sector& CreateSector(const std::string& sectorName);

		/**
		*	@brief	Method to create a new reaction that will be contained in this world
		*	@param	reactionClassName name of the reaction class to be created
		*	@param	reactionInstanceName name of the instance of the created reaction
		*	@return	reference to the created reaction
		*/
		Reaction& CreateReaction(const std::string& reactionClassName, const std::string& reactionInstanceName);

		/**
		*	@brief	The update method calls the update method in each of its contained sectors
		*/
		void Update();

		/**
		*	@brief	Method to return a clone of the current World object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created World.
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

		std::string mName;			/**<	The name of the world	*/

		Datum* mSectors;			/**<	Datum pointer pointing to the datum containing the list of sectors	*/
		Datum* mReactions;			/**<	Datum pointer pointing to the datum containing the list of reactions	*/

		WorldState mWorldState;		/**<	The world state for this world.	*/

		EventQueue mEventQueue;		/**<	The event queue for this world	*/

	};

}