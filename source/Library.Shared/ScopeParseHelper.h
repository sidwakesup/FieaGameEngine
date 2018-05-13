#pragma once

#include "Scope.h"
#include "IParseHelper.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The ScopeParseHelper is a specialized helper that derives from the base interface.
	*			It is designed to specifically handle json grammars that pertain to entering data
	*			into scopes.
	*/
	class ScopeParseHelper final : public IParseHelper
	{
	public:

		/**
		*	@brief	The Metadata struct is used to store data in an intermediary format before appending it as a datum
		*			to the scope.
		*/
		typedef struct
		{
			std::string key;
			Json::Value root;
			std::string type;
		} Metadata;


		/**
		*	@brief	The default constructor is defaulted.
		*/
		ScopeParseHelper() = default;

		/**
		*	@brief	The copy constructor is defaulted.
		*/
		ScopeParseHelper(const ScopeParseHelper& other) = default;

		/**
		*	@brief	The move constructor is defaulted.
		*/
		ScopeParseHelper(ScopeParseHelper&& other) = default;

		/**
		*	@brief	The copy assignment operator is defaulted.
		*/
		ScopeParseHelper& operator=(const ScopeParseHelper& other) = default;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		ScopeParseHelper& operator=(ScopeParseHelper&& other) = default;

		/**
		*	@brief	The destructor is defaulted.
		*/
		~ScopeParseHelper() = default;

		/**
		*	@brief	The Clone method returns a heap instantiated ScopeParseHelper
		*	@return	reference to the heap instantiated clone
		*/
		ScopeParseHelper& Clone() const override;

		/**
		*	@brief	The StartHandler adds the given key to the stack if it contains nested scopes and appends
		*			a scope corresponding to that key. It also caches off that key in the Metadata.
		*	@param	key the key of the Json key value pair being parsed
		*	@param	root the Json Value object pertaining to the key 'key'
		*	@param	sharedData reference to the sharedData object that this parser is to work with
		*	@return	if the helper was able to handle the data
		*/
		bool StartHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) override;

		/**
		*	@brief	The ValueHandler is called when the Json Value is not an object but a basic key value pair,
		*			and caches of the type and value of this Json Value in the Metadata.
		*	@param	key the key of the Json key value pair being parsed
		*	@param	root the Json Value object pertaining to the key 'key'
		*	@param	sharedData reference to the sharedData object that this parser is to work with
		*	@return	if the helper was able to handle the data
		*/
		bool ValueHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) override;

		/**
		*	@brief	The end handler is responsible for coming out of the nested scope by popping off the top of the stack
		*			and resetting the Scope pointer in the sharedData object. It is also responsible for the actual insertion
		*			of the datum in the scope with the corresponding data.
		*	@param	key the key of the Json key value pair being parsed
		*	@param	root the Json Value object pertaining to the key 'key'
		*	@param	sharedData reference to the sharedData object that this parser is to work with
		*	@return	if the helper was able to handle the data
		*/
		bool EndHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) override;


	private:

		Vector<std::string> mKeyStack;		/**<	The stack that keeps track of the nesting of scopes by adding their corresponding keys.	*/
		Metadata mElement;					/**<	The Metadata struct that stores the data that is to be pushed into the datum by the end handler.	*/
	};

}