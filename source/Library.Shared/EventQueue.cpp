#include "pch.h"
#include "EventQueue.h"


namespace FieaGameEngine
{

	void EventQueue::Enqueue(const std::shared_ptr<IEventPublisher>& eventPublisher, const GameTime& gameTime, std::chrono::milliseconds delay)
	{
		eventPublisher->SetTime(gameTime.CurrentTime(), delay);

		{
			std::lock_guard<std::mutex> lock(mMutex);

			mQueue.push_back(eventPublisher);
		}
	}




	void EventQueue::Send(const std::shared_ptr<IEventPublisher>& eventToSend)
	{
		eventToSend->Deliver();
	}




	void EventQueue::Update(const GameTime& gameTime)
	{
		std::vector<std::shared_ptr<IEventPublisher>>::iterator firstExpiredEvent;

		auto expression = [&gameTime](std::shared_ptr<IEventPublisher> eventPublisher)
		{
			return !eventPublisher->IsExpired(gameTime.CurrentTime());
		};

		firstExpiredEvent = std::partition(mQueue.begin(), mQueue.end(), expression);

		std::move(firstExpiredEvent, mQueue.end(), std::back_inserter(mExpiredEvents));

		mQueue.erase(firstExpiredEvent, mQueue.end());

		std::vector<std::future<void>> futures;

		for (auto& expiredEvent : mExpiredEvents)
		{
			futures.emplace_back(std::async(std::launch::async, [expiredEvent]()
			{
				expiredEvent->Deliver();
			}));

		}

		for (auto& future : futures)
		{
			future.get();
		}

		mExpiredEvents.erase(mExpiredEvents.begin(), mExpiredEvents.end());

	}




	bool EventQueue::IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(mMutex);

		return mQueue.empty();
	}




	std::uint32_t EventQueue::Size() const
	{
		std::lock_guard<std::mutex> lock(mMutex);

		return static_cast<std::uint32_t>(mQueue.size());
	}

}