#pragma once

#include "ActionList.h"
#include "IEventSubscriber.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	The Reaction class is an interface that derives from ActionList
	*			and the EventSubscriber interface. It basically ties the event
	*			system to the rest of the game engine.
	*/
	class Reaction : public ActionList, public IEventSubscriber
	{

		RTTI_DECLARATIONS(Reaction, ActionList)

	public:

		/**
		*	@brief	Parameterized constructor for the Reaction class.
		*	@param	name the name of the reaction
		*/
		explicit Reaction(const std::string& name);

		/**
		*	@brief	The copy constructor for the Reaction class
		*	@param	other the Reaction to be copied
		*/
		Reaction(const Reaction& other);

		/**
		*	@brief	Move constructor for Reaction. Calls the move
		*			constructor of parent class.
		*	@param	other the Reaction being moved
		*/
		Reaction(Reaction&& other);

		/**
		*	@brief	The copy assignment operator for the Reaction class
		*	@param	other the Reaction to be copied
		*	@return	Reaction reference
		*/
		Reaction& operator=(const Reaction& other);

		/**
		*	@brief	The move assignment operator for Reaction. Calls
		*			the move assignment operator of parent class.
		*	@param	other the Reaction to be moved
		*	@return	Reaction reference
		*/
		Reaction& operator=(Reaction&& other);

		/**
		*	@brief	The destructor is defaulted.
		*/
		~Reaction() = default;

	private:

	};


}