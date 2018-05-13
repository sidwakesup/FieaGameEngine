#include "pch.h"
#include "SList.h"

#pragma region SList
template<typename T>
FieaGameEngine::SList<T>::SList() : mSize(0), mFront(nullptr), mBack(nullptr)
{

}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::PushFront(const T& data)
{
	mFront = new Node(data, mFront);
	if (mSize == 0)
	{
		mBack = mFront;
	}
	++mSize;

	return Iterator(mFront, *this);
}


template<typename T>
T FieaGameEngine::SList<T>::PopFront()
{
	if (mFront == nullptr)
	{
		throw std::exception("PopFront: List is empty.");
	}

	T data = mFront->data;
	Node* nodeToBePopped = mFront;
	mFront = mFront->next;
	delete nodeToBePopped;
	--mSize;
	if (mSize == 0)
	{
		mFront = nullptr;
		mBack = nullptr;
	}
	return data;
}


template<typename T>
T FieaGameEngine::SList<T>::PopBack()
{
	if (mFront == nullptr)
	{
		throw std::exception("PopBack: List is empty.");
	}

	Node* nodeToBePopped;
	Iterator prev, current;
	current = begin();
	if (mSize == 1)
	{
		mFront = nullptr;
		mBack = nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < mSize - 1; ++i)
		{
			prev = current;
			current.mNode = current.mNode->next;
		}
		prev.mNode->next = current.mNode->next;
	}
	nodeToBePopped = current.mNode;
	T data = current.mNode->data;
	delete nodeToBePopped;
	--mSize;

	return data;
}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::PushBack(const T& data)
{
	Node* newnode = new Node(data, nullptr);
	if (mBack == nullptr)
	{
		mFront = newnode;
	}
	else
	{
		Node* current = mBack;
		current->next = newnode;
	}
	mBack = newnode;
	++mSize;

	return Iterator(newnode, *this);
}


template<typename T>
bool FieaGameEngine::SList<T>::IsEmpty() const
{
	return (mSize == 0);
}


template<typename T>
const T& FieaGameEngine::SList<T>::Front() const
{
	if (mFront == nullptr)
	{
		throw std::exception("Front: List is empty.");
	}
	
	return mFront->data;
}

template<typename T>
T& FieaGameEngine::SList<T>::Front()
{
	if (mFront == nullptr)
	{
		throw std::exception("Front: List is empty.");
	}
	
	return mFront->data;
}


template<typename T>
const T& FieaGameEngine::SList<T>::Back() const
{
	if (mBack == nullptr)
	{
		throw std::exception("List is empty.");
	}
	
	return mBack->data;
}

template<typename T>
T& FieaGameEngine::SList<T>::Back()
{
	if (mBack == nullptr)
	{
		throw std::exception("List is empty.");
	}
	
	return mBack->data;
}


template<typename T>
int FieaGameEngine::SList<T>::Size() const
{
	return mSize;
}


template<typename T>
FieaGameEngine::SList<T>::SList(const SList<T>& other) : mFront(nullptr), mBack(nullptr), mSize(0)
{
	for (auto& value : other)
	{
		PushBack(value);
	}
}


template<typename T>
FieaGameEngine::SList<T>::SList(SList<T>&& other) : mFront(nullptr) mBack(nullptr), mSize(0)
{
	mFront = other.mFront;
	mBack = other.mBack;
	mSize = other.mSize;

	other.mFront = nullptr;
	other.mBack = nullptr;
	other.mSize = 0;
}


template<typename T>
FieaGameEngine::SList<T>& FieaGameEngine::SList<T>::operator=(const FieaGameEngine::SList<T>& other)
{
	if (this != &other)
	{
		Clear();
		for (auto& value : other)
		{
			PushBack(value);
		}
	}

	return *this;
}


template<typename T>
FieaGameEngine::SList<T>& FieaGameEngine::SList<T>::operator=(FieaGameEngine::SList<T>&& other)
{
	if (this != &other)
	{
		Clear();
		mFront = other.mFront;
		mBack = other.mBack;
		mSize = other.mSize;

		other.mFront = nullptr;
		other.mBack = nullptr;
		other.mSize = 0;
	}

	return *this;
}


template<typename T>
FieaGameEngine::SList<T>::~SList()
{
	Clear();
}


template<typename T>
void FieaGameEngine::SList<T>::Clear()
{
	while (mSize > 0)
	{
		PopFront();
	}
}

