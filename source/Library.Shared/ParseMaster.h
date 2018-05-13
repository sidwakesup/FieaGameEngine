#pragma once

#include "Vector.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	class IParseHelper;		//forward reference to the parse helper

	/**
	*	@brief	The ParseMaster class is responsible for parsing the Json file
	*			and delegating the tasks of storing that data into sharedData object
	*			to its helpers.
	*/
	class ParseMaster final
	{
	public:

		/**
		*	@brief	This is the abstract base class for the shared data object that will contain
		*			the data extracted from Json.
		*/
		class SharedData : public RTTI
		{
			friend class ParseMaster;		//ParseMaster is a friend so that it can access the private members

			RTTI_DECLARATIONS(SharedData, RTTI)

		public:

			/**
			*	@brief	The default constructor is defaulted.
			*/
			SharedData() = default;

			/**
			*	@brief	The copy constructor is defaulted.
			*/
			SharedData(const SharedData& other) = default;

			/**
			*	@brief	The move constructor is defaulted.
			*/
			SharedData(SharedData&& other) = default;

			/**
			*	@brief	The copy assignment operator is defaulted.
			*/
			SharedData& operator=(const SharedData& other) = default;

			/**
			*	@brief	The move assignment operator is defaulted.
			*/
			SharedData& operator=(SharedData&& other) = default;

			/**
			*	@brief	The destructor is defaulted.
			*/
			virtual ~SharedData() = default;

			/**
			*	@brief	This is a pure virtual method that is overridden and implemented
			*			in derived classes. See also ScopeSharedData::Clone().
			*/
			virtual SharedData& Clone() const = 0;

			/**
			*	@brief	Method to indicate whether the shared data object is a clone.
			*	@return	bool that indicates whether the shared data object is a clone.
			*/
			bool IsClone() const;

		protected:

			bool mIsClone;		/**<	bool that indicates whether this shared data object is a clone.	*/

		};

		/**
		*	@brief	Parameterized constructor that takes in a shareddata object and
		*			creates a parse master that will fill in the data into this shared
		*			data object.
		*	@param	sharedData the sharedData object pertaining to this parse master.
		*/
		explicit ParseMaster(SharedData& sharedData);

		/**
		*	@brief	The copy constructor is deleted.
		*/
		ParseMaster(const ParseMaster& other) = delete;

		/**
		*	@brief	The move constructor is defaulted.
		*/
		ParseMaster(ParseMaster&& other) = default;

		/**
		*	@brief	The copy assignment operator is deleted.
		*/
		ParseMaster& operator=(const ParseMaster& other) = delete;

		/**
		*	@brief	The move assignment operator is defaulted.
		*/
		ParseMaster& operator=(ParseMaster&& other) = default;

		/**
		*	@brief	The destructor explicitly deletes its helpers and the shared data if it is a clone.
		*/
		~ParseMaster();

		/**
		*	@brief	The Clone method creates a heap instantiated copy of this master. The clone's helpers
		*			and shared data object are also heap instantiated clones of the originals.
		*	@return	A reference to the clone
		*/
		ParseMaster& Clone() const;

		/**
		*	@brief	Method to add a helper to the master's list of helpers
		*	@param	parseHelper the helper to be added
		*/
		void AddHelper(IParseHelper& parseHelper);

		/**
		*	@brief	Method to remove a helper from the master's list of helpers
		*	@param	parseHelper the helper to be removed
		*	@return	reference to the removed helper
		*/
		IParseHelper& RemoveHelper(IParseHelper& parseHelper);

		/**
		*	@brief	Method to parse json data stored in a string
		*	@oaram	buffer string that contains the json data
		*/
		void Parse(const std::string& buffer);

		/**
		*	@brief	Method to parse json data stored in a stream
		*	@param	stream the input steam to be parsed
		*/
		void Parse(std::istream& stream);

		/**
		*	@brief	Method to parse json data from a file.
		*	@param	fileName name of the file to read the json data from
		*/
		void ParseFromFile(const std::string& fileName);

		/**
		*	@brief	Method to find the helper that is capable of extracting data
		*			from the Json Value object and delegating the task of storing
		*			that data into the shared data object
		*	@param	root the json value object
		*/
		void DelegateTask(Json::Value& root);

		/**
		*	@brief	Method to get the name of the json file that was parsed.
		*	@return	the name of the file
		*/
		std::string& GetFileName();

		/**
		*	@brief	Method to get the associated shared data object
		*	@return	reference to the shared data object
		*/
		SharedData& GetSharedData() const;

		/**
		*	@brief	Method to set the shared data object associated with this master
		*	@param	sharedData the shared data object
		*/
		void SetSharedData(SharedData& sharedData);

		/**
		*	@brief	Method that indicates whether this master is a clone
		*	@return	bool that indicates whether this master is a clone
		*/
		bool IsClone() const;

	private:

		Vector<IParseHelper*> mParseHelpers;		/**<	List of helpers the master can delegate tasks to	*/
		SharedData& mSharedData;					/**<	The associated shared data object	*/
		std::string mFileToParse;					/**<	Name of the file that was parsed.	*/
		bool mIsClone;								/**<	bool that indicates whether this master is a clone.	*/

	};

}