#include "pch.h"
#include "Event.h"


namespace FieaGameEngine
{
	template<typename Payload>
	RTTI_DEFINITIONS(Event<Payload>)


	template<typename Payload>
	Vector<IEventSubscriber*> Event<Payload>::mSubscribers(0);

	template<typename Payload>
	std::mutex Event<Payload>::mMutex;


	template<typename Payload>
	Event<Payload>::Event(const Payload& payload, const Vector<IEventSubscriber*>& subscribers) : IEventPublisher::IEventPublisher(mSubscribers, mMutex), mPayload(payload)
	{
		std::lock_guard<std::mutex> lock(mMutex);

		for (auto& subscriber : subscribers)
		{
			Event<Payload>::Subscribe(*subscriber);
		}

	}




	template<typename Payload>
	void Event<Payload>::Subscribe(IEventSubscriber& eventSubscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);

		if (mSubscribers.Find(&eventSubscriber) == mSubscribers.end())
		{
			mSubscribers.PushBack(&eventSubscriber);
		}
	}




	template<typename Payload>
	void Event<Payload>::Unsubscribe(IEventSubscriber& eventSubscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);

		mSubscribers.Remove(&eventSubscriber);
	}




	template<typename Payload>
	void Event<Payload>::UnsubscribeAll()
	{
		std::lock_guard<std::mutex> lock(mMutex);

		mSubscribers.Clear();
	}




	template<typename Payload>
	const Payload& Event<Payload>::Message() const
	{
		return mPayload;
	}

}