#pragma endregion

#pragma region Iterator

template<typename T>
FieaGameEngine::SList<T>::Iterator::Iterator() : mNode(nullptr), mOwner(nullptr)
{

}

template<typename T>
FieaGameEngine::SList<T>::Iterator::Iterator(const Iterator& other) : mNode(other.mNode), mOwner(other.mOwner)
{

}

template<typename T>
typename FieaGameEngine::SList<T>::Iterator& FieaGameEngine::SList<T>::Iterator::operator=(const Iterator& other)
{
	if (this != &other)
	{
		mNode = other.mNode;
		mOwner = other.mOwner;
	}
	return *this;
}


template<typename T>
typename bool FieaGameEngine::SList<T>::Iterator::operator==(const Iterator& other) const
{
	return ((mOwner == other.mOwner) && (mNode == other.mNode));
}


template<typename T>
typename bool FieaGameEngine::SList<T>::Iterator::operator!=(const Iterator& other) const
{
	return !(operator==(other));
}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator& FieaGameEngine::SList<T>::Iterator::operator++()
{
	if (mNode == nullptr)
	{
		throw std::exception("Out of items.");
	}
	mNode = mNode->next;
	return *this;
}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::Iterator::operator++(int)
{
	if (mNode == nullptr)
	{
		throw std::exception("Out of items.");
	}
	Iterator it(*this);
	operator++();
	return it;
}


template<typename T>
typename T& FieaGameEngine::SList<T>::Iterator::operator*()
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator uninitialized.");
	}
	return mNode->data;
}


template<typename T>
typename const T& FieaGameEngine::SList<T>::Iterator::operator*() const
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator uninitialized.");
	}
	return mNode->data;
}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::begin()
{
	return Iterator(mFront, *this);
}


template<typename T>
typename const FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::begin() const
{
	return Iterator(mFront, *this);
}

template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::end()
{
	return Iterator(nullptr, *this);
}


template<typename T>
typename const FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::end() const
{
	return Iterator(nullptr, *this);
}


template<typename T>
void FieaGameEngine::SList<T>::InsertAfter(const T& data, const Iterator& it)
{
	if (it.mOwner != this)
	{
		throw std::exception("The iterator does not belong to this list.");
	}

	if (it == end() || it.mNode == mBack)
	{
		PushBack(data);
	}
	else
	{
		Node* newnode = new Node(data, it.mNode->next);
		it.mNode->next = newnode;
		if (mBack == it.mNode)
		{
			mBack = newnode;
		}
		++mSize;
	}
}


template<typename T>
typename FieaGameEngine::SList<T>::Iterator FieaGameEngine::SList<T>::Find(const T& data) const
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (*it == data)
		{
			return it;
		}
	}
	return end();
}


template<typename T>
void FieaGameEngine::SList<T>::Remove(const T& value)
{
	Iterator current, prev;
	for(current = begin(); current != end(); ++current)
	{
		if (current.mNode->data == value)
		{
			if (prev.mNode == nullptr)
			{
				mFront = current.mNode->next;
				delete current.mNode;
				--mSize;
				if (mSize == 0)
				{
					mBack = nullptr;
				}
				return;
			}
			prev.mNode->next = current.mNode->next;
			mBack = prev.mNode;
			delete current.mNode;
			--mSize;
			return;
		}
		prev = current;
	}
}


template<typename T>
void FieaGameEngine::SList<T>::Remove(const Iterator& it)
{
	if (it == end())
	{
		throw std::exception("Cannot delete Iterator pointing to end of Slist.");
	}


	if (it.mNode == mFront)
	{
		PopFront();
	}
	else if (mSize > 1)
	{
		Iterator prev = begin();
		while (prev.mNode->next != it.mNode)
		{
			prev++;
		}
		prev.mNode->next = it.mNode->next;
		delete it.mNode;
		--mSize;
	}
	else
	{
		PopBack();
	}

	return;
}


template<typename T>
FieaGameEngine::SList<T>::Iterator::~Iterator()
{

}

template<typename T>
FieaGameEngine::SList<T>::Iterator::Iterator(Node* node, const SList& owner) : mNode(node), mOwner(&owner)
{

}

#pragma endregion

#pragma region Node
template<typename T>
FieaGameEngine::SList<T>::Node::Node(const T& Data, Node* Next) : data(Data), next(Next)
{

}

#pragma endregion