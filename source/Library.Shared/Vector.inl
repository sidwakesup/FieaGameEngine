#include "pch.h"
#include "Vector.h"

#pragma region Vector

#pragma region Iterator

template<typename T>
FieaGameEngine::Vector<T>::Iterator::Iterator() : mIndex(0), mOwner(nullptr)
{

}


template<typename T>
FieaGameEngine::Vector<T>::Iterator::Iterator(const Iterator& other) : mIndex(other.mIndex), mOwner(other.mOwner)
{

}


template<typename T>
FieaGameEngine::Vector<T>::Iterator::Iterator(Iterator&& other) : mIndex(other.mIndex), mOwner(other.mOwner)
{
	other.mIndex = 0;
	other.mOwner = nullptr;
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator& FieaGameEngine::Vector<T>::Iterator::operator=(const typename FieaGameEngine::Vector<T>::Iterator& other)
{
	if (this != &other)
	{
		mIndex = other.mIndex;
		mOwner = other.mOwner;
	}
	return *this;
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator& FieaGameEngine::Vector<T>::Iterator::operator=(typename FieaGameEngine::Vector<T>::Iterator&& other)
{
	if (this != &other)
	{
		mIndex = other.mIndex;
		mOwner = other.mOwner;
		other.mIndex = 0;
		other.mOwner = nullptr;
	}
	return *this;
}


template<typename T>
bool FieaGameEngine::Vector<T>::Iterator::operator==(const typename FieaGameEngine::Vector<T>::Iterator& other) const
{
	return ((mOwner == other.mOwner) && (mIndex == other.mIndex));
}


template<typename T>
bool FieaGameEngine::Vector<T>::Iterator::operator!=(const typename FieaGameEngine::Vector<T>::Iterator& other) const
{
	return !(operator==(other));
}


template<typename T>
bool FieaGameEngine::Vector<T>::Iterator::operator<(const typename FieaGameEngine::Vector<T>::Iterator& other) const
{
	return ((mOwner == other.mOwner) && (mIndex < other.mIndex));
}


template<typename T>
bool FieaGameEngine::Vector<T>::Iterator::operator>(const typename FieaGameEngine::Vector<T>::Iterator& other) const
{
	return ((mOwner == other.mOwner) && (mIndex > other.mIndex));
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator& FieaGameEngine::Vector<T>::Iterator::operator++()
{
	if (mOwner == nullptr)
	{
		throw std::exception("Iterator is invalid as it has no owner.");
	}
	if (mIndex >= (mOwner->Size()))
	{
		throw std::exception("Reached end of vector.");
	}
	++mIndex;
	return *this;
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator FieaGameEngine::Vector<T>::Iterator::operator++(int)
{
	Iterator it = *this;
	operator++();
	return it;
}


template<typename T>
T& FieaGameEngine::Vector<T>::Iterator::operator*() const
{
	if (mOwner == nullptr)
	{
		throw std::exception("Iterator uninitialized.");
	}
	else if (mIndex >= mOwner->mSize)
	{
		throw std::exception("Iterator index out of bounds.");
	}

	return mOwner->mBuffer[mIndex];
}


template<typename T>
FieaGameEngine::Vector<T>::Iterator::Iterator(const Vector<T>* owner, unsigned int index) : mOwner(owner), mIndex(index)
{

}


template<typename T>
FieaGameEngine::Vector<T>::Vector() : mSize(0), mCapacity(0), mBuffer(nullptr)
{

}


template<typename T>
FieaGameEngine::Vector<T>::Vector(const unsigned int capacity) : mSize(0), mCapacity(0), mBuffer(nullptr)
{
	Reserve(capacity);
}


template<typename T>
FieaGameEngine::Vector<T>::Vector(const Vector<T>& other) : mSize(other.mSize), mCapacity(other.mCapacity)
{
	mBuffer = static_cast<T*>(malloc(sizeof(T) * mCapacity));

	for (unsigned int i = 0; i < mSize; ++i)
	{
		new (mBuffer + i) T(other.At(i));

	}
}


template<typename T>
FieaGameEngine::Vector<T>::Vector(Vector<T>&& other) : mSize(other.mSize), mCapacity(other.mCapacity), mBuffer(other.mBuffer)
{
	other.mBuffer = nullptr;
	other.mSize = 0;
	other.mCapacity = 0;
}


template<typename T>
FieaGameEngine::Vector<T>& FieaGameEngine::Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		Clear();
		mSize = other.mSize;
		mCapacity = other.mCapacity;
		mBuffer = static_cast<T*>(malloc(sizeof(T) * mCapacity));
		for (unsigned int i = 0; i < mSize; ++i)
		{
			new (mBuffer + i) T(other.At(i));
		}
	}
	return *this;
}


template<typename T>
FieaGameEngine::Vector<T>& FieaGameEngine::Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		Clear();
		mSize = other.mSize;
		mCapacity = other.mCapacity;
		mBuffer = other.mBuffer;

		other.mBuffer = nullptr;
		other.mSize = 0;
		other.mCapacity = 0;
	}

	return *this;
}


