#pragma once

#include "Reaction.h"
#include "Factory.h"
#include "EventMessageAttributed.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The ReactionAttributed class derives from the Reaction interface. It is used
	*			to register to events of type EventMessageAttributed. It has its own associated
	*			factory.
	*/
	class ReactionAttributed : public Reaction
	{

		RTTI_DECLARATIONS(ReactionAttributed, Reaction)

	public:

		/**
		*	@brief	Parameterized constructor for the ReactionAttributed class. It also
		*			subscribes to events of type eventMessageAttributed.
		*	@param	name the name of the reaction
		*	@param	subType the subType that this ReactionAttributed can subscribe to
		*/
		explicit ReactionAttributed(const std::string& name = "", const std::string& subType = "");

		/**
		*	@brief	The copy constructor for the ReactionAttributed class.
		*	@param	other the ReactionAttributed to be copied
		*/
		ReactionAttributed(const ReactionAttributed& other);

		/**
		*	@brief	Move constructor for Reaction. Calls the move
		*			constructor of parent class.
		*	@param	other the Reaction being moved
		*/
		ReactionAttributed(ReactionAttributed&& other);

		/**
		*	@brief	The copy assignent operator for the ReactionAttributed class.
		*	@param	other the ReactionAttributed to be copied
		*	@return ReactionAttributed reference
		*/
		ReactionAttributed& operator=(const ReactionAttributed& other);

		/**
		*	@brief	The move assignment operator for Reaction. Calls
		*			the move assignment operator of parent class.
		*	@param	other the Reaction to be moved
		*	@return	ReactionAttributed reference
		*/
		ReactionAttributed& operator=(ReactionAttributed&& other);

		/**
		*	@brief	Destructor for the ReactionAttributed class.
		*			It unsubscribes from events of type EventMessageAttributed.
		*/
		~ReactionAttributed();

		/**
		*	@brief	Method that gives the subtype that this reaction subscribes to.
		*	@return	string that represents the subtype
		*/
		std::string GetSubType() const;

		/**
		*	@brief	Method that sets the subtype that this reaction subscribes to.
		*	@param	subType string that represents the subtype
		*/
		void SetSubType(const std::string& subType);

		/**
		*	@brief	Simply calls ActionList::Update
		*/
		virtual void Update(WorldState& worldState) override;

		/**
		*	@brief	Method to return a clone of the current ReactionAttributed object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created ReactionAttributed.
		*/
		virtual Scope* Clone() override;

		/**
		*	@brief	Method that is called when the corresponding event is raised.
		*			Copies over all auxiliary attributes from the payload of the event
		*			and then calls Update.
		*	@param	publisher the event that was raised.
		*/
		virtual void Notify(const IEventPublisher& publisher) override;

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

		std::string mSubType;		/**<	String that represents the SubType	*/

	};


	ConcreteFactory(ReactionAttributed, Reaction)

}