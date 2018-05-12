#pragma once

#include "ActionList.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The ActionListIf class derives from the ActionList class
	*			and is a specialized ActionList, in that it allows us to
	*			simulate an 'if' clause through script (JSON).
	*/
	class ActionListIf final : public ActionList
	{

		RTTI_DECLARATIONS(ActionListIf, ActionList)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit ActionListIf(const std::string& name = "");
		
		/**
		*	@brief	The copy constructor copies the attributes of the ActionListIf to be copied
		*			and creates a new ActionListIf
		*	@param	other the ActionListIf to be copied
		*/
		ActionListIf(const ActionListIf& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionListIf be moved and
		*			creates a new ActionListIf, leaving the other ActionListIf in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionListIf to be moved
		*/
		ActionListIf(ActionListIf&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionListIf to be copied
		*	@param	other the ActionListIf to be copied
		*	@return	reference to the result ActionListIf
		*/
		ActionListIf& operator=(const ActionListIf& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionListIf to be moved
		*	@param	other the ActionListIf to be moved
		*	@return	reference to the result ActionListIf
		*/
		ActionListIf& operator=(ActionListIf&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~ActionListIf() = default;

		/**
		*	@brief	Method to create an action based on the condition
		*	@param	actionClassName class name of the action
		*	@param	actionInstanceName instance name of the action
		*	@param	branchName name of branch that contains the name of the action to be created
		*	@return	reference to the created action
		*/
		Action& CreateAction(const std::string& actionClassName, const std::string& actionInstanceName, const std::string& branchName);

		/**
		*	@brief	Calls update on the action that is in the appropriate branch based on the condition
		*	@param	worldState the WorldState object reference
		*/
		void Update(WorldState& worldState);

		/**
		*	@brief	Method to return a clone of the current ActionListIf object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionListIf.
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

		std::int32_t mCondition;		/**<	integer representing the condition	*/

		Scope* mThen;					/**<	Scope pointer to the then branch	*/
		Scope* mElse;					/**<	Scope pointer to the else branch	*/

	};

	ConcreteFactory(ActionListIf, Action)

}