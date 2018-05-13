#include "pch.h"
#include "ScopeSharedData.h"


namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ScopeSharedData)


	ScopeSharedData::ScopeSharedData() : SharedData(), mData()
	{
	}




	ScopeSharedData::ScopeSharedData(Scope& otherScopeData) : SharedData(), mData(&otherScopeData)
	{
	}




	ScopeSharedData::ScopeSharedData(const ScopeSharedData& other) : SharedData(other), mData(other.mData)
	{
	}




	ScopeSharedData& ScopeSharedData::operator=(const ScopeSharedData& other)
	{
		if (this != &other)
		{
			mIsClone = false;
			mData = other.mData;
		}

		return *this;
	}




	ScopeSharedData::~ScopeSharedData()
	{
	}
		
		
		
		
	ScopeSharedData& ScopeSharedData::Clone() const
	{
		ScopeSharedData* newSharedData = new ScopeSharedData(*mData);
		newSharedData->mIsClone = true;
		return *newSharedData;
	}

}