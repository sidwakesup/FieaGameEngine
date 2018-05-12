#pragma once

#include "Action.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	The ActionPrint class derives from the Action interface
	*			and is used to print a string to the console on its update.
	*/
	class ActionPrint final : public Action
	{

		RTTI_DECLARATIONS(ActionPrint, Action)
		
	public:

		/**
		*	@brief	Parameterized constructor that takes in the name of the action
		*	@param	name the name of the action
		*/
		explicit ActionPrint(const std::string& name = "");
		
		/**
		*	@brief	The copy constructor copies the attributes of the ActionPrint to be copied
		*			and creates a new ActionPrint
		*	@param	other the ActionPrint to be copied
		*/
		ActionPrint(const ActionPrint& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionPrint to be moved and
		*			creates a new ActionPrint, leaving the other ActionPrint in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionPrint to be moved
		*/
		ActionPrint(ActionPrint&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionPrint to be copied
		*	@param	other the ActionPrint to be copied
		*	@return	reference to the result ActionPrint
		*/
		ActionPrint& operator=(const ActionPrint& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionPrint to be moved
		*	@param	other the ActionPrint to be moved
		*	@return	reference to the result ActionPrint
		*/
		ActionPrint& operator=(ActionPrint&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~ActionPrint() = default;

		/**
		*	@brief	The update method outputs the mLog as a debug string
		*	@param	worldState the WorldState object reference
		*/
		void Update(WorldState& worldState) override;

		/**
		*	@brief	Method to return a clone of the current ActionPrint object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionPrint.
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

		std::string mLog;		/**<	The string that is to be printed	*/

	};

	ConcreteFactory(ActionPrint, Action)

}