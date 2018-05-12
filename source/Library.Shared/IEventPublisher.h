#pragma once

#include "Vector.h"
#include "GameTime.h"
#include "IEventSubscriber.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{

	/**
	*	@brief	The EventPublisher is an interface that the templated Event class derives
	*			from. It is used to implement the observer pattern.
	*/
	class IEventPublisher : public RTTI
	{

		RTTI_DECLARATIONS(IEventPublisher, RTTI)

	public:

		/**
		*	@brief	Parameterized constructor that takes in a reference to a vector of event subscribers
		*	@param	subscriberList reference to a vector of pointers to event subscribers.
		*/
		explicit IEventPublisher(Vector<IEventSubscriber*>& subscriberList, std::mutex& mutex);
		
		/**
		*	@brief	The copy constructor is defaulted
		*/
		IEventPublisher(const IEventPublisher& other) = default;

		/**
		*	@brief	The move constructor is defaulted
		*/
		IEventPublisher(IEventPublisher&& other) = default;

		/**
		*	@brief	The copy assignment operator is defaulted
		*/
		IEventPublisher& operator=(const IEventPublisher& other) = default;

		/**
		*	@brief	The move assignment operator is defaulted
		*/
		IEventPublisher& operator=(IEventPublisher&& other) = default;

		/**
		*	@brief	The destructor is defaulted
		*/
		virtual ~IEventPublisher() = default;

		/**
		*	@brief	Method to set the time this event is enqueued and the delay after which it expires
		*	@param	timeEnqueued the time at which this event is enqueued
		*	@param	delay the time after which this event expires
		*/
		void SetTime(const std::chrono::high_resolution_clock::time_point& timeEnqueued, const std::chrono::milliseconds& delay = std::chrono::duration_values<std::chrono::milliseconds>::zero());

		/**
		*	@brief	Method to get the time at which this event was enqueued
		*	@return	the time point at which this event was enqueued
		*/
		const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;

		/**
		*	@brief	Method to get the delay in milliseconds
		*	@return	the delay in milliseconds
		*/
		const std::chrono::milliseconds& Delay() const;

		/**
		*	@brief	Method to check whether this event has expired
		*	@param	currentTime the time point that represents the current time
		*	@return	bool that indicates whether this event has expired
		*/
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const;

		/**
		*	@brief	Method that basically notifies all the subscribers of this event
		*/
		void Deliver();

		/**
		*	@brief	Method to obtain the pointer to the mutex
		*	@return	mutex pointer
		*/
		std::mutex* Mutex() const;

	protected:

		std::mutex* mMutexPointer;											/**<	mutex pointer for the event publisher class	*/

		std::chrono::high_resolution_clock::time_point mTimeEnqueued;		/**<	the time point at which this event is enqueued	*/

		std::chrono::milliseconds mDelay;									/**<	the delay after which this event expires	*/

		Vector<IEventSubscriber*>* mReferenceToSubscriberList;				/**<	reference to the vector of pointers to subscribers of this event	*/

	};

}