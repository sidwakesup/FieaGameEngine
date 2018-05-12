#pragma once

#include "SList.h"
#include "Vector.h"
#include "HashMap.h"
#include "Scope.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The default hash function for an unsigned 64-bit integer.
	*			This functor is defined to be used in the static hashmap
	*			that keeps track of the prescribed attributes.
	*/
	template<>
	class DefaultHashFunction<std::uint64_t>
	{
	public:
		size_t operator()(std::uint64_t k) const
		{
			return Hash(std::to_string(k));
		}
	};

	/**
	*	@brief	The Attributed class derives from Scope. Any time an object
	*			of a class is created, we want to create datum and scope objects
	*			which mirror those objects. Attributed class is an interface
	*			that makes this mirroring easy to code.
	*/
	class Attributed : public Scope
	{

		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		
		/**
		*	@brief	The default constructor initializes member variables.
		*/
		Attributed();

		/**
		*	@brief	The copy constructor that copies one attributed interface
		*			into another. A deep copy is performed to avoid memory
		*			leaks and invalid pointers.
		*	@param	other a const reference to the Attributed class to be copied
		*/
		Attributed(const Attributed& other);

		/**
		*	@brief	The move constructor that moves one attributed interface
		*			into another. Steps are taken to avoid memory
		*			leaks and invalid pointers.
		*	@param	other an rvalue reference to the Attributed class to be moved
		*/
		Attributed(Attributed&& other);

		/**
		*	@brief	Method to return a clone of the current Attributed object as a Scope pointer.
		*			This method polymorphically overrides the Clone method defined in Scope class.
		*	@return	Scope pointer pointing to the newly created Attributed.
		*/
		virtual Scope* Clone() override;

		/**
		*	@brief	The copy assignment operator is overloaded to copy one attributed
		*			interface into another. A deep copy is performed to avoid memory
		*			leaks and invalid pointers.
		*	@param	other a const reference to the Attributed class to be copied
		*	@return	reference to the Attributed interface obtained after the copy
		*/
		Attributed& operator=(const Attributed& other);

		/**
		*	@brief	The move assignment operator is overloaded to move one Attributed
		*			interface into another. Steps are taken to avoid memory leaks and
		*			invalid pointers.
		*	@param	other an rvalue reference to the Attributed class to be moved
		*	@return	reference to the Attributed interface obtained after the move
		*/
		Attributed& operator=(Attributed&& other);

		/**
		*	@brief	Method to check whether the given key corresponds to an attribute
		*			in the Attributed interface.
		*	@param	key the string that represents the key we are testing for
		*	@return	bool that indicates whether the given key corresponds to an
		*			attribute.
		*/
		bool IsAttribute(const std::string& key) const;

		/**
		*	@brief	Method to check whether the given key corresponds to a prescribed
		*			attribute in the Attributed interface.
		*	@param	key the string that represents the key we are testing for
		*	@return	bool that indicates whether the given key corresponds to a
		*			prescribed attribute.
		*/
		bool IsPrescribedAttribute(const std::string& key) const;

		/**
		*	@brief	Method to check whether the given key corresponds to an auxiliary
		*			attribute in the Attributed interface.
		*	@param	key the string that represents the key we are testing for
		*	@return	bool that indicates whether the given key corresponds to an
		*			auxiliary attribute.
		*/
		bool IsAuxiliaryAttribute(const std::string& key) const;

		/**
		*	@brief	Method to add an auxiliary attribute to a class deriving from
		*			the Attributed interface.
		*	@param	key a const string that is the key corresponding to the new
		*			auxiliary attribute we are appending
		*	@return	reference to the Datum that contains the new auxiliary attribute
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& key);

		/**
		*	@brief	Method to get the vector of attributes.
		*/
		const Vector<std::pair<std::string, Datum>*>& GetAttributes() const;

		/**
		*	@brief	Method to get the vector of prescribed attributes.
		*/
		Vector<std::pair<std::string, Datum>*> GetPrescribedAttributes() const;

		/**
		*	@brief	Method to get the vector of auxiliary attributes.
		*/
		Vector<std::pair<std::string, Datum>*> GetAuxiliaryAttributes() const;

		/**
		*	@brief	The destructor is defaulted to ensure
		*			there are no memory leaks.
		*/
		virtual ~Attributed() = default;

	protected:

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const int that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, const std::int32_t& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const float that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, const std::float_t& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const vector4 that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, const glm::vec4& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const 4x4 matrix that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, const glm::mat4x4& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const Scope pointer that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, Scope* const& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const string that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, const std::string& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an internal prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	defaultValue a const RTTI pointer that the prescribed attribute is initialized with
		*	@param	count the number of such prescribed attributes to create
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddInternalPrescribedAttribute(const std::string& name, RTTI* const& defaultValue, std::uint32_t& count);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external int for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, std::int32_t* externalData, const std::uint32_t size);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external float for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, std::float_t* externalData, const std::uint32_t size);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external vector4 for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, glm::vec4* externalData, const std::uint32_t size);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external 4x4 matrix for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, glm::mat4x4* externalData, const std::uint32_t size);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external string for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, std::string* externalData, const std::uint32_t size);

		/**
		*	@brief	Method to add an external prescribed attribute to the Attributed derived class.
		*	@param	name a const string that refers to the name of the prescribed attribute
		*	@param	externalData a pointer to the external RTTI pointer for which the attribute is created
		*	@param	size the size of the external array
		*	@return	pointer to the Datum that is the prescribed attribute
		*/
		Datum* AddExternalPrescribedAttribute(const std::string& name, RTTI** externalData, const std::uint32_t size);

		/**
		*	@brief	Helper method to add the name to the static
		*			hashmap that keeps track of the prescribed
		*			attributes.
		*	@param	name the string key that corresponds to the
		*			prescribed attribute.
		*/
		void AddToPrescribedAttributes(const std::string& name);

		/**
		*	@brief	Method to initialize the attributes of
		*			the class. It is a pure virtual function 
		*			and is expected to be implemented in the
		*			derived classes.
		*/
		virtual void InitializeAttributes();

		/**
		*	@brief	Method to update the list of prescribed
		*			attributes whenever the list is reinitialized.
		*			It is a pure virtual function and is expected
		*			to be implemented in the derived classes.
		*/
		virtual void UpdatePrescribedAttributes();

		/**
		*	@brief	The Attributed interface contains a static hashmap that is shared
		*			by all the instances of all the derived classes of this interface.
		*			This hashmap keeps track of all the prescribed attributes, hashed
		*			based on the instance id of the different classes.
		*/
		static HashMap<std::uint64_t, Vector<std::string>> mPrescribedAttributes;

	};

}