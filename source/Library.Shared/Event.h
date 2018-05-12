#pragma once

#include "IEventPublisher.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The Event class is a templated class that derives from the EventPublisher interface.
	*			The Event system implements the observer pattern and each event has a set of subscribers.
	*			Events carry a templated data 'payload' and can be delivered immediately, or queued for
	*			future delivery.
	*/
	template<typename Payload>
	class Event : public IEventPublisher
	{

		RTTI_DECLARATIONS(Event<Payload>, IEventPublisher)

	public:

		/**
		*	@brief	Parameterized constructor that takes in the payload and a list of subscribers
		*	@param	payload the data that this event contains specific to the template
		*	@param	subscribers the list of subscribers that will subscribe to this event
		*/
		Event(const Payload& payload = Payload(), const Vector<IEventSubscriber*>& subscribers = Vector<IEventSubscriber*>());

		/**
		*	@brief	Copy constructor for the Event class is defaulted
		*	@param	other the event to be copied
		*/
		Event(const Event& other) = default;

		/**
		*	@brief	Move constructor for Event class is defaulted
		*	@param	other the event to be moved
		*/
		Event(Event&& other) = default;

		/**
		*	@brief	Copy assignment operator for Event class is defaulted
		*	@param	other the event to be copied
		*/
		Event& operator=(const Event& other) = default;

		/**
		*	@brief	Move assignment operator for event class is defaulted
		*	@param	other the event to be moved
		*/
		Event& operator=(Event&& other) = default;

		/**
		*	@brief	Destructor for the Event class is defaulted.
		*/
		~Event() = default;

		/**
		*	@brief	Static method to add a subscriber to the list of subscribers for this event type
		*	@param	eventSubscriber reference to the subscriber
		*/
		static void Subscribe(IEventSubscriber& eventSubscriber);

		/**
		*	@brief	Static method to remove a subscriber from the list of subscribers for this event type
		*	@param	eventSubscriber reference to the subscriber
		*/
		static void Unsubscribe(IEventSubscriber& eventSubscriber);

		/**
		*	@brief	Static method to remove all subscribers for this event type
		*/
		static void UnsubscribeAll();

		/**
		*	@brief	Method to obtain the payload of this event
		*	@return	reference to the Payload object contained in this event
		*/
		const Payload& Message() const;

	private:

		static std::mutex mMutex;							/**<	static mutex for the templated event class	*/

		Payload mPayload;									/**<	the payload object	*/
		
		static Vector<IEventSubscriber*> mSubscribers;		/**<	static vector of pointers to event subscribers	*/

	};

}


#include "Event.inl"