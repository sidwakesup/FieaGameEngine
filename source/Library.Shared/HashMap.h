#pragma once

#include "SList.h"
#include "Vector.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	
	inline size_t Hash(std::string s)
	{
		const std::uint32_t RANDOM_PRIME_NUMBER = 36847;		/**<	@brief	Random prime number chosen for the hash function	*/

		std::uint32_t hash = RANDOM_PRIME_NUMBER;
		for (auto c : s)
		{
			hash = (hash << 5) + hash + c;
		}
		return hash;
	}

	/**
	*	@brief	Functor declaration for the default hashing
	*			function that takes in a template argument.
	*			Must be specialized for char* and abstract
	*			datatypes.
	*/
	template<typename K>
	class DefaultHashFunction
	{
	public:
		/**
		*	@brief	The hash function declaration. It is defined in
		*			the inl file.
		*	@param	k a const K reference. K is a template argument
		*			for this functor
		*	@return	a size_t that represents the bucket number that
		*			the key in question will be put in
		*/
		size_t operator()(const K& k) const;
	};

	/**
	*	@brief	Template specialization of the default hash function
	*			to accomodate char* key types.
	*/
	template<>
	class DefaultHashFunction<const char*>
	{
	public:
		/**
		*	@brief	The hash function specialization. The specialization
		*			is for a const char* key.
		*	@param	k a const char* reference.
		*	@return	a size_t that represents the bucket number that
		*			the key in question will be put in
		*/
		size_t operator()(const char* k) const
		{
			std::string temp(k);
			return Hash(temp);
		}
	};

	/**
	*	@brief	Template specialization of the default hash function
	*			to accomodate std::string key types.
	*/
	template<>
	class DefaultHashFunction<std::string>
	{
	public:
		/**
		*	@brief	The hash function specialization. The specialization is
		*			for a std::string.
		*	@param	k a std::string
		*	@return	a size_t that represents the bucket number that
		*			the key in question will be put in
		*/
		size_t operator()(std::string k) const
		{
			return Hash(k);
		}
	};

	/**
	*	@brief	Functor declaration for the custom
	*			comparison function for comparing two
	*			keys that can be of any datatype. Hence,
	*			it is templated.
	*/
	template<typename Key>
	class CustomComparisonFunction
	{
	public:
		
		/**
		*	@brief	The custom comparison function declaration.
		*			It is defined in the inl file.
		*	@param	lhs a const Key reference
		*	@param	rhs the other const Key reference
		*	@return	a bool which indicates the result of comparing
		*			lhs and rhs
		*/
		bool operator()(const Key& lhs, const Key& rhs) const;
	};

	/**
	*	@brief	Template specialization for the custom comparison
	*			function to accomodate const char* types
	*/
	template<>
	class CustomComparisonFunction<const char*>
	{
	public:

		/**
		*	@brief	The compare operation specialization for std::strings
		*	@param	lhs a const char*
		*	@param	rhs the other const char*
		*	@return	a bool which indicates the result of comparing
		*			lhs and rhs
		*/
		bool operator()(const char* lhs, const char* rhs) const
		{
			return (strcmp(lhs, rhs) == 0);
		}
	};

	/**
	*	@brief	HashMap is a templated class that implements
	*			a hashmap, which is basically a Vector of SLists.
	*			It contains methods that run in constant time
	*			as well as those that run in linear time.
	*/
	template<typename TKey, typename TData, typename HashFunctor = DefaultHashFunction<TKey>, typename ComparisonFunctor = CustomComparisonFunction<TKey>>
	class HashMap final
	{
	public:

		static const std::uint32_t BUCKET_SIZE = 13u;					/**<	@brief	Default bucket size		*/

		typedef std::pair<TKey, TData> PairType;				/**<	@brief	Referring to key value pairs as PairTypes	*/
		typedef SList<PairType> ChainType;						/**<	@brief	Referring to SLists of PairTypes as ChainTypes	*/
		typedef Vector<ChainType> BucketType;					/**<	@brief	Referring to Vector of ChainTypes as BucketTypes	*/
		typedef typename ChainType::Iterator ChainIterator;		/**<	@brief	Referring to ChainType Iterators as ChainIterators	*/

		/**
		*	@brief	Iterator is a class nested inside the HashMap class
		*			that is used as a way to iterate through the elements
		*			in the hashmap.
		*/
		class Iterator
		{
			friend class HashMap;		//HashMap is allowed to access the public and private members of Iterator

		public:

			/**
			*	@brief	Default constructor that initializes the iterator to not
			*			point to any element in the hashmap
			*/
			Iterator();

			/**
			*	@brief	Copy constructor for the iterator class
			*	@param	other const Iterator reference that is to be copied
			*			to construct the new iterator
			*/
			Iterator(const Iterator& other) = default;

			/**
			*	@brief	Move constructor for the iterator class
			*	@param	other const Iterator reference whose data
			*			is to be moved into the new iterator
			*/
			Iterator(Iterator&& other) = default;

			/**
			*	@brief	The assignment operator is overloaded to copy the
			*			iterator
			*	@param	other a const reference to the Iterator that is to
			*			be copied
			*	@return	a reference to the Iterator obtained after the copy
			*/
			Iterator& operator=(const Iterator& other) = default;

			/**
			*	@brief	The assignment operator is overloaded to move the
			*			iterator
			*	@param	other a const reference to the Iterator whose data
			*			is to be moved
			*	@return	a reference to the Iterator obtained after the move
			*/
			Iterator& operator=(Iterator&& other) = default;

			/**
			*	@brief	Prefix version of the increment operator is overloaded
			*			to reassign the Iterator to point to the element in the
			*			Hashmap
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
			*			contained in the element pointed to by the Iterator
			*	@return	a reference to the data contained in the element that the
			*			Iterator points to
			*/
			PairType& operator*();

			/**
			*	@brief	Another dereference operator is overloaded to obtain the data
			*			contained in the element pointed to by the Iterator
			*	@return	a reference to the data contained in the element that the
			*			Iterator points to
			*/
			PairType& operator->();

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
			*	@brief	Destructor for the Iterator
			*/
			~Iterator() = default;

		private:

			/**
			*	@brief	Parameterized constructor for the iterator
			*	@param	owner const reference to the HashMap that owns this iterator
			*	@param	bucketIndex const unsigned int that refers to the index in the BucketType
			*	@param	listIterator ChainIterator that points to a node in the SList
			*/
			Iterator(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& owner, const std::uint32_t bucketIndex, const ChainIterator& listIterator);

			const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>* mOwner;		/**<	@brief	The HashMap that owns this iterator	*/
			std::uint32_t mBucketIndex;												/**<	@brief	The index in the BucketType	*/
			ChainIterator mListIterator;											/**<	@brief	ChainIterator that points to a node in the SList	*/
		};

		/**
		*	@brief	Parameterized constructor that sets the
		*			number of buckets in the hashmap
		*	@param	numberOfBuckets the number of buckets that
		*			need to be created. defaults to BUCKET_SIZE
		*/
		explicit HashMap(const std::uint32_t numberOfBuckets = BUCKET_SIZE);

		/**
		*	@brief	Copy constructor for the HashMap
		*	@param	other const reference to the HashMap to be copied
		*/
		HashMap(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) = default;

		/**
		*	@brief	Move constructor for the HashMap
		*	@param	other the HashMap whose data is to be moved
		*/
		HashMap(HashMap<TKey, TData, HashFunctor, ComparisonFunctor>&& other) = default;

		/**
		*	@brief	The copy assignment operator is overloaded for HashMap
		*			and is defaulted
		*	@param	other const reference to the HashMap to be copied
		*/
		HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& operator=(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) = default;

		/**
		*	@brief	The move assignment operator is overloaded for HashMap
		*			and is defaulted
		*	@param	other the HashMap whose data is to be moved
		*/
		HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& operator=(HashMap<TKey, TData, HashFunctor, ComparisonFunctor>&& other) = default;

		/**
		*	@brief	The comparison operator for the hashmap is overloaded to use the custom comparison functor provided as a template parameter
		*	@param	other the hashmap to compare with
		*	@return	bool indicating whether the two hashmaps are equal. true if equal.
		*/
		bool operator==(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) const;

		/**
		*	@brief	The comparison operator for the hashmap is overloaded to use the custom comparison functor provided as a template parameter
		*	@param	other the hashmap to compare with
		*	@return	bool indicating whether the two hashmaps are equal. false if equal.
		*/
		bool operator!=(const HashMap<TKey, TData, HashFunctor, ComparisonFunctor>& other) const;

		/**
		*	@brief	The [] operator is overloaded to get an element in the Hashmap,
		*			given the key
		*	@param	key a const reference to the TKey that is used to search for the
		*			element in the HashMap
		*/
		TData& operator[](const TKey& key);

		/**
		*	@brief	Method that searches for an element in the HashMap
		*			given the key
		*	@param	key a const TKey reference that is to be searched for
		*	@return	an Iterator pointing to the element if it is found,
		*			end() otherwise
		*/
		Iterator Find(const TKey& key) const;

		/**
		*	@brief	Method to insert a key value pair in the HashMap, unless it
		*			already exists in the HashMap
		*	@param	keyValuePair a const reference to the PairType that is to be
		*			added into the HashMap
		*	@return	Iterator pointing to the PairType
		*/
		Iterator Insert(const PairType& keyValuePair);

		/**
		*	@brief	Method to insert a key value pair in the HashMap, unless it already exists
		*			in the HashMap. Also takes in a bool reference as an out parameter that is set
		*			to true if the key value pair is inserted.
		*	@param	keyValuePair a const reference to the PairType that is to be added to the
		*			HashMap
		*	@param	wasInserted bool reference used to indicate whether the insertion happened
		*	@return	Iterator pointing to the PairType
		*/
		Iterator Insert(const PairType& keyValuePair, bool& wasInserted);

		/**
		*	@brief	Method to remove a PairType from the HashMap, unless it doesn't
		*			exist in the first place, in which case it does nothing
		*	@param	key a const TKey reference that represents the key to search for
		*/
		bool Remove(const TKey& key);

		/**
		*	@brief	Method to check if the HashMap is empty
		*/
		bool IsEmpty() const;

		/**
		*	@brief	Method that empties the table and deletes any memory
		*			it allocated
		*/
		void Clear();

		/**
		*	@brief	Method to get the number of elements in the HashMap
		*	@return	an unsigned int that represents the number of
		*			elements in the HashMap
		*/
		std::uint32_t Size() const;

		/**
		*	@brief	Method to get the number of buckets in the HashMap
		*	@return	an unsigned int that represents the number of buckets
		*			in the HashMap
		*/
		std::uint32_t NumberOfBuckets() const;

		/**
		*	@brief	Method to check if the HashMap contains a key value pair
		*			with the key same as the supplied key
		*	@param	key a const TKey reference that represents the key that is
		*			to be searched in the HashMap
		*	@return	a bool that indicates whether the HashMap contains that key
		*/
		bool ContainsKey(const TKey& key);

		/**
		*	@brief	Overloaded implementation of ContainsKey that also has an
		*			out parameter that stores an Iterator pointing to the element
		*			if it is found, end() otherwise
		*	@param	key a const TKey reference that represents the key that is
		*			to be searched in the HashMap
		*	@param	it Iterator reference that serves as an out parameter
		*			that stores an iterator pointing to the key if it is found,
		*			end() otherwise
		*	@return	bool that indicates whether the key was found in the HashMap
		*/
		bool ContainsKey(const TKey& key, Iterator& it);

		/**
		*	@brief	Overloaded implementation of ContainsKey that also has an
		*			out parameter that stores an Iterator pointing to the element
		*			if it is found, end() otherwise (const version)
		*	@param	key a const TKey reference that represents the key that is
		*			to be searched in the HashMap
		*	@param	it Iterator reference that serves as an out parameter
		*			that stores an iterator pointing to the key if it is found,
		*			end() otherwise
		*	@return	bool that indicates whether the key was found in the HashMap
		*/
		const bool ContainsKey(const TKey& key, Iterator& it) const;

		/**
		*	@brief	Method to find the data at an element represented by the key
		*	@param	key a const TKey reference to search in the Hashmap
		*	@return	TData reference that represents the data corresponding to the
		*			TKey key
		*/
		TData& At(const TKey& key);

		/**
		*	@brief	Method to find the data at an element represented by the key (const version)
		*	@param	key a const TKey reference to search in the Hashmap
		*	@return	TData reference that represents the data corresponding to the
		*			TKey key
		*/
		const TData& At(const TKey& key) const;

		/**
		*	@brief	Method that returns an Iterator that points to the
		*			beginning of the HashMap
		*	@return	an Iterator pointing to the first element in the HashMap
		*/
		Iterator begin() const;

		/**
		*	@brief	Method that returns an Iterator that points to
		*			the end of the HashMap
		*	@return	an Iterator pointing to the end (not the last
		*			element) of the HashMap
		*/
		Iterator end() const;

		/**
		*	@brief	Destructor for the HashMap, which is defaulted
		*/
		~HashMap() = default;

	private:

		BucketType mBuckets;					/**<	The Vector of buckets	*/
		std::uint32_t mSize;					/**<	unsigned int that indicates the number of elements in the Hashmap	*/
	};
}

#include "HashMap.inl"