#pragma once

#include "Action.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The ActionList class derives from the Action class. It is
	*			implemented using the Composite pattern and thus, is an Action
	*			that serves as a collection of Actions.
	*/
	class ActionList : public Action
	{

		RTTI_DECLARATIONS(ActionList, Action)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit ActionList(const std::string& name = "");
		
		/**
		*	@brief	The copy constructor copies the attributes of the ActionList to be copied
		*			and creates a new ActionList
		*	@param	other the ActionList to be copied
		*/
		ActionList(const ActionList& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionList be moved and
		*			creates a new ActionList, leaving the other ActionList in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionList to be moved
		*/
		ActionList(ActionList&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionList to be copied
		*	@param	other the ActionList to be copied
		*	@return	reference to the result ActionList
		*/
		ActionList& operator=(const ActionList& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionList to be moved
		*	@param	other the ActionList to be moved
		*	@return	reference to the result ActionList
		*/
		ActionList& operator=(ActionList&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~ActionList() = default;

		/**
		*	@brief	Method to create an action
		*	@param	actionClassName class name of the action
		*	@param	actionInstanceName instance name of the action
		*	@return	reference to the created action
		*/
		Action& CreateAction(const std::string& actionClassName, const std::string& actionInstanceName);

		/**
		*	@brief	Method that returns the list of actions that are in this
		*			action list
		*	@return	Datum pointer corresponding to the actions
		*/
		const Datum* Actions() const;

		/**
		*	@brief	The update method calls the update method in each of its actions
		*	@param	worldState the WorldState object reference
		*/
		void Update(WorldState& worldState);

		/**
		*	@brief	Method to return a clone of the current ActionList object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionList.
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

		Datum* mActions;		/**<	Datum pointer pointing to the datum containing the list of actions.	*/

	};

	ConcreteFactory(ActionList, Action)

}