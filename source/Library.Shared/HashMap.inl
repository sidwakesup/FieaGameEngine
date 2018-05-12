#include "pch.h"
#include "HashMap.h"


template<typename K>
size_t FieaGameEngine::DefaultHashFunction<K>::operator()(const K& k) const
{
	std::string temp(reinterpret_cast<char*>(k));
	return Hash(temp);
}


template<typename Key>
bool FieaGameEngine::CustomComparisonFunction<Key>::operator()(const Key& lhs, const Key& rhs) const
{
	return (lhs == rhs);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::Iterator() : mOwner(nullptr), mBucketIndex(0), mListIterator(ChainIterator())
{
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator++()
{
	if (!mOwner)
	{
		throw std::exception("Invalid owner.");
	}

	if (++mListIterator == mOwner->mBuckets[mBucketIndex].end())
	{
		++mBucketIndex;
		while ((mBucketIndex < mOwner->mBuckets.Size()) && (mOwner->mBuckets[mBucketIndex].IsEmpty()))
		{
			++mBucketIndex;
		}
		if (mBucketIndex < mOwner->mBuckets.Size())
		{
			mListIterator = mOwner->mBuckets[mBucketIndex].begin();
		}
		else
		{
			mListIterator = mOwner->mBuckets[mBucketIndex - 1].end();
		}
	}

	return *this;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator++(int)
{
	HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator temp(*this);

	operator++();

	return temp;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::PairType& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator*()
{
	if (!mOwner)
	{
		throw std::exception("Invalid owner.");
	}

	if (mBucketIndex == mOwner->mBuckets.Size())
	{
		throw std::exception("End of vector reached.");
	}

	return (*mListIterator);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::PairType& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator->()
{
	if (!mOwner)
	{
		throw std::exception("Invalid owner.");
	}

	if (mBucketIndex == mOwner->mBuckets.Size())
	{
		throw std::exception("End of vector reached.");
	}

	return (*mListIterator);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator==(const Iterator& other) const
{
	return ((mOwner == other.mOwner) && (mBucketIndex == other.mBucketIndex) && (mListIterator == other.mListIterator));
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::operator!=(const Iterator& other) const
{
	return !(operator==(other));
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator::Iterator(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& owner, const std::uint32_t bucketIndex, const ChainIterator& listIterator) : mOwner(&owner), mBucketIndex(bucketIndex), mListIterator(listIterator)
{
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::HashMap(const std::uint32_t numberOfBuckets) : mSize(0), mBuckets(BucketType())
{
	mBuckets.Resize(numberOfBuckets);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::operator==(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) const
{
	if (mSize == other.mSize)
	{
		for (Iterator it = begin(); it != end(); ++it)
		{
			if (*other.Find((*it).first) != *it)
			{
				return false;
			}
		}
		return true;
	}

	return false;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::operator!=(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) const
{
	return !(operator==(other));
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
TData& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::operator[](const TKey& key)
{
	Iterator it(Insert(std::make_pair(key, TData())));
	
	return (*it).second;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Find(const TKey& key) const
{
	ComparisonFunctor compare;

	Iterator it = begin();
	if (begin() != end())
	{
		for (it = begin(); it != end(); ++it)
		{
			if (compare((*it).first, key))
			{
				break;
			}
		}
	}

	return it;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Insert(const PairType& keyValuePair)
{
	HashFunctor hashFunction;
	std::uint32_t index = hashFunction(keyValuePair.first) % mBuckets.Size();

	Iterator it;

	if (ContainsKey(keyValuePair.first, it))
	{
		return it;
	}

	it = Iterator(*this, index, mBuckets[index].PushBack(keyValuePair));
	++mSize;

	return it;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Insert(const PairType& keyValuePair, bool& wasInserted)
{
	HashFunctor hashFunction;
	std::uint32_t index = hashFunction(keyValuePair.first) % mBuckets.Size();
	wasInserted = false;

	Iterator it;

	if (ContainsKey(keyValuePair.first, it))
	{
		return it;
	}

	it = Iterator(*this, index, mBuckets[index].PushBack(keyValuePair));
	++mSize;

	wasInserted = true;
	return it;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Remove(const TKey& key)
{
	Iterator it;

	if (!ContainsKey(key, it))
	{
		return false;
	}

	mBuckets[it.mBucketIndex].Remove(it.mListIterator);
	--mSize;

	return true;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::IsEmpty() const
{
	return (mSize == 0u);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
void FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Clear()
{
	for (std::uint32_t i = 0; i < mBuckets.Size(); ++i)
	{
		mBuckets[i].Clear();
	}
	mSize = 0;

}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
std::uint32_t FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Size() const
{
	return mSize;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
std::uint32_t FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::NumberOfBuckets() const
{
	return mBuckets.Size();
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::ContainsKey(const TKey& key)
{
	Iterator it;

	return ContainsKey(key, it);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::ContainsKey(const TKey& key, Iterator& it)
{
	bool containsKey = false;
	it = Find(key);
	if (it != end())
	{
		containsKey = true;
	}

	return containsKey;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
const bool FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::ContainsKey(const TKey& key, Iterator& it) const
{
	bool containsKey = false;
	it = Find(key);
	if (it != end())
	{
		containsKey = true;
	}

	return containsKey;
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
TData& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::At(const TKey& key)
{
	auto it = Find(key);
	if (it == end())
	{
		throw std::exception("Invalid key.");
	}

	return ((*it).second);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
const TData& FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::At(const TKey& key) const
{
	auto it = Find(key);
	if (it == end())
	{
		throw std::exception("Invalid key.");
	}

	return ((*it).second);
}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::begin() const
{
	std::uint32_t i;
	for (i = 0; i < mBuckets.Size(); ++i)
	{
		if (!mBuckets[i].IsEmpty())
		{
			return Iterator(*this, i, mBuckets[i].begin());
		}
	}

	return end();

}


template<typename TKey, typename TData, typename HashFunctor, typename ComparisonFunctor>
typename FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::Iterator FieaGameEngine::HashMap<TKey, TData, HashFunctor, ComparisonFunctor>::end() const
{
	return Iterator(*this, mBuckets.Size(), mBuckets[mBuckets.Size() - 1].end());
}