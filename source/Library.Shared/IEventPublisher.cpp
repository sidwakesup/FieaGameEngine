#include "pch.h"
#include "IEventPublisher.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(IEventPublisher)


	IEventPublisher::IEventPublisher(Vector<IEventSubscriber*>& subscriberList, std::mutex& mutex) : mReferenceToSubscriberList(&subscriberList), mMutexPointer(&mutex)
	{

	}
		
		
		
		
	void IEventPublisher::SetTime(const std::chrono::high_resolution_clock::time_point& timeEnqueued, const std::chrono::milliseconds& delay)
	{
		std::lock_guard<std::mutex> lock(*mMutexPointer);

		mTimeEnqueued = timeEnqueued;
		mDelay = delay;
	}




	const std::chrono::high_resolution_clock::time_point& IEventPublisher::TimeEnqueued() const
	{
		std::lock_guard<std::mutex> lock(*mMutexPointer);

		return mTimeEnqueued;
	}




	const std::chrono::milliseconds& IEventPublisher::Delay() const
	{
		std::lock_guard<std::mutex> lock(*mMutexPointer);

		return mDelay;
	}




	bool IEventPublisher::IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const
	{
		std::lock_guard<std::mutex> lock(*mMutexPointer);

		if (std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime) >= (std::chrono::time_point_cast<std::chrono::milliseconds>(mTimeEnqueued) + mDelay))
		{
			return true;
		}

		return false;
	}




	void IEventPublisher::Deliver()
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> lock(*mMutexPointer);

			for (auto& subscriber : *mReferenceToSubscriberList)
			{
				futures.emplace_back(std::async(std::launch::async, [subscriber, this]()
				{
					subscriber->Notify(*this);
				}));
			}

		}

		for (auto& future : futures)
		{
			future.get();
		}
	}




	std::mutex* IEventPublisher::Mutex() const
	{
		return mMutexPointer;
	}

}