#include "pch.h"
#include "ScopeParseHelper.h"
#include "ScopeSharedData.h"
#include "ParseMaster.h"

#include "World.h"
#include "ActionList.h"


namespace FieaGameEngine
{

	ScopeParseHelper& ScopeParseHelper::Clone() const
	{
		ScopeParseHelper* newParseHelper = new ScopeParseHelper();
		newParseHelper->mIsClone = true;
		return *newParseHelper;
	}



	
	bool ScopeParseHelper::StartHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData)
	{
		ScopeSharedData* scopeSharedData = sharedData.As<ScopeSharedData>();
		if (scopeSharedData == nullptr)
		{
			return false;
		}

		mElement.key = key;
		std::vector<std::string> rootKeys = root.getMemberNames();
		if (root[rootKeys[0]].isObject())
		{
			Vector<std::string> tokens;
			std::stringstream tokenStream(key);
			std::string token;
			
			while (std::getline(tokenStream, token, '_'))
			{
				tokens.PushBack(token);
			}

			if (tokens[0] == "Sector")
			{
				scopeSharedData->mData = &scopeSharedData->mData->As<World>()->CreateSector(tokens[1]);
			}
			else if (tokens[0] == "Entity")
			{
				scopeSharedData->mData = &scopeSharedData->mData->As<Sector>()->CreateEntity(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "Action")
			{
				if (mKeyStack.Back().find("Entity") != std::string::npos)
				{
					scopeSharedData->mData = &scopeSharedData->mData->As<Entity>()->CreateAction(tokens[1], tokens[2]);
				}
				else if (mKeyStack.Back().find("Action") != std::string::npos || mKeyStack.Back().find("Reaction") != std::string::npos)
				{
					scopeSharedData->mData = &scopeSharedData->mData->As<ActionList>()->CreateAction(tokens[1], tokens[2]);
					if (mKeyStack.Back().find("ActionListIf") != std::string::npos)
					{
						scopeSharedData->mData->GetParent()->Adopt(*scopeSharedData->mData, tokens[3]);
					}
				}
			}
			else if (tokens[0] == "Reaction")
			{
				scopeSharedData->mData = &scopeSharedData->mData->As<World>()->CreateReaction(tokens[1], tokens[2]);
			}
			else
			{
				scopeSharedData->mData = &(scopeSharedData->mData->AppendScope(key));
			}

			mKeyStack.PushBack(key);
		}

		return true;
	}




	bool ScopeParseHelper::ValueHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData)
	{
		ScopeSharedData* scopeSharedData = sharedData.As<ScopeSharedData>();
		if (scopeSharedData == nullptr)
		{
			return false;
		}

		if (key == "Type")
		{
			mElement.type = root.asString();
		}
		else if (key == "Value")
		{
			mElement.root = root;
		}

		return true;
	}




	bool ScopeParseHelper::EndHandler(std::string& key, Json::Value& root, ParseMaster::SharedData& sharedData)
	{
		UNREFERENCED_PARAMETER(root);
		ScopeSharedData* scopeSharedData = sharedData.As<ScopeSharedData>();
		if (scopeSharedData == nullptr)
		{
			return false;
		}

		if ((!mKeyStack.IsEmpty()) && (mKeyStack.Back() == key))
		{
			mKeyStack.PopBack();
			scopeSharedData->mData = scopeSharedData->mData->GetParent();
		}
		else
		{
			Datum& datum = scopeSharedData->mData->Append(key);

			if (mElement.type == "Integer")
			{
				datum.SetType(EDatumType::EInteger);
			}
			else if (mElement.type == "Float")
			{
				datum.SetType(EDatumType::EFloat);
			}
			else if (mElement.type == "Vector4")
			{
				datum.SetType(EDatumType::EVector4);
			}
			else if (mElement.type == "Matrix4x4")
			{
				datum.SetType(EDatumType::EMatrix4x4);
			}
			else if (mElement.type == "String")
			{
				datum.SetType(EDatumType::EString);
			}

			if (mElement.root.isArray())
			{
				std::uint32_t newSize = mElement.root.size();
				
				if (!datum.IsExternalStorage())
				{
					datum.Resize(datum.Size() + newSize);
				}
				
				for (std::uint32_t i = 0; i < datum.Size(); ++i)
				{
					if (datum.Type() == EDatumType::EInteger)
					{
						datum.Set(mElement.root[i].asInt(), i);
					}
					else if (datum.Type() == EDatumType::EFloat)
					{
						datum.Set(mElement.root[i].asFloat(), i);
					}
					else
					{
						datum.SetFromString(mElement.root[i].asString(), i);
					}
				}
			}
			else
			{
				if (!datum.IsExternalStorage())
				{
					datum.Resize(datum.Size() + 1);
				}
				
				datum.SetFromString(mElement.root.asString(), (datum.Size() - 1));
			}
		}

		return true;
	}

}