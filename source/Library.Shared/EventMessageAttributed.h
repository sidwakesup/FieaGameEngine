#pragma once

#include "Attributed.h"
#include "Event.h"
#include "World.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	The EventMessageAttributed class derives from the Attributed
	*			interface. It serves as a payload for the events that are
	*			subscribed to by the Reactions defined in the world.
	*/
	class EventMessageAttributed : public Attributed
	{

		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)

	public:

		/**
		*	@brief	Parameterized constructor for the EventMessageAttributed class.
		*	@param	subType the subType that this ReactionAttributed can subscribe to
		*	@param	world pointer to the world
		*/
		EventMessageAttributed(const std::string& subType = "", World* world = nullptr);

		/**
		*	@brief	Copy constructor for the EventMessageAttributed class
		*	@param	other the EventMessageAttributed to be copied
		*/
		EventMessageAttributed(const EventMessageAttributed& other);

		/**
		*	@brief	Move constructor for EventMessageAttributed class
		*	@param	other the EventMessageAttributed to be moved
		*/
		EventMessageAttributed(EventMessageAttributed&& other);

		/**
		*	@brief	Copy assignment operator for EventMessageAttributed class
		*	@param	other the EventMessageAttributed to be copied
		*/
		EventMessageAttributed& operator=(const EventMessageAttributed& other);

		/**
		*	@brief	Move assignment operator for EventMessageAttributed class
		*	@param	other the EventMessageAttributed to be moved
		*/
		EventMessageAttributed& operator=(EventMessageAttributed&& other);

		/**
		*	@brief	The destructor is defaulted.
		*/
		~EventMessageAttributed() = default;

		/**
		*	@brief	Method to return a clone of the current EventMessageAttributed object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created EventMessageAttributed.
		*/
		Scope* Clone() override;

		/**
		*	@brief	Method that gives the subtype.
		*	@return	string that represents the subtype
		*/
		const std::string& GetSubType() const;

		/**
		*	@brief	Method that sets the subtype.
		*	@param	subType string that represents the subtype
		*/
		void SetSubType(const std::string& subType);

		/**
		*	@brief	Method that gives the world that contains this
		*	@return	world pointer
		*/
		World* GetWorld() const;

		/**
		*	@brief	Method to set the world pointer
		*	@param	world the pointer to the world
		*/
		void SetWorld(World* world);

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

		std::string mSubType;		/**<	String representing the subtype	*/
		World* mWorld;				/**<	pointer to the world	*/

	};

}