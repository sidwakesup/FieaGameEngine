#pragma once

#include "Scope.h"
#include "ParseMaster.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The Scope shared data class is a specialized derivative of the
	*			shared data class. It contains a pointer to a scope that will
	*			contain all the data extracted from the json file.
	*/
	class ScopeSharedData final : public ParseMaster::SharedData
	{

		RTTI_DECLARATIONS(ScopeSharedData, ParseMaster::SharedData)

	public:

		/**
		*	@brief	Default constructor that instantiates the scope on the heap
		*/
		ScopeSharedData();

		/**
		*	@brief	Parameterized constructor for the scope shared data class that
		*			instantiates a copy constructed scope from the given parameter
		*			on the heap
		*	@param	otherScopeData the scope that is to be used to instantiate the scope
		*			that this class contains on the heap
		*/
		explicit ScopeSharedData(Scope& otherScopeData);

		/**
		*	@brief	Copy constructor that deep copies the scope and instantiates it on the heap
		*	@param	other the ScopeSharedData to be copied
		*/
		ScopeSharedData(const ScopeSharedData& other);

		/**
		*	@brief	The move constructor for the ScopeSharedData has default behavior.
		*	@param	other the ScopeSharedData to be moved
		*/
		ScopeSharedData(ScopeSharedData&& other) = default;

		/**
		*	@brief	The copy assignment operator is overloaded to deep copy the scope and instantiate
		*			it on the heap.
		*	@param	other the ScopeSharedData to be copied
		*	@return	reference to the ScopeSharedData
		*/
		ScopeSharedData& operator=(const ScopeSharedData& other);

		/**
		*	@brief	The move assignment operator for ScopeSharedData has default behavior.
		*	@param	other the ScopeSharedData to be moved
		*	@return	reference to the ScopeSharedData
		*/
		ScopeSharedData& operator=(ScopeSharedData&& other) = default;

		/**
		*	@brief	The destructor for the ScopeSharedData explicitly deletes the heap instantiated scope
		*/
		~ScopeSharedData();

		/**
		*	@brief	The Clone method copies the current ScopeSharedData into a heap instantiated ScopeSharedData
		*	@return	reference to the heap instantiated clone
		*/
		ScopeSharedData& Clone() const override;

		Scope* mData;		/**<	Pointer to the Scope	*/

	};

}