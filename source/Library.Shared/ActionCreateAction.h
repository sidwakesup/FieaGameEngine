#pragma once

#include "Action.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	ActionCreateAction is an Action class that derives from the base
	*			Action interface. This Action is meant to create a new Action on
	*			its Update.
	*/
	class ActionCreateAction final : public Action
	{

		RTTI_DECLARATIONS(ActionCreateAction, Action)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit ActionCreateAction(const std::string& name = "");
		
		/**
		*	@brief	The copy constructor copies the attributes of the ActionCreateAction to be copied
		*			and creates a new ActionCreateAction
		*	@param	other the ActionCreateAction to be copied
		*/
		ActionCreateAction(const ActionCreateAction& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionCreateAction to be moved and
		*			creates a new ActionCreateAction, leaving the other ActionCreateAction in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionCreateAction to be moved
		*/
		ActionCreateAction(ActionCreateAction&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionCreateAction to be copied
		*	@param	other the ActionCreateAction to be copied
		*	@return	reference to the result ActionCreateAction
		*/
		ActionCreateAction& operator=(const ActionCreateAction& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionCreateAction to be moved
		*	@param	other the ActionCreateAction to be moved
		*	@return	reference to the result ActionCreateAction
		*/
		ActionCreateAction& operator=(ActionCreateAction&& other);

		/**
		*	@brief	The destructor is defaulted.
		*/
		~ActionCreateAction() = default;

		/**
		*	@brief	Creates an action from the class name and instance name
		*/
		void Update(WorldState& worldState) override;

		/**
		*	@brief	Method to return a clone of the current ActionCreateAction object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionCreateAction.
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

		std::string mClassName;				/**<	class name of the action to be created	*/
		std::string mInstanceName;			/**<	instance name of the action to be created	*/

	};



	ConcreteFactory(ActionCreateAction, Action)
		
}