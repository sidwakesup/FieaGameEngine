#pragma once

#include "SList.h"
#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The class is implementation of a Scope, which is a
	*			table that creates a dictionary of name-value pairs
	*			where Datum objects are the values. Each entry in the
	*			Scope has a name and a Datum, where the Datum represents
	*			an array of values of a single type. An entry in a Scope
	*			can refer to another Scope table and thereby provide the
	*			means to create user-defined types which are a Datum type.
	*/
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

	public:

		typedef std::pair<std::string, Datum> LookupTableEntry;			/**<	the string-Datum pair is typedef'd for more readability	*/

		/**
		*	@brief	Method to export the data in the Scope as a string.
		*	@return	string that contains the data of the scope
		*/
		virtual std::string ToString() const override;

		/**
		*	@brief	Method to compare two Scopes by overriding the method
		*			defined in RTTI, which Scope inherits from.
		*	@param	rhs a const RTTI* which needs to be interpreted as a
		*			Scope in this case for the comparison to take place.
		*	@return	bool indicating whether the two Scopes are equal.
		*/
		virtual bool Equals(const RTTI* rhs) const override;

		/**
		*	@brief	Default constructor for the Scope
		*/
		Scope();

		/**
		*	@brief	Copy constructor for the Scope
		*	@param	other a const reference to the Scope to be copied
		*/
		Scope(const Scope& other);

		/**
		*	@brief	Move constructor for the Scope
		*	@param	other a const reference to the Scope to be moved
		*/
		Scope(Scope&& other);

		/**
		*	@brief	Parameterized constructor for the Scope
		*	@param	capacity a const unsigned integer that indicates the
		*			capacity of the Scope
		*/
		explicit Scope(const std::uint32_t& capacity);

		/**
		*	@brief	The copy assignment operator is overloaded for deep copying
		*			the Scope
		*	@param	other const reference to the Scope to be copied
		*	@return	reference to the Scope after the assignment
		*/
		Scope& operator=(const Scope& other);

		/**
		*	@brief	The move assignment operator is overloaded for move
		*			semantics
		*	@param	other const reference to the Scope to be movced
		*	@return	reference to the Scope after the assignment
		*/
		Scope& operator=(Scope&& other);

		/**
		*	@brief	Helper function for the copy constructor and the copy
		*			assignment operator overload to implement deep copy.
		*	@param	other const reference to the Scope that is to be copied.
		*/
		void DeepCopy(const Scope& other);

		/**
		*	@brief	Helper function for the move constructor and the move
		*			assignment operator overload to implement move semantics.
		*	@param	other a Scope rvalue reference
		*	@param	name the key associated with the Scope's record in its parent
		*/
		void MoveSemantics(Scope&& other, const std::string& name);

		/**
		*	@brief	Method to return a clone of the current Scope as a Scope pointer.
		*			This method is polymorphically overriden by derived classes.
		*	@return	Scope pointer pointing to the newly created Scope.
		*/
		virtual Scope* Clone();

		/**
		*	@brief	Method to return the address of the Datum associated
		*			with the given name in the Scope, if it exists, nullptr
		*			otherwise
		*	@param	key a const reference to the string that represents the key
		*			associated with the Datum you are looking for
		*	@return	pointer to the Datum if it is found, nullptr otherwise
		*/
		Datum* Find(const std::string& key) const;

		/**
		*	@brief	Method to return the address of the most closely nested Datum
		*			associated with the given name in this Scope or its ancestors,
		*			if it exists, nullptr otherwise.
		*	@param	key a const string reference of the name to search for
		*	@return	pointer to the Datum if it is found, nullptr otherwise
		*/
		Datum* Search(const std::string& key);

		/**
		*	@brief	Method to return the address of the most closely nested Datum
		*			associated with the given name in this Scope or its ancestors,
		*			if it exists, nullptr otherwise. (const version)
		*	@param	key a const string reference of the name to search for
		*	@return	pointer to the Datum if it is found, nullptr otherwise
		*/
		const Datum* Search(const std::string& key) const;

		/**
		*	@brief	Overload for the search method that also passes in an out parameter
		*			that gives us the Scope that contains the Datum we are looking for
		*	@param	key a const string reference of the name to search for
		*	@param	scope a const pointer referenee of type Scope that serves as an out parameter
		*			to store the Scope that you find the datum in, nullptr if the datum 
		*			is not found
		*	@return	pointer to the Datum if it is found, nullptr otherwise
		*/
		Datum* Search(const std::string& key, const Scope*& scope);

		/**
		*	@brief	Overload for the search method that also passes in an out parameter
		*			that gives us the Scope that contains the Datum we are looking for
		*			(const version)
		*	@param	key a const string reference of the name to search for
		*	@param	scope a const pointer reference of type Scope that serves as an out parameter
		*			to store the Scope that you find the datum in, nullptr if the datum
		*			is not found
		*	@return	pointer to the Datum if it is found, nullptr otherwise
		*/
		const Datum* Search(const std::string& key, const Scope*& scope) const;

		/**
		*	@brief	Method that takes in a key and returns a reference to a Datum with the
		*			associated name. If a Datum already exists at that key, return that one,
		*			otherwise create a new one.
		*	@param	key const reference to the key associated to the Datum we are looking for
		*	@return	reference to the found or newly created Datum
		*/
		Datum& Append(const std::string& key);

		/**
		*	@brief	Method that returns a reference to a Scope with the associated name. If a Datum
		*			already exists, reuse it, otherwise create a new one and append the scope to that.
		*	@param	key const reference to the key associated with the Datum we want to append a Scope to
		*	@return	reference to the appended Scope
		*/
		Scope& AppendScope(const std::string& key);

		/**
		*	@brief	Method that takes a reference to the Scope to adopt and the key associated with the Datum
		*			to which we will append this child scope
		*	@param	childToAdopt reference to the Scope that we want to adopt
		*	@param	key a reference to the name associated with the Datum we want to append the child scope to
		*/
		void Adopt(Scope& childToAdopt, const std::string& key);

		/**
		*	@brief	Method to get the parent of the Scope
		*	@return	Scope pointer that contains the address of the
		*			parent scope
		*/
		Scope* GetParent() const;

		/**
		*	@brief	This is simply a wrapper for Append
		*	@param	key const reference to the key associated with the Datum we want to append a Scope to
		*	@return	reference to the appended Scope
		*/
		Datum& operator[](const std::string& key);

		/**
		*	@brief	This operator overload takes in an unsigned integer and returns a reference to the Datum
		*			at the given index. The index values correspond to the order in which items were appended.
		*	@param	index const unsigned integer that indicates the index location of the Datum we want
		*	@return	reference to the Datum we were searching for
		*/
		Datum& operator[](const std::uint32_t& index) const;

		/**
		*	@brief	The comparison operator is overloaded to compare the contents of two Scopes. It is important to
		*			note that the structure is not compared. Only the contents are. (returns true if equal)
		*	@param	other const reference to the Scope to be compared
		*	@return	bool indicating whether the two Scopes are equal
		*/
		bool operator==(const Scope& other) const;

		/**
		*	@brief	The comparison operator is overloaded to compare the contents of two Scopes. It is important to
		*			note that the structure is not compared. Only the contents are. (returns false if equal)
		*	@param	other const reference to the Scope to be compared
		*	@return	bool indicating whether the two Scopes are equal
		*/
		bool operator!=(const Scope& other) const;

		/**
		*	@brief	Method to compare the structure of two scopes. Returns true if equal.
		*	@param	other const reference to the Scope to be compared
		*	@return	bool indicating whether the Scopes are equal
		*/
		bool CompareStructure(const Scope& other) const;

		/**
		*	@brief	Method that takes a reference to a scope and finds the key associated with the Datum that contains the
		*			passed in scope. Returns a default constructed string if the scope is not found
		*	@param	scope const reference to the Scope whose key we want
		*	@return	string that represents the key associated with the Datum that contains the passed in scope
		*/
		std::string FindName(const Scope& scope) const;

		/**
		*	@brief	Method that takes a reference to a scoep and finds the key associated with the datum that contains
		*			the passed in scope. Returns a default constructed string if the scope is not found. In addition to this,
		*			the method also takes in a datum pointer as an out parameter that will point to the datum containing the
		*			scope. The method also takes in a reference to an int as an out parameter that will contain the index of
		*			the scope in the datum
		*	@param	scope a reference to the Scope to be found
		*	@param	datum the out parameter that will point to the datum containing the scope to be found, nullptr otherwise
		*	@param	index the out parameter that will contain the index of the scope
		*	@return string that represents the key associated with the Datum that contains the passed in scope
		*/
		std::string FindContainedScope(const Scope& scope, Datum*& datum, std::uint32_t& index) const;

		/**
		*	@brief	Method to check if the scope is empty.
		*	@return	bool that indicates whether the scope is empty
		*/
		bool IsEmpty() const;

		/**
		*	@brief	Method to get the size of the scope
		*	@return an unsigned integer representing the size of the scope
		*/
		std::uint32_t Size() const;

		/**
		*	@brief	Method to remove the passed in scope from the list of child scope. When the child is orphaned,
		*			its parent is set to nullptr.
		*	@param	child reference to the Scope that is to be orphaned.
		*/
		void OrphanChild(Scope& child);

		/**
		*	@brief	Method to clear the scope and delete all its child scopes.
		*/
		void Clear();

		/**
		*	@brief Destructor for the Scope. Basically calls Clear.
		*/
		virtual ~Scope();

	protected:

		Vector<LookupTableEntry*> mPointersToLookupTable;				/**<	Ordered list of pointers to the string-Datum pairs in the Scope	*/
		HashMap<std::string, Datum> mLookupTable;						/**<	Unordered list of string-Datum pairs in the Scope.	*/

	private:

		Scope* mParent;													/**<	Pointer to a Scope's parent.	*/

	};
}