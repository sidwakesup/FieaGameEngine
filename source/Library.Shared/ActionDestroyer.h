#pragma once

#include "Vector.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	class Action;	//forward declaration for the Action class

	/**
	*	@brief	The ActionDestroyer class serves as a garbage collector for the Actions.
	*			On its update, it deletes all the actions that are pending kill.
	*/
	class ActionDestroyer final
	{

	public:

		/**
		*	@brief	The default constructor has no special functionality, and hence is defaulted.
		*/
		ActionDestroyer() = default;

		/**
		*	@brief	The copy constructor for this class is deleted.
		*/
		ActionDestroyer(const ActionDestroyer& other) = delete;

		/**
		*	@brief	The move constructor for this class is defaulted.
		*/
		ActionDestroyer(ActionDestroyer&& other) = default;

		/**
		*	@brief	The copy assignment operator is deleted.
		*/
		ActionDestroyer& operator=(const ActionDestroyer& other) = delete;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		ActionDestroyer& operator=(ActionDestroyer&& other) = default;

		/**
		*	@brief	The destructor for this class is defaulted.
		*/
		~ActionDestroyer() = default;

		/**
		*	@brief	Static method to add an action to the list of actions that are marked for destroy.
		*	@param	actionToBeDestroyed pointer to the action to be destroyed.
		*/
		static void AddToListOfActionsToBeDestroyed(Action* actionToBeDestroyed);

		/**
		*	@brief	Static method that actually destroys the actions that are marked for delete.
		*/
		static void Cleanup();


		static Vector<Action*> mActionsToBeDestroyed;		/**<	static vector of pointers to actions that are marked for destruction	*/

	};

}