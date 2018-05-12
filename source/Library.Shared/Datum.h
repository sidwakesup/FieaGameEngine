#pragma once

#define GLM_FORCE_CXX98


/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	class Scope;

	/**
	*	@brief	Enumeration that contains a list of
	*			different datatypes that the Datum
	*			can currently support.
	*/
	enum class EDatumType
	{
		EUnknown,
		EInteger,
		EFloat,
		EVector4,
		EMatrix4x4,
		ETable,
		EString,
		ERTTIPointer,
		ENumberOfSupportedDatatypes
	};

	/**
	*	@brief	The Datum class can store an array of primitive
	*			or user-defined values. Different Datum objects
	*			can store values of different types.
	*/
	class Datum final
	{
	public:

		/**
		*	@brief	Default constructor that initializes the
		*			Datum to be empty with Unknown type.
		*/
		Datum();

		/**
		*	@brief	Copy constructor for the Datum that takes
		*			another Datum object and performs a deep
		*			copy.
		*	@param	other a const reference to the Datum object
		*			to be copied.
		*/
		Datum(const Datum& other);

		/**
		*	@brief	Move constructor for the Datum that takes another
		*			Datum object and moves its data to this Datum
		*	@param	other a const reference to the Datum object to
		*			be moved
		*/
		Datum(Datum&& other);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single integer. Datums constructed this
		*			way are always in internal storage.
		*	@param	i a const reference to the integer that will be
		*			the first element in the Datum.
		*/
		Datum(const std::int32_t& i);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single float. Datums constructed this
		*			way are always in internal storage.
		*	@param	f a const reference to the float that will be
		*			the first element in the Datum.
		*/
		Datum(const std::float_t& f);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single vec4. Datums constructed this
		*			way are always in internal storage.
		*	@param	v a const reference to the vec4 that will be
		*			the first element in the Datum.
		*/
		Datum(const glm::vec4& v);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single mat4x4. Datums constructed this
		*			way are always in internal storage.
		*	@param	m a const reference to the mat4x4 that will be
		*			the first element in the Datum.
		*/
		Datum(const glm::mat4x4& m);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single Scope pointer. Datums constructed this
		*			way are always in internal storage.
		*	@param	t a const reference to the Scope pointer that will be
		*			the first element in the Datum.
		*/
		Datum(Scope* const& t);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single string. Datums constructed this
		*			way are always in internal storage.
		*	@param	s a const reference to the string that will be
		*			the first element in the Datum.
		*/
		Datum(const std::string& s);

		/**
		*	@brief	Scalar copy constructor that creates a Datum
		*			with a single RTTI pointer. Datums constructed this
		*			way are always in internal storage.
		*	@param	r a const reference to the RTTI pointer that will be
		*			the first element in the Datum.
		*/
		Datum(RTTI* const& r);

		/**
		*	@brief	The copy assignment operator is overloaded to copy
		*			one datum into another
		*	@param	other a const reference of the Datum to be copied
		*	@return	reference to the Datum to which the data was copied
		*/
		Datum& operator=(const Datum& other);

		/**
		*	@brief	The move assignment operator is overloaded to move the
		*			contents of one datum into another
		*	@param	other an rvalue reference to the datum whose contents
		*			are to be moved
		*	@return	reference to the Datum to which the data was moved
		*/
		Datum& operator=(Datum&& other);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single integer and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	i a const reference to the integer to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(const std::int32_t& i);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single float and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	f a const reference to the float to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(const std::float_t& f);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single vec4 and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	v a const reference to the vec4 to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(const glm::vec4& v);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single mat4x4 and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	m a const reference to the mat4x4 to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(const glm::mat4x4& m);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single Scope pointer and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	t a const reference to the Scope pointer to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(Scope* const& t);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single string and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	s a const reference to the string to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(const std::string& s);

		/**
		*	@brief	The copy assignment operator is overloaded to take a
		*			single RTTI pointer and either push it into the array as a
		*			new element, or replace the already existing first element
		*			of the Datum.
		*	@param	r a const reference to the RTTI pointer to be copied.
		*	@return reference to the Datum to which the data was copied
		*/
		Datum& operator=(RTTI* const& r);

		/**
		*	@brief The comparison operator is overloaded to compare
		*			the data members of the two Datums.
		*	@param	other const reference of the Datum with which
		*			the comparison is to take place
		*	@return bool indicating whether the two Datums are equal.
		*			Returns true if equal.
		*/
		bool operator==(const Datum& other) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another integer
		*	@param	i const reference to the integer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(const std::int32_t& i) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another float
		*	@param	f const reference to the float to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(const std::float_t& f) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another vec4
		*	@param	v const reference to the vec4 to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(const glm::vec4& v) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another mat4x4
		*	@param	m const reference to the mat4x4 to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(const glm::mat4x4& m) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another Scope pointer
		*	@param	t const reference to the Scope pointer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(Scope* const& t) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another string
		*	@param	s const reference to the string to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(const std::string& s) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another RTTI pointer
		*	@param	r const reference to the RTTI pointer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			true if equal.
		*/
		bool operator==(RTTI* const& r) const;

		/**
		*	@brief The comparison operator is overloaded to compare
		*			the data members of the two Datums.
		*	@param	other const reference of the Datum with which
		*			the comparison is to take place
		*	@return bool indicating whether the two Datums are equal.
		*			Returns false if equal.
		*/
		bool operator!=(const Datum& other) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another integer
		*	@param	i const reference to the integer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(const std::int32_t& i) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another vec4
		*	@param	v const reference to the vec4 to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(const std::float_t& f) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another vec4
		*	@param	v const reference to the vec4 to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(const glm::vec4& v) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another mat4x4
		*	@param	m const reference to the mat4x4 to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(const glm::mat4x4& m) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another Scope pointer
		*	@param	t const reference to the Scope pointer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(Scope* const& t) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another string
		*	@param	s const reference to the string to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(const std::string& s) const;

		/**
		*	@brief	The comparison operator is overloaded to compare
		*			a Datum with a single element with another RTTI pointer
		*	@param	r const reference to the RTTI pointer to be compared with
		*	@return	bool that indicates whether they are equal. Returns
		*			false if equal.
		*/
		bool operator!=(RTTI* const& r) const;

		/**
		*	@brief	This operator overload allows a syntactically simplified access
		*			to the nested scopes in the Datum
		*	@param	index the index of the scope to access
		*	@return reference to the Scope you want to access
		*/
		Scope& operator[](const std::uint32_t index) const;

		/**
		*	@brief	Method that return the type of the Datum
		*	@return	An EDatumType that represents the type of the Datum
		*/
		EDatumType Type() const;

		/**
		*	@brief	Method to set the type of the Datum
		*	@param	datumType a const EDatumType that represents the new
		*			type of the Datum
		*/
		void SetType(const EDatumType datumType);

		/**
		*	@brief	Method to obtain the size (number of elements) of the Datum
		*	@return	Integer that represents the size (number of elements) of the Datum
		*/
		std::uint32_t Size() const;

		/**
		*	@brief	Method to change the capacity of a Datum and also default construct
		*			the allocated memory. This method can be used to expand as well as
		*			shrink the data array in the Datum.
		*	@param	size a const integer that represents the new size of the Datum
		*/
		void Resize(const std::uint32_t size);

		/**
		*	@brief	Method to completely clear the array and free any memory allocated
		*/
		void Clear();

		/**
		*	@brief	Method to remove an element in the datum by passing in the index of that
		*			element
		*	@param	index a const unsigned integer that indicates the location of the element
		*			that needs to be removed
		*/
		void RemoveByIndex(const std::uint32_t index);


		/**
		*	@brief	Method to remove the specified element
		*	@param	data const integer reference to the element to be removed
		*/
		void Remove(const std::int32_t& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const float reference to the element to be removed
		*/
		void Remove(const std::float_t& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const vec4 reference to the element to be removed
		*/
		void Remove(const glm::vec4& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const mat4x4 reference to the element to be removed
		*/
		void Remove(const glm::mat4x4& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const Scope pointer reference to the element to be removed
		*/
		void Remove(Scope* const& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const string reference to the element to be removed
		*/
		void Remove(const std::string& data);

		/**
		*	@brief	Method to remove the specified element
		*	@param	data const RTTI pointer reference to the element to be removed
		*/
		void Remove(RTTI* const& data);

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the Remove methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which Remove is called
		*	@return	if none of the exceptions are thrown, returns true
		*/
		bool RemoveMethodExceptionHandler(const EDatumType datumType) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const integer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(const std::int32_t& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const float reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(const std::float_t& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const vec4 reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(const glm::vec4& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const mat4x4 reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(const glm::mat4x4& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const Scope pointer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(Scope* const& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const string reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(const std::string& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found.
		*	@param	data const RTTI pointer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		std::uint32_t Find(RTTI* const& data);

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const integer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(const std::int32_t& data) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const float reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(const std::float_t& data) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const vec4 reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(const glm::vec4& data) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const mat4x4 reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(const glm::mat4x4& data) const;
		
		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const Scope pointer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(Scope* const& data) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const string reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(const std::string& data) const;

		/**
		*	@brief	Method to find the index of a specified element.
		*			Returns the size of the array if element is not found. (const version)
		*	@param	data const RTTI pointer reference to the data that is to be searched for
		*			in the Datum
		*	@return	integer that represents the index of the element to be found, is equal
		*			to the size of the array if the element is not found
		*/
		const std::uint32_t Find(RTTI* const& data) const;

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the Find methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which Find is called
		*	@return	if none of the exceptions are thrown, returns true
		*/
		bool FindMethodExceptionHandler(const EDatumType datumType) const;

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum.
		*	@param	data integer pointer to the array
		*	@param	size the size of that array
		*/
		void SetStorage(std::int32_t* data, const std::uint32_t size);

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum.
		*	@param	data float pointer to the array
		*	@param	size the size of that array
		*/
		void SetStorage(std::float_t* data, const std::uint32_t size);

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum.
		*	@param	data vec4 pointer to the array
		*	@param	size the size of that array
		*/
		void SetStorage(glm::vec4* data, const std::uint32_t size);

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum.
		*	@param	data mat4x4 pointer to the array
		*	@param	size the size of that array
		*/
		void SetStorage(glm::mat4x4* data, const std::uint32_t size);

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum. Set() and
		*			Get() will work since they don't affect size or capacity.
		*	@param	data string pointer to the array
		*	@param	size the size of that array
		*/
		void SetStorage(std::string* data, const std::uint32_t size);

		/**
		*	@brief	Given an array and the number of elements in it, this method assigns the
		*			internal values array pointer to the given array and the size and capacity
		*			is set to the size of the array. This datum is then tagged to be external
		*			storage, meaning its size and capacity cannot be modified, ie, methods like
		*			PushBack(), PopBack(), Remove(), etc will not work on this Datum.
		*	@param	data RTTI double pointer which represents an array of RTTI pointers
		*	@param	size the size of that array
		*/
		void SetStorage(RTTI** data, const std::uint32_t size);

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the SetStorage methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which is SetStorage is called
		*	@param	size the size of the array
		*	@return	if none of the exceptions are thrown, returns true
		*/
		bool SetStorageMethodExceptionHandler(const EDatumType datumType, const std::uint32_t size);

		/**
		*	@brief	Method to set a new maximum capacity for the Datum
		*	@param	capacity a const unsigned integer that represents
		*			the new capacity of the Datum
		*/
		void Reserve(std::uint32_t capacity);
		
		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the integer to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(const std::int32_t& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the float to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(const std::float_t& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the vec4 to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(const glm::vec4& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the mat4x4 to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(const glm::mat4x4& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the Scope pointer to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(Scope* const& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the string to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(const std::string& data, const std::uint32_t index = 0);

		/**
		*	@brief	Given a value and an optional index (defaults to 0), this
		*			method assigns to the appropriate element in the values array
		*			the given value.
		*	@param	data a const reference to the RTTI pointer to be set
		*	@param	index the index of the element to be set (defaults to 0)
		*/
		void Set(RTTI* const& data, const std::uint32_t index = 0);

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the Set methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which is Set is called
		*	@param	index the index of the element to be set
		*	@return	if none of the exceptions are thrown, returns true
		*/
		bool SetMethodExceptionHandler(const EDatumType datumType, const std::uint32_t index) const;

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the integer to be pushed
		*/
		void PushBack(const std::int32_t& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the float to be pushed
		*/
		void PushBack(const std::float_t& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the vec4 to be pushed
		*/
		void PushBack(const glm::vec4& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the mat4x4 to be pushed
		*/
		void PushBack(const glm::mat4x4& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the Scope pointer to be pushed
		*/
		void PushBack(Scope* const& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the string to be pushed
		*/
		void PushBack(const std::string& data);

		/**
		*	@brief	Method to append the given item to the end of the values array
		*	@param	data a const reference to the RTTI pointer to be pushed
		*/
		void PushBack(RTTI* const& data);

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the PushBack methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which is PushBack is called
		*	@return	if none of the exceptions are thrown, returns true
		*/
		bool PushBackMethodExceptionHandler(const EDatumType datumType);

		/**
		*	@brief	Given an optional index (defaults to 0), this method returns the
		*			appropriate element from the values array. It is a templated method
		*			that is specialized for the supported datatypes.
		*	@param	index the index of the element to get
		*/
		template<typename T>
		T& Get(const std::uint32_t index = 0);

		template<>
		std::int32_t& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::EInteger, index);

			return mData.i[index];
		}

		template<>
		std::float_t& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::EFloat, index);

			return mData.f[index];
		}

		template<>
		glm::vec4& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::EVector4, index);

			return mData.v[index];
		}

		template<>
		glm::mat4x4& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::EMatrix4x4, index);

			return mData.m[index];
		}

		template<>
		Scope*& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::ETable, index);

			return mData.t[index];
		}

		template<>
		std::string& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::EString, index);

			return mData.s[index];
		}

		template<>
		RTTI*& Get(const std::uint32_t index)
		{
			GetMethodExceptionHandler(EDatumType::ERTTIPointer, index);

			return mData.r[index];
		}
		
		/**
		*	@brief	Given an optional index (defaults to 0), this method returns the
		*			appropriate element from the values array. It is a templated method
		*			that is specialized for the supported datatypes. (const version)
		*	@param	index the index of the element to get
		*/
		template<typename T>
		const T& Get(const std::uint32_t index = 0) const;

		template<>
		const std::int32_t& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::EInteger, index);

			return mData.i[index];
		}

		template<>
		const std::float_t& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::EFloat, index);

			return mData.f[index];
		}

		template<>
		const glm::vec4& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::EVector4, index);

			return mData.v[index];
		}

		template<>
		const glm::mat4x4& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::EMatrix4x4, index);

			return mData.m[index];
		}

		template<>
		Scope* const& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::ETable, index);

			return mData.t[index];
		}

		template<>
		const std::string& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::EString, index);

			return mData.s[index];
		}

		template<>
		RTTI* const& Get(const std::uint32_t index) const
		{
			GetMethodExceptionHandler(EDatumType::ERTTIPointer, index);

			return mData.r[index];
		}

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the Get methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which is Get is called
		*	@param	index the index of the element to get
		*/
		void GetMethodExceptionHandler(const EDatumType datumType, const std::uint32_t index) const;

		/**
		*	@brief	Method to remove the last item of the values array in the Datum and
		*			return its value.
		*	@return the value of the item that was popped
		*/
		template<typename T>
		T PopBack();

		template<>
		std::int32_t PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::EInteger);

			std::int32_t data = mData.i[--mSize];
			return data;
		}

		template<>
		std::float_t PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::EFloat);

			std::float_t data = mData.f[--mSize];
			return data;
		}

		template<>
		glm::vec4 PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::EVector4);

			glm::vec4 data = mData.v[--mSize];
			return data;
		}

		template<>
		glm::mat4x4 PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::EMatrix4x4);

			glm::mat4x4 data = mData.m[--mSize];
			return data;
		}

		template<>
		Scope* PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::ETable);

			Scope* data = mData.t[--mSize];
			return data;
		}

		template<>
		std::string PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::EString);

			std::string data = mData.s[--mSize];
			mData.s[mSize].~basic_string();
			return data;
		}

		template<>
		RTTI* PopBack()
		{
			PopBackMethodExceptionHandler(EDatumType::ERTTIPointer);

			RTTI* data = mData.r[--mSize];
			return data;
		}

		/**
		*	@brief	Method that performs all the checks for exceptions that is called
		*			in all the PopBack methods, to avoid redundancy in code.
		*	@param	datumType the DatumType of the datum for which is PopBack is called
		*/
		void PopBackMethodExceptionHandler(const EDatumType datumType) const;

		/**
		*	@brief	Given an STL string and an optional index (defaults to 0), this method
		*			parses the string and converts it to the appropriate data type and sets
		*			it in the given index position in the values array of the Datum. This
		*			cannot be done for RTTI Pointers.
		*	@param	data STL string that needs to be parsed to actually get the data
		*	@param	index the location in the values array that is to be set
		*/
		void SetFromString(const std::string data, const std::uint32_t index = 0);

		/**
		*	@brief	Given an optional index (defaults to 0), this method returns an STL string
		*			representing the appropriate element in the values array.
		*	@param	index the location of the element to be converted to a string
		*	@return	STL string that represents the appropriate element in the values array
		*/
		std::string ToString(const std::uint32_t index = 0);

		/**
		*	@brief	Method to check whether the datum is external storage
		*	@return	bool indicating whether the datum is external storage
		*/
		bool IsExternalStorage() const;

		/**
		*	@brief	Destructor for the Datum class that ensures there are no memory leaks.
		*/
		~Datum();

	private:

		/**
		*	@brief	A union that contains pointers of the different supported datatypes.
		*			All these pointers point to the same location. But a datum can only
		*			have a single type of data, so, only one of these pointers can actually
		*			look at the allocated memory in a way that makes sense.
		*/
		union DatumType
		{
			std::int32_t* i;
			std::float_t* f;
			glm::vec4* v;
			glm::mat4x4* m;
			Scope** t;
			std::string* s;
			RTTI** r;
			void* vp;

			/**
			*	@brief	Default constructor for the union
			*/
			DatumType() : vp(nullptr) {}

			/**
			*	@brief	Copy constructor for the union, which
			*			is defaulted
			*	@param	rhs const reference of the union to copy
			*/
			DatumType(const DatumType& rhs) = default;

			/**
			*	@brief	Copy assignment operator overload for the union
			*	@param	rhs const reference of the union to be copied
			*	@return	reference to the union after the assignment
			*/
			DatumType& operator=(const DatumType& rhs) = default;
		};

		DatumType mData;				/**<	The values array of the Datum	*/
		std::uint32_t mSize;			/**<	The size of the values array	*/
		std::uint32_t mCapacity;		/**<	The capacity of the values array	*/
		EDatumType mDatumType;			/**<	The type of data that this Datum stores	*/
		bool mIsInternalStorage;		/**<	Bool that indicates whether this Datum points to internal storage or external storage	*/

		static const size_t TypeToSizeMapping[static_cast<std::uint32_t>(EDatumType::ENumberOfSupportedDatatypes)];	/**<	A static array that stores the size of each of the supported datatypes indexed by their enum representations	*/
	};
}