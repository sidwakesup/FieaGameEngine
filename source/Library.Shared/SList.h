#pragma once

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	SList is a templated class that implements
	*			a singly linked list. It contains methods
	*			that run in constant time as well as those
	*			that run in linear time.
	*/
	template<typename T>
	class SList final
	{
	public:

		class Iterator;		//forward declaring the Iterator class so that it can be used by the SList

		/**
		*	@brief	Default constructor that initializes the list
		*			to be empty.
		*/
		SList();

		/**
		*	@brief	Method to insert the given item before the 
		*			front of the list.
		*	@param	data a reference to the data that is
		*			to be added as a node to the front of the
		*			list.
		*	@return	Iterator that points to the newly added node
		*/
		Iterator PushFront(const T& data);

		/**
		*	@brief	Method to remove the first item in the front of
		*			the list and return its value.
		*	@return	an object of type T which is basically the 
		*			data contained in the node that was popped
		*			from the front of the list.
		*/
		T PopFront();

		/**
		*	@brief	Method to remove the last item in the back of the
		*			list and return its value
		*	@return	an object of type T which is basically the data
		*			contained in the node that was popped from the back
		*			of the list
		*/
		T PopBack();

		/**
		*	@brief	Method to append the given item to the back of 
		*			the list.
		*	@param	data a reference to the data that is
		*			to be added as a node to the back of the list
		*	@return	Iterator that points to the newly added node
		*/
		Iterator PushBack(const T& data);

		/**
		*	@brief	Method that indicates whether the list contains any items
		*	@return	bool that indicates whether the list
		*			is empty
		*/
		bool IsEmpty() const;

		/**
		*	@brief	Method that returns the first item in the list (const protected)
		*	@return	const T reference that refers to the data
		*			in the first node, ie, the front of the list
		*/
		const T& Front() const;

		/**
		*	@brief	Method that returns the first item in the list
		*	@return	T reference that refers to the data
		*			in the first node, ie, the front of the list
		*/
		T& Front();

		/**
		*	@brief	Method that returns the last item in the list (const protected)
		*	@return	const T reference that refers to the data
		*			in the last node, ie, the back of the list
		*/
		const T& Back() const;

		/**
		*	@brief	Method that returns the last item in the list
		*	@return	T reference that refers to the data
		*			in the last node, ie, the back of the list
		*/
		T& Back();

		/**
		*	@brief	Method that returns the size of the list
		*	@return	int that denotes the number of nodes
		*			in the list, ie, the size of the list
		*/
		int Size() const;

		/**
		*	@brief	Copy constructor that creates a deep copy of the other list
		*	@param	other a const SList reference to the list that is to be
		*			copied
		*/
		SList(const SList& other);

		/**
		*	@brief	Move constructor that moves the data from one list to the other
		*	@param	other a const SList rvalue reference to the list that is to be moved
		*/
		SList(SList&& other);

		/**
		*	@brief	The '=' operator is overloaded to create a
		*			deep copy of the other list
		*	@param	other a const SList reference to the list that is to be
		*			copied
		*/
		SList& operator= (const SList& other);

		/**
		*	@brief	The '=' operator is also overloaded to implement
		*			move semantics in an assignment operation.
		*	@param	other a const SList reference to the list that is to be
		*			moved.
		*/
		SList& operator=(SList&& other);

		/**
		*	@brief	Destructor that makes sure there are no memory leaks
		*/
		~SList();

		/**
		*	@brief	Removes all the items from the list
		*/
		void Clear();
		
		class Node;		//forward declaring the Node class so that it can be used by the Iterator

		/**
		*	@brief	Iterator is a class nested inside the SList class
		*			that is used as a way to iterate through the nodes
		*			in the SList
		*/
		class Iterator
		{
			friend class SList;		//SList is allowed to access the public and private members of the Iterator class

		public:

			/**
			*	@brief	Default constructor that initializes the iterator to not
			*			point to any node or belong to any SList
			*/
			Iterator();
			
			/**
			*	@brief	Parameterized constructor that copies an iterator
			*			and creates a new one.
			*	@param	other a const reference to the Iterator that is to
						be copied
			*/
			Iterator(const Iterator& other);

			/**
			*	@brief	The assignment operator is overloaded to copy the
			*			iterator
			*	@param	other a const reference to the Iterator that is to
			*			be copied
			*	@return	a reference to the Iterator obtained after the copy
			*/
			Iterator& operator=(const Iterator& other);

			/**
			*	@brief	The comparison operator is overloaded to compare the
			*			data members of the two Iterators
			*	@param	other a const reference to the Iterator you want to
			*			compare with
			*	@return	bool that indicates whether the two Iterators that
			*			were compared are equal or not (true if equal)
			*/
			bool operator==(const Iterator& other) const;

			/**
			*	@brief	The comparison operator is overloaded to compare the
			*			data members of the two Iterators
			*	@param	other a const reference to the Iterator you want to
			*			compare with
			*	@return	bool that indicates whether the two Iterators that
			*			were compared are equal or not (false if equal)
			*/
			bool operator!=(const Iterator& other) const;

			/**
			*	@brief	Prefix version of the increment operator is overloaded
			*			to reassign the Iterator to point to the next node
			*	@return	a reference to the Iterator after it has been incremented
			*/
			Iterator& operator++();

			/**
			*	@brief	Postfix version of the increment operator is overloaded
			*			to reassign the Iterator to point to the next node, but
			*			this increment should only be reflected in the statement
			*			following the increment
			*	@return	a copy of the Iterator before the increment to be used in
			*			the same statement
			*/
			Iterator operator++(int);

			/**
			*	@brief	The dereference operator is overloaded to obtain the data
			*			contained in the node pointed to by the Iterator
			*	@return	a reference to the data contained in the node that the
			*			Iterator points to
			*/
			T& operator*();

			/**
			*	@brief	The dereference operator is overloaded to obtain the data
			*			contained in the node pointed to by the Iterator
			*	@return	a reference to the data contained in the node that the
			*			Iterator points to
			*/
			const T& operator*() const;

			/**
			*	@brief	Destructor for the Iterator
			*/
			~Iterator();

		private:

			/**
			*	@brief	Parameterized constructor for the Iterator class
			*	@param	node a pointer to the Node that the Iterator must point to
			*	@param	owner a const reference to the SList that the Iterator will
			*			belong to
			*/
			Iterator(Node* node, const SList& owner);

			Node* mNode;			/**<	@brief	pointer to the node in the list that the Iterator points to	*/
			const SList* mOwner;	/**<	@brief	const pointer to the SList that the Iterator belongs to	*/
		};

		/**
		*	@brief	Method that returns an Iterator that points to the node
		*			at the beginning of the list
		*	@return	an Iterator pointing to the first node in the list
		*/
		Iterator begin();

		/**
		*	@brief	Method that returns an Iterator that points to the node
		*			at the beginning of the list
		*	@return	an Iterator pointing to the first node in the list
		*/
		const Iterator begin() const;

		/**
		*	@brief	Method that returns an Iterator that points to
		*			the end of the list
		*	@return	an Iterator pointing to the end of the list
		*/
		Iterator end();

		/**
		*	@brief	Method that returns an Iterator that points
		*			to the end of the list
		*	@return	an Iterator pointing to the end of the list
		*/
		const Iterator end() const;

		/**
		*	@brief	Method to insert a node after the node that an
		*			Iterator is pointing to
		*	@param	data a const reference to the data that the node
		*			will contain
		*	@param	it a const Iterator reference to the Iterator after
		*			which the node is to be inserted
		*/
		void InsertAfter(const T& data, const Iterator& it);

		/**
		*	@brief	Method that iterates through the SList using an Iterator
		*			to search for a specific data item
		*	@param	a const reference to the data that is to be searched
		*	@return	an Iterator pointing to the node that contains the data
		*			to be searched. Returns the end of the list if the node
		*			is not found
		*/
		Iterator Find(const T& data) const;

		/**
		*	@brief	Method to remove a node in the list
		*	@param	value a const reference to the data that is to be removed
		*/
		void Remove(const T& value);

		/**
		*	@brief	Method to remove a node in the list
		*	@param	it a const reference to the Iterator pointing to the node
		*			in the list that is to be removed
		*/
		void Remove(const Iterator& it);

	private:

		/**
		*	@brief	A Node represent each item in the singly
		*			linked list SList. It has its own set of
		*			data members and methods.
		*/
		class Node
		{
		public:

			/**
			*	@brief	Parameterized constructor for creating a new node
			*	@param	data a const T reference to the data that the node
			*			will contain
			*	@param	next a const pointer to the next node in the list. defaults
			*			to nullptr
			*/
			Node(const T& data, Node* next = nullptr);

			T data;				/**<	@brief	The data contained in a node	*/
			Node* next;			/**<	@brief	Reference to the next node in the list	*/
		};

		Node* mFront;			/**<	@brief	Reference to the front (first node) of the list	*/
		Node* mBack;			/**<	@brief	Reference to the back (last node) of the list	*/
		unsigned int mSize;		/**<	@brief	Member variable that stores the size of the list	*/
	};
}

#include "SList.inl"