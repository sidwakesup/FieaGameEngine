#pragma once

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	class IEventPublisher;		//forward declaration for the event publisher class.
	
	/**
	*	@brief	The Event Subscriber is the class that gets notified whenever an event is
	*			fired. This is the abstract base class that actual subscribers will derive
	*			from. It inherits from RTTI.
	*/
	class IEventSubscriber
	{

	public:

		/**
		*	@brief The default constructor is defaulted.
		*/
		IEventSubscriber() = default;

		/**
		*	@brief The copy constructor is defaulted.
		*/
		IEventSubscriber(const IEventSubscriber& other) = default;

		/**
		*	@brief The move constructor is defaulted.
		*/
		IEventSubscriber(IEventSubscriber&& other) = default;

		/**
		*	@brief The copy assignment operator is defaulted.
		*/
		IEventSubscriber& operator=(const IEventSubscriber& other) = default;

		/**
		*	@brief The move assignment operator is defaulted.
		*/
		IEventSubscriber& operator=(IEventSubscriber&& other) = default;

		/**
		*	@brief The destructor is defaulted.
		*/
		virtual ~IEventSubscriber() = default;

		/**
		*	@brief	The Notify method is a pure virtual method that must be implemented by
		*			derived subscriber classes. It specifies what the subscriber does when
		*			an event is published.
		*	@param	publisher reference to the event being published
		*/
		virtual void Notify(const IEventPublisher& publisher) = 0;

	};

}