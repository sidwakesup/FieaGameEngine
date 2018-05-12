#pragma once

#include "Action.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	ActionDestroyAction is an Action class that derives from the base
	*			Action interface. This Action is meant to destroy an Action on
	*			its Update.
	*/
	class ActionDestroyAction final : public Action
	{

		RTTI_DECLARATIONS(ActionDestroyAction, Action)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit ActionDestroyAction(const std::string& name = "");
		
		/**
		*	@brief	The copy constructor copies the attributes of the ActionDestroyAction to be copied
		*			and creates a new ActionDestroyAction
		*	@param	other the ActionDestroyAction to be copied
		*/
		ActionDestroyAction(const ActionDestroyAction& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionDestroyAction to be moved and
		*			creates a new ActionDestroyAction, leaving the other ActionDestroyAction in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionDestroyAction to be moved
		*/
		ActionDestroyAction(ActionDestroyAction&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionDestroyAction to be copied
		*	@param	other the ActionDestroyAction to be copied
		*	@return	reference to the result ActionDestroyAction
		*/
		ActionDestroyAction& operator=(const ActionDestroyAction& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionDestroyAction to be moved
		*	@param	other the ActionDestroyAction to be moved
		*	@return	reference to the result ActionDestroyAction
		*/
		ActionDestroyAction& operator=(ActionDestroyAction&& other);

		/**
		*	@brief	The destructor is defaulted.
		*/
		~ActionDestroyAction() = default;

		/**
		*	@brief	Marks an action for delete from the class name and instance name
		*/
		void Update(WorldState& worldState) override;

		/**
		*	@brief	Method to return a clone of the current ActionDestroyAction object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionDestroyAction.
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

		std::string mInstanceName;			/**<	Instance name of the class to be destroyed	*/

	};

	ConcreteFactory(ActionDestroyAction, Action)

}