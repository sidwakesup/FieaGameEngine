#include "pch.h"
#include "ParseMaster.h"
#include "IParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ParseMaster::SharedData)




	bool ParseMaster::SharedData::IsClone() const
	{
		return mIsClone;
	}




	ParseMaster::ParseMaster(SharedData& sharedData) : mParseHelpers(), mSharedData(sharedData), mFileToParse(), mIsClone(false)
	{
	}




	ParseMaster::~ParseMaster()
	{
		if (mIsClone)
		{
			for (auto& helper : mParseHelpers)
			{
				delete helper;
			}

			delete &mSharedData;
		}
	}




	ParseMaster& ParseMaster::Clone() const
	{
		ParseMaster* newMaster = new ParseMaster(mSharedData.Clone());
		for (auto& helper : mParseHelpers)
		{
			newMaster->mParseHelpers.PushBack(&(helper->Clone()));
		}
		newMaster->mIsClone = true;

		return *newMaster;
	}




	void ParseMaster::AddHelper(IParseHelper& parseHelper)
	{
		if (mIsClone)
		{
			throw std::exception("Cannot add a parse helper to a cloned master.");
		}

		mParseHelpers.PushBack(&parseHelper);
	}




	IParseHelper& ParseMaster::RemoveHelper(IParseHelper& parseHelper)
	{
		if (mIsClone)
		{
			throw std::exception("Cannot remove a parse helper from a cloned master.");
		}

		mParseHelpers.Remove(&parseHelper);
		return parseHelper;
	}




	void ParseMaster::Parse(const std::string& buffer)
	{
		std::stringstream bufferStream;
		bufferStream << buffer;
		Parse(bufferStream);
	}




	void ParseMaster::Parse(std::istream& stream)
	{
		Json::Value root;
		stream >> root;

		DelegateTask(root);
	}




	void ParseMaster::ParseFromFile(const std::string& fileName)
	{
		std::ifstream fin(fileName);
		if (fin.bad())
		{
			throw std::exception("Unable to open file.");
		}

		mFileToParse = fileName;
		Parse(fin);

		fin.close();
	}




	void ParseMaster::DelegateTask(Json::Value& root)
	{
		std::vector<std::string> rootKeys = root.getMemberNames();
		for (auto& rootKey : rootKeys)
		{
			bool memberIsObject = root[rootKey].isObject();
			
			if (memberIsObject)
			{
				for (auto& helper : mParseHelpers)
				{
					if (helper->StartHandler(rootKey, root[rootKey], mSharedData))
					{
						DelegateTask(root[rootKey]);
						break;
					}
				}
			}

			if (!memberIsObject)
			{
				for (auto& helper : mParseHelpers)
				{
					if (helper->ValueHandler(rootKey, root[rootKey], mSharedData))
					{
						break;
					}
				}
			}

			if (memberIsObject)
			{
				for (auto& helper : mParseHelpers)
				{
					if (helper->EndHandler(rootKey, root[rootKey], mSharedData))
					{
						break;
					}
				}
			}
		}
	}




	std::string& ParseMaster::GetFileName()
	{
		return mFileToParse;
	}




	ParseMaster::SharedData& ParseMaster::GetSharedData() const
	{
		return mSharedData;
	}




	void ParseMaster::SetSharedData(SharedData& sharedData)
	{
		mSharedData = sharedData;
	}




	bool ParseMaster::IsClone() const
	{
		return mIsClone;
	}

}