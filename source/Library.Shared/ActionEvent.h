#pragma once

#include "Action.h"
#include "Factory.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	The ActionEvent class derives from the Action interface.
	*			This Action is used to create and enqueue an event on 
	*			its update.
	*/
	class ActionEvent final : public Action
	{

		RTTI_DECLARATIONS(ActionEvent, Action)

	public:

		/**
		*	@brief	Parameterized constructor for ActionEvent
		*	@param	name name of the action
		*	@param	subType subType of the events that this action can create
		*	@param	delay the delay after which the spawned event will expire
		*/
		ActionEvent(const std::string& name = "", const std::string& subType = "", const std::int32_t& delay = 0);

		/**
		*	@brief	The copy constructor copies the attributes of the ActionEvent to be copied
		*			and creates a new ActionEvent
		*	@param	other the ActionEvent to be copied
		*/
		ActionEvent(const ActionEvent& other);

		/**
		*	@brief	The move constructor moves the attributes of the ActionEvent to be moved and
		*			creates a new ActionEvent, leaving the other ActionEvent in a potentially
		*			unusable state, as intended.
		*	@param	other the ActionEvent to be moved
		*/
		ActionEvent(ActionEvent&& other);

		/**
		*	@brief	The copy assignment operator copies the attributes of the ActionEvent to be copied
		*	@param	other the ActionEvent to be copied
		*	@return	reference to the result ActionEvent
		*/
		ActionEvent& operator=(const ActionEvent& other);

		/**
		*	@brief	The move assignment operator moves the attributes of the ActionEvent to be moved
		*	@param	other the ActionEvent to be moved
		*	@return	reference to the result ActionEvent
		*/
		ActionEvent& operator=(ActionEvent&& other);

		/**
		*	@brief	The destructor is defaulted
		*/
		~ActionEvent() = default;

		/**
		*	@brief	Method that gives the subtype.
		*	@return	string that represents the subtype
		*/
		std::string GetSubType() const;

		/**
		*	@brief	Method that sets the subtype.
		*	@param	subType string that represents the subtype
		*/
		void SetSubType(const std::string& subType);

		/**
		*	@brief	Method that gives the delay.
		*	@return	int that represents the delay
		*/
		std::int32_t GetDelay() const;

		/**
		*	@brief	Method that sets the delay.
		*	@param	subType int that represents the delay
		*/
		void SetDelay(const std::int32_t& delay);

		/**
		*	@brief	The update method creates an event of type
		*			event message attributed with a specific subtype,
		*			gives it a delay, and appends to it all the auxiliary
		*			attributes. It then enqueues this event to the event queue
		*			that belongs to the world
		*	@param	worldState the worldState
		*/
		void Update(WorldState& worldState) override;

		/**
		*	@brief	Method to return a clone of the current ActionEvent object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ActionEvent.
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

		std::string mSubType;	/**<	String representing the subtype	*/
		std::int32_t mDelay;	/**<	Int representing the delay	*/

	};

	
	ConcreteFactory(ActionEvent, Action)

}