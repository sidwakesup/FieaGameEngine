#pragma once

#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	class Entity;	//forward declaration of Entity class.

	/**
	*	@brief	The Action class derives from the Attributed interface
	*			and represents all the verbs that take place in the
	*			world created by the game engine. Each action is
	*			associated with an entity and performs some functionality
	*			pertaining to that.
	*/
	class Action : public Attributed
	{

		RTTI_DECLARATIONS(Action, Attributed)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit Action(const std::string& name = "");

		/**
		*	@brief	The copy constructor copies the attributes of the Action to be copied
		*			and creates a new Action
		*	@param	other the Action to be copied
		*/
		Action(const Action& other);

		/**
		*	@brief	The move constructor moves the attributes of the Action to be moved and
		*			creates a new Action, leaving the other Action in a potentially 
		*			unusable state, as intended.
		*	@param	other the Action to be moved
		*/
		Action(Action&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the Action to be copied
		*	@param	other the Action to be copied
		*	@return	reference to the result Action
		*/
		Action& operator=(const Action& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the Action to be moved
		*	@param	other the Action to be moved
		*	@return	reference to the result Action
		*/
		Action& operator=(Action&& other);

		/**
		*	@brief	The destructor is defaulted.
		*/
		virtual ~Action() = default;

		/**
		*	@brief	Method that retrieves the name of the action
		*	@return	string that represents the name of the action
		*/
		const std::string& Name() const;

		/**
		*	@brief	Method that sets the name of the action
		*	@param	name the name of the action
		*/
		void SetName(const std::string& name);

		/**
		*	@brief	Pure virtual method that must be overriden by
		*			derived action classes.
		*	@param	worldState reference to the WorldState object
		*/
		virtual void Update(WorldState& worldState) = 0;

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

		std::string mName;		/**<	Name of the action	*/

	};

}