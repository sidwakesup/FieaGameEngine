#pragma once

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	Vector is a templated class that implements
	*			a vector, which is basically a dynamic array.
	*			It contains methods that run in constant time
	*			as well as those that run in linear time.
	*/
	template<typename T>
	class Vector final
	{
	public:
		
		/**
		*	@brief	Iterator is a class nested inside the Vector class
		*			that is used as a way to iterate through the elements
		*			in the dynamic array.
		*/
		class Iterator
		{
			friend class Vector;		//Vector is allowed to access the public and private members of the Iterator class
		public:

			/**
			*	@brief	Default constructor that initializes the iterator to not
			*			point to any array element or belong to any Vector
			*/
			Iterator();

			/**
			*	@brief	Copy constructor for the iterator class
			*	@param	other const Iterator reference that is to be copied
			*			to construct the new iterator
			*/
			Iterator(const Iterator& other);

			/**
			*	@brief	Move constructor for the iterator class
			*	@param	other const Iterator reference whose data
			*			is to be moved into the new iterator
			*/
			Iterator(Iterator&& other);

			/**
			*	@brief	The assignment operator is overloaded to copy the
			*			iterator
			*	@param	other a const reference to the Iterator that is to
			*			be copied
			*	@return	a reference to the Iterator obtained after the copy
			*/
			Iterator& operator=(const Iterator& other);

			/**
			*	@brief	The assignment operator is overloaded to move the
			*			iterator
			*	@param	other a const reference to the Iterator whose data
			*			is to be moved
			*	@return	a reference to the Iterator obtained after the move
			*/
			Iterator& operator=(Iterator&& other);

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
			*	@brief	The comparison operator is overloaded to compare the
			*			data members of the two Iterators
			*	@param	other a const reference to the Iterator you want to
			*			compare with
			*	@return	bool that indicates whether the two Iterators that
			*			were compared are equal or not (true if less than)
			*/
			bool operator<(const Iterator& other) const;

			/**
			*	@brief	The comparison operator is overloaded to compare the
			*			data members of the two Iterators
			*	@param	other a const reference to the Iterator you want to
			*			compare with
			*	@return	bool that indicates whether the two Iterators that
			*			were compared are equal or not (true if greater than)
			*/
			bool operator>(const Iterator& other) const;

			/**
			*	@brief	Prefix version of the increment operator is overloaded
			*			to reassign the Iterator to point to the element in the
			*			Vector
			*	@return	a reference to the Iterator after it has been incremented
			*/
			Iterator& operator++();

			/**
			*	@brief	Postfix version of the increment operator is overloaded
			*			to reassign the Iterator to point to the next element, but
			*			this increment should only be reflected in the statement
			*			following the increment
			*	@return	a copy of the Iterator before the increment to be used in
			*			the same statement
			*/
			Iterator operator++(int);

			/**
			*	@brief	The dereference operator is overloaded to obtain the data
			*			contained in the index pointed to by the Iterator
			*	@return	a reference to the data contained in the index that the
			*			Iterator points to
			*/
			T& operator*() const;

			/**
			*	@brief	Destructor for the Iterator
			*/
			~Iterator() = default;

		private:

			/**
			*	@brief	Parameterized constructor for the Iterator class
			*	@param	owner a const Vector reference to which the Iterator belongs
			*	@param	index an unsigned int that specifies which element the Iterator
			*			points to
			*/
			Iterator(const Vector<T>* owner, unsigned int index = 0);

			const Vector<T>* mOwner;		/**<	The Vector that the Iterator belongs to	*/
			unsigned int mIndex;			/**<	The array index of the element that the Iterator points to	*/
		};

		/**
		*	@brief	Default constructor that initializes
		*			the vector to be empty, ie, zero size
		*			and zero capacity.
		*/
		Vector();

		/**
		*	@brief	Parameterized constructor for the Vector
		*	@param	capacity a const unsigned int that represents
		*			the initial capacity of the Vector
		*/
		explicit Vector(const unsigned int capacity);

		/**
		*	@brief	Copy constructor for the vector
		*	@param	other a const Vector reference that is to be copied
		*/
		Vector(const Vector<T>& other);

		/**
		*	@brief	Move constructor for the Vector
		*	@param	other the Vector whose data is to be moved
		*			into the vector being constructed
		*/
		Vector(Vector<T>&& other);

		/**
		*	@brief	The copy assignment operator is overloaded to
		*			copy one vector into another
		*	@param	other const reference of the vector that is to
		*			be copied
		*	@return	a reference to the vector that the data was copied
		*			into
		*/
		Vector<T>& operator=(const Vector<T>& other);

		/**
		*	@brief	The move assignment operator is overloaded to
		*			move the contents of one vector into another
		*	@param	other the Vector whose data is to be moved
		*	@return	a reference to the vector into which the data
		*			was moved
		*/
		Vector<T>& operator=(Vector<T>&& other);

		/**
		*	@brief	Comparsion operator overload for the vector
		*	@param	other const reference to the vector to compare
		*	@return	bool that indicates whether the vectors are equal
		*			(true if equal)
		*/
		bool operator==(const Vector<T>& other) const;

		/**
		*	@brief	Comparsion operator overload for the vector
		*	@param	other const reference to the vector to compare
		*	@return	bool that indicates whether the vectors are equal
		*			(false if equal)
		*/
		bool operator!=(const Vector<T>& other) const;

		/**
		*	@brief	The index operator is overloaded to gain easy
		*			access to the elements of the vector
		*	@param	index a const unsigned int that represents the
		*			index of the element in the vector we want the
		*			contents of
		*	@return	a reference to the data at the given index in
		*			the vector
		*/
		T& operator[](const unsigned int index);

		/**
		*	@brief	The index operator is overloaded to gain easy
		*			access to the elements of the vector (const
		*			version)
		*	@param	index a const unsigned int that represents the
		*			index of the element in the vector we want the
		*			contents of
		*	@return	a const reference to the data at the given index
		*			in the vector
		*/
		const T& operator[](const unsigned int index) const;

		/**
		*	@brief	Method to remove the first item in the back of
		*			the vector and return its value.
		*	@return	an object of type T which is basically the
		*			data contained in the element that was popped
		*			from the back of the vector.
		*/
		T PopBack();

		/**
		*	@brief	Method that indicates whether the vector contains any items
		*	@return	bool that indicates whether the vector is empty
		*/
		bool IsEmpty() const;

		/**
		*	@brief	Method that returns the first item in the vector
		*	@return	T reference that refers to the data
		*			in the first element, ie, the front of the vector
		*/
		T& Front();

		/**
		*	@brief	Method that returns the first item in the vector (const protected)
		*	@return	const T reference that refers to the data
		*			in the first element, ie, the front of the vector
		*/
		const T& Front() const;

		/**
		*	@brief	Method that returns the last item in the vector
		*	@return	T reference that refers to the data
		*			in the last element, ie, the back of the vector
		*/
		T& Back();

		/**
		*	@brief	Method that returns the last item in the vector (const protected)
		*	@return	const T reference that refers to the data
		*			in the last element, ie, the back of the vector
		*/
		const T& Back() const;

		/**
		*	@brief	Method that returns the size of the vector
		*	@return	unsigned int that denotes the number of elements
		*			in the vector, ie, the size of the vector
		*/
		unsigned int Size() const;

		/**
		*	@brief	Method that returns the capacity of the vector
		*	@return	unsigned int that denotes the capacity
		*			of the vector
		*/
		unsigned int Capacity() const;

		/**
		*	@brief	Method that returns an Iterator that points to the
		*			beginning of the vector
		*	@return	an Iterator pointing to the first element in the vector
		*/
		Iterator begin() const;

		/**
		*	@brief	Method that returns an Iterator that points to
		*			the end of the vector
		*	@return	an Iterator pointing to the end (not the last
		*			element) of the vector
		*/
		Iterator end() const;

		/**
		*	@brief	Method to append the given item to the back of
		*			the vector.
		*	@param	data a reference to the data that is
		*			to be added as an element to the back of the
		*			vector
		*	@return	Iterator that points to the newly added element
		*/
		Iterator PushBack(const T& data);

		/**
		*	@brief	Method to obtain the contents of an element at a
		*			specified index in the vector
		*	@param	index a const unsigned int that indicates which
		*			element we want the contents of
		*	@return	a T reference to the data contained in the element
		*			at the specified index
		*/
		T& At(const unsigned int index);

		/**
		*	@brief	Method to obtain the contents of an element at a
		*			specified index in the vector (const protected)
		*	@param	index a const unsigned int that indicates which
		*			element we want the contents of
		*	@return	a const T reference to the data contained in the
		*			element at the specified index
		*/
		const T& At(const unsigned int index) const;

		/**
		*	@brief	Method to set a new maximum capacity for the vector
		*	@param	capacity a const unsigned integer that represents
		*			the new capacity of the vector
		*/
		void Reserve(const unsigned int capacity);

		/**
		*	@brief	Method to set a new size for the vector. If new size is
		*			greater than current size, then default constructed elements
		*			will populate the vector. If the new size is less than the
		*			current size, there is a potential loss of data.
		*	@param	size a const unsigned integer that represents the new size of
		*			the vector
		*/
		void Resize(const unsigned int size);

		/**
		*	@brief	Method to find an element in the vector
		*	@param	data a const T reference to the data that is
		*			to be searched
		*	@return	an Iterator that points to the element containing
		*			the data to be found (returns the end of the vector
		*			if the element is not found)
		*/
		Iterator Find(const T& data) const;

		/**
		*	@brief	Method to clear the entire vector by calling the destructor
		*			on all the initialized elements of the vector and also
		*			freeing all the memory that the vector owned
		*/
		void Clear();

		/**
		*	@brief	Method to remove a certain data from the vector
		*	@param	value a const T reference of the data to be removed
		*/
		void Remove(const T& value);

		/**
		*	@brief	Method to remove data in the vector pointed to by an Iterator
		*	@param	it a const Iterator reference that points to the data to be removed
		*/
		void Remove(const Iterator& it);

		/**
		*	@brief	Method to remove all the elements starting from the one pointed to by
		*			the first parameter Iterator to the one pointed to by the second parameter
		*			Iterator
		*	@param	first a const Iterator reference that points to the first item to be deleted
		*	@param	last a const Iterator reference that points to the last item to be deleted
		*/
		void Remove(const Iterator& first, const Iterator& last);

		/**
		*	@brief	Destructor for the Vector class that ensures
		*			there are no memory leaks
		*/
		virtual ~Vector();

	private:

		unsigned int mSize;				/**<	the size of the vector	*/
		unsigned int mCapacity;			/**<	the capacity of the vector	*/
		T* mBuffer;						/**<	pointer to the first element in the dynamic array	*/
	};
}

#include "Vector.inl"