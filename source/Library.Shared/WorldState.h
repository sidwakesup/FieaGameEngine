#pragma once

#include "GameTime.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The WorldState class is used to keep track of the current
	*			context that we are in. It is especially useful in update
	*			loops to avoid lookup times.
	*/
	class WorldState final
	{
	public:

		/**
		*	@brief	The default constructor initializes all the pointer members to nullptr
		*/
		WorldState();

		/**
		*	@brief	The copy constructor is deleted.
		*/
		WorldState(const WorldState& other) = delete;

		/**
		*	@brief	The move constructor is defaulted.
		*/
		WorldState(WorldState&& other) = default;

		/**
		*	@brief	The copy assignment operator is deleted.
		*/
		WorldState& operator=(const WorldState& other) = delete;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		WorldState& operator=(WorldState&& other) = default;

		/**
		*	@brief	The destructor is defaulted.
		*/
		~WorldState() = default;

		/**
		*	@brief	Method that returns the game time.
		*	@return	Game time object
		*/
		const GameTime& GetGameTime() const;

		/**
		*	@brief	Method to override the current game time object
		*	@param	newGameTimeObject the new game time object that will
		*			override the current game time object
		*/
		void SetGameTime(const GameTime& newGameTimeObject);


		GameTime mGameTime;					/**<	The game time object associated with this world state.	*/

		class World* CurrentWorld;			/**<	Pointer to the current world.	*/
		class Sector* CurrentSector;		/**<	Pointer to the current sector.	*/
		class Entity* CurrentEntity;		/**<	Pointer to the current entity.	*/
		class Action* CurrentAction;		/**<	Pointer to the current action.	*/

	};

}