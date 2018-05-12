#pragma once

#include "ParseMaster.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The IParseHelper class is the abstract base class for helpers
	*			that the parse master can use. It contains some pure virtual methods
	*			that must be overridden by classes that derive from it.
	*/
	class IParseHelper
	{
	public:

		/**
		*	@brief	The default constructor is defaulted.
		*/
		IParseHelper() = default;

		/**
		*	@brief	The copy constructor is defaulted.
		*/
		IParseHelper(const IParseHelper& other) = default;

		/**
		*	@brief	The move constructor is defaulted.
		*/
		IParseHelper(IParseHelper&& other) = default;

		/**
		*	@brief	The copy assignment operator is defaulted.
		*/
		IParseHelper& operator=(const IParseHelper& other) = default;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		IParseHelper& operator=(IParseHelper&& other) = default;

		/**
		*	@brief	The destructor is defaulted.
		*/
		virtual ~IParseHelper() = default;

		/**
		*	@brief	This is a pure virtual method that is overridden and implemented
		*			in derived classes. See also ScopeParseHelper::Clone().
		*/
		virtual IParseHelper& Clone() const = 0;

		/**
		*	@brief	Method to indicate whether the helper is a clone.
		*	@return	bool that indicates whether the helper is a clone.
		*/
		bool IsClone() const;

		/**
		*	@brief	This is a pure virtual method that is overridden and implemented
		*			in derived classes. See also ScopeParseHelper::StartHandler().
		*/
		virtual bool StartHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) = 0;

		/**
		*	@brief	This is a pure virtual method that is overridden and implemented
		*			in derived classes. See also ScopeParseHelper::ValueHandler().
		*/
		virtual bool ValueHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) = 0;

		/**
		*	@brief	This is a pure virtual method that is overridden and implemented
		*			in derived classes. See also ScopeParseHelper::EndHandler().
		*/
		virtual bool EndHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData) = 0;

	protected:

		bool mIsClone;		/**<	bool that indicates whether this helper is a clone.	*/

	};

}