template<typename T>
bool FieaGameEngine::Vector<T>::operator==(const Vector<T>& other) const
{
	if (mSize == other.mSize)
	{
		Iterator i, j;
		for (i = begin(), j = other.begin(); i != end(); ++i, ++j)
		{
			if (i != j)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}


template<typename T>
bool FieaGameEngine::Vector<T>::operator!=(const Vector<T>& other) const
{
	return !(operator==(other));
}


template<typename T>
T& FieaGameEngine::Vector<T>::operator[](const unsigned int index)
{
	if (index >= mSize)
	{
		throw std::exception("Array index out of bounds.");
	}
	return mBuffer[index];
}


template<typename T>
const T& FieaGameEngine::Vector<T>::operator[](const unsigned int index) const
{
	if (index >= mSize)
	{
		throw std::exception("Array index out of bounds.");
	}
	return mBuffer[index];
}


template<typename T>
T FieaGameEngine::Vector<T>::PopBack()
{
	if (mSize == 0)
	{
		throw std::exception("No items left to pop.");
	}
	T data = mBuffer[--mSize];
	mBuffer[mSize].~T();
	return data;
}


template<typename T>
bool FieaGameEngine::Vector<T>::IsEmpty() const
{
	return (mSize == 0);
}


template<typename T>
T& FieaGameEngine::Vector<T>::Front()
{
	if (mSize == 0)
	{
		throw std::exception("Vector is empty.");
	}
	return mBuffer[0];
}


template<typename T>
const T& FieaGameEngine::Vector<T>::Front() const
{
	if (mSize == 0)
	{
		throw std::exception("Vector is empty.");
	}
	return mBuffer[0];
}


template<typename T>
T& FieaGameEngine::Vector<T>::Back()
{
	if (mSize == 0)
	{
		throw std::exception("Vector is empty.");
	}
	return mBuffer[mSize - 1];
}


template<typename T>
const T& FieaGameEngine::Vector<T>::Back() const
{
	if (mSize == 0)
	{
		throw std::exception("Vector is empty.");
	}
	return mBuffer[mSize - 1];
}


template<typename T>
unsigned int FieaGameEngine::Vector<T>::Size() const
{
	return mSize;
}


template<typename T>
unsigned int FieaGameEngine::Vector<T>::Capacity() const
{
	return mCapacity;
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator FieaGameEngine::Vector<T>::begin() const
{
	return Iterator(this, 0);
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator FieaGameEngine::Vector<T>::end() const
{
	return Iterator(this, mSize);
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator FieaGameEngine::Vector<T>::PushBack(const T& data)
{
	if (mSize >= mCapacity)
	{
		Reserve(mCapacity + 5);
	}
	new (mBuffer + mSize) T(data);
	return Iterator(this, mSize++);
}


template<typename T>
T& FieaGameEngine::Vector<T>::At(const unsigned int index)
{
	if (index >= mSize)
	{
		throw std::exception("Index out of bounds.");
	}
	return mBuffer[index];
}


template<typename T>
const T& FieaGameEngine::Vector<T>::At(const unsigned int index) const
{
	if (index >= mSize)
	{
		throw std::exception("Index out of bounds.");
	}
	return mBuffer[index];
}


template<typename T>
void FieaGameEngine::Vector<T>::Reserve(const unsigned int capacity)
{
	if (capacity > mCapacity)
	{
		mBuffer = static_cast<T*>(realloc(mBuffer, (sizeof(T) * capacity)));
		mCapacity = capacity;
	}
}


template<typename T>
void FieaGameEngine::Vector<T>::Resize(const unsigned int size)
{
	Reserve(size);
	for (unsigned int i = size; i < mSize; ++i)
	{
		mBuffer[i].~T();
	}
	mBuffer = reinterpret_cast<T*>(realloc(mBuffer, (size * sizeof(T))));
	for (unsigned int i = mSize; i < size; ++i)
	{
		new (mBuffer + i) T();
	}
	mSize = size;
	mCapacity = size;
}


template<typename T>
typename FieaGameEngine::Vector<T>::Iterator FieaGameEngine::Vector<T>::Find(const T& data) const
{
	unsigned int i = 0;
	for (i = 0; i < mSize; i++)
	{
		if (mBuffer[i] == data)
		{
			break;
		}
	}
	return Iterator(this, i);
}


template<typename T>
void FieaGameEngine::Vector<T>::Clear()
{
	if (mCapacity != 0)
	{
		for (unsigned int i = 0; i < mSize; ++i)
		{
			mBuffer[i].~T();
		}
		mSize = 0;
		free(mBuffer);
		mBuffer = nullptr;
		mCapacity = 0;
	}
}


template<typename T>
void FieaGameEngine::Vector<T>::Remove(const T& data)
{
	Remove(Find(data));
}


template<typename T>
void FieaGameEngine::Vector<T>::Remove(const Iterator& it)
{
	if (this != it.mOwner)
	{
		throw std::exception("Invalid owner.");
	}
	if (mSize > 0)
	{
		if (it.mIndex == (mSize - 1))
		{
			PopBack();
			return;
		}
		mBuffer[it.mIndex].~T();
		memmove_s((mBuffer + it.mIndex), (sizeof(T) * (mSize - it.mIndex)), (mBuffer + it.mIndex + 1), (sizeof(T) * (mSize - it.mIndex)));
		--mSize;
	}
}


template<typename T>
void FieaGameEngine::Vector<T>::Remove(const Iterator& first, const Iterator& last)
{
	if ((first.mOwner != last.mOwner) || (first > last))
	{
		throw std::exception("Invalid parameters.");
	}
	else if (first == last)
	{
		Remove(first);
	}
	else
	{
		for (unsigned int i = first.mIndex; i <= last.mIndex; ++i)
		{
			mBuffer[i].~T();
		}
		memmove_s((mBuffer + first.mIndex), (sizeof(T) * (mSize - (last.mIndex - first.mIndex))), (mBuffer + last.mIndex + 1), (sizeof(T) * (mSize - (last.mIndex - first.mIndex))));
		mSize -= (last.mIndex - first.mIndex + 1);
	}
}


template<typename T>
FieaGameEngine::Vector<T>::~Vector()
{
	Clear();
}

#pragma endregion

#pragma endregion