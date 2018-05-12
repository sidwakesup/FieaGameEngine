#pragma once

#include "IEventPublisher.h"
#include "GameTime.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The Event Queue class handles delivering events and thus,
	*			notifying the subscribers of those events. It maintains a queue
	*			of events and discards expired events after delivering them.
	*/
	class EventQueue
	{
	public:

		/**
		*	@brief	The default constructor has no special functionality, and hence,
		*			is defaulted.
		*/
		EventQueue() = default;

		/**
		*	@brief	The copy constructor is defaulted.
		*/
		EventQueue(const EventQueue& other) = default;

		/**
		*	@brief	The move constructor is defaulted.
		*/
		EventQueue(EventQueue&& other) = default;

		/**
		*	@brief	The copy assignment operator is defaulted.
		*/
		EventQueue& operator=(const EventQueue& other) = default;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		EventQueue& operator=(EventQueue&& other) = default;

		/**
		*	@brief	The destructor is defaulted.
		*/
		~EventQueue() = default;

		/**
		*	@brief	Method to add an event to the queue.
		*	@param	eventPublisher the event to be added
		*	@param	gameTime the time at which the event is enqueued
		*	@param	delay the time after being enqueued that the event will expire
		*/
		void Enqueue(const std::shared_ptr<IEventPublisher>& eventPublisher, const GameTime& gameTime, std::chrono::milliseconds delay = std::chrono::duration_values<std::chrono::milliseconds>::zero());

		/**
		*	@brief	Method to immediately send an event irrespective of its expiry status
		*	@param	eventToSend reference to the event to be sent
		*/
		void Send(const std::shared_ptr<IEventPublisher>& eventToSend);
		
		/**
		*	@brief	Method to update the queue, ie, deliver all events that have expired
		*			and then update the queue by discarding expired/delivered events.
		*	@param	gameTime GameTime object to obtain current time
		*/
		void Update(const GameTime& gameTime);

		/**
		*	@brief	Method to check whether the queue is empty
		*	@return	bool that indicates whether the queue is empty
		*/
		bool IsEmpty() const;

		/**
		*	@brief	Method to obtain the size of the queue
		*	@return	int representing the size of the queue
		*/
		std::uint32_t Size() const;

	private:

		mutable std::mutex mMutex;											/**<	mutex for the event queue	*/

		std::vector<std::shared_ptr<IEventPublisher>> mQueue;				/**<	vector of event publishers that represents the event queue.	*/

		std::vector<std::shared_ptr<IEventPublisher>> mExpiredEvents;		/**<	vector of expired events that need to be delivered	*/

	};

}