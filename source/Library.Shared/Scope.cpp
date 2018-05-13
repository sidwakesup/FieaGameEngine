#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);


	std::string Scope::ToString() const
	{
		std::string tempString;
		for (std::uint32_t i = 0; i < mPointersToLookupTable.Size(); ++i)
		{
			tempString.append(mPointersToLookupTable[i]->second.ToString());
		}

		return tempString;
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (rhs == this)
		{
			return true;
		}

		if (rhs == nullptr)
		{
			return false;
		}

		Scope* rhsScope = rhs->As<Scope>();
		if (rhsScope == nullptr)
		{
			return false;
		}

		return (*this == *rhsScope);

	}




	Scope::Scope() : mParent(nullptr), mLookupTable(), mPointersToLookupTable()
	{
	}




	Scope::Scope(const Scope& other) : mParent(nullptr), mLookupTable(other.mLookupTable.NumberOfBuckets()), mPointersToLookupTable()
	{
		DeepCopy(other);
	}




	Scope::Scope(Scope&& other) : mParent(nullptr), mLookupTable(std::move(other.mLookupTable)), mPointersToLookupTable(std::move(other.mPointersToLookupTable))
	{
		std::string name;

		if (other.mParent != nullptr)
		{
			name = other.mParent->FindName(other);
		}

		MoveSemantics(std::move(other), name);
	}




	Scope::Scope(const std::uint32_t& capacity) : mParent(nullptr), mLookupTable(capacity), mPointersToLookupTable(capacity)
	{
	}




	Scope& Scope::operator=(const Scope& other)
	{
		if (this != &other)
		{
			Clear();

			mLookupTable = HashMap<std::string, Datum>(other.mLookupTable.NumberOfBuckets());
			mPointersToLookupTable = Vector<LookupTableEntry*>();

			DeepCopy(other);
		}

		return *this;
	}




	Scope& Scope::operator=(Scope&& other)
	{
		if (this != &other)
		{
			Clear();

			if (mParent != nullptr)
			{
				mParent->OrphanChild(*this);
			}

			std::string name;

			if (other.mParent != nullptr)
			{
				name = other.mParent->FindName(other);
			}

			mParent = nullptr;
			mLookupTable = std::move(other.mLookupTable);
			mPointersToLookupTable = std::move(other.mPointersToLookupTable);

			MoveSemantics(std::move(other), name);
		}

		return *this;
	}




	void Scope::DeepCopy(const Scope& other)
	{
		mPointersToLookupTable.Reserve(other.mPointersToLookupTable.Size());
		for (std::uint32_t i = 0; i < other.mPointersToLookupTable.Size(); ++i)
		{
			if (other.mPointersToLookupTable[i]->second.Type() == EDatumType::ETable)
			{
				for (std::uint32_t j = 0; j < other.mPointersToLookupTable[i]->second.Size(); ++j)
				{
					Scope* scope = other.mPointersToLookupTable[i]->second[j].Clone();
					Adopt(*scope, other.mPointersToLookupTable[i]->first);
				}
			}
			else
			{
				mPointersToLookupTable.PushBack(&(*mLookupTable.Insert(std::make_pair(other.mPointersToLookupTable[i]->first, other.mPointersToLookupTable[i]->second))));
			}
		}
	}




	void Scope::MoveSemantics(Scope&& other, const std::string& name)
	{
		for (std::uint32_t i = 0; i < mPointersToLookupTable.Size(); ++i)
		{
			auto& pointerToLookupTableElement = mPointersToLookupTable[i];

			if (pointerToLookupTableElement->second.Type() == EDatumType::ETable)
			{
				for (std::uint32_t j = 0; j < pointerToLookupTableElement->second.Size(); ++j)
				{
					pointerToLookupTableElement->second[j].mParent = this;
				}
			}
		}

		if (other.mParent != nullptr)
		{
			Scope* Parent = other.mParent;
			other.mParent->OrphanChild(other);
			Parent->Adopt(*this, name);
		}

		other.Clear();
	}




	Scope* Scope::Clone()
	{
		return new Scope(*this);
	}




	Datum* Scope::Find(const std::string& key) const
	{
		Datum* datumPointer = nullptr;
		if (!IsEmpty())
		{
			auto it = mLookupTable.Find(key);
			if (it != mLookupTable.end())
			{
				datumPointer = &(*it).second;
			}
		}
		return datumPointer;
	}




	Datum* Scope::Search(const std::string& key)
	{
		Datum* datumPointer = Find(key);

		if (mParent != nullptr)
		{
			if (datumPointer == nullptr)
			{
				datumPointer = mParent->Search(key);
			}
		}

		return datumPointer;
	}




	const Datum* Scope::Search(const std::string& key) const
	{
		Datum* datumPointer = Find(key);

		if (mParent != nullptr)
		{
			if (datumPointer == nullptr)
			{
				datumPointer = mParent->Search(key);
			}
		}

		return datumPointer;
	}




	Datum* Scope::Search(const std::string& key, const Scope*& scope)
	{
		Datum* datumPointer = Find(key);
		scope = nullptr;


		if (datumPointer == nullptr)
		{
			datumPointer = mParent->Search(key, scope);
		}
		else
		{
			scope = this;
		}

		return datumPointer;
	}




	const Datum* Scope::Search(const std::string& key, const Scope*& scope) const
	{
		Datum* datumPointer = Find(key);
		scope = nullptr;

		if (datumPointer == nullptr)
		{
			datumPointer = mParent->Search(key, scope);
		}
		else
		{
			scope = this;
		}

		return datumPointer;
	}

	


	Datum& Scope::Append(const std::string& key)
	{
		bool wasInserted;
		auto it = mLookupTable.Insert(std::make_pair(key, Datum()), wasInserted);

		if (wasInserted)
		{
			mPointersToLookupTable.PushBack(&(*it));
		}

		return (*it).second;
	}




	Scope& Scope::AppendScope(const std::string& key)
	{
		Datum& datum = Append(key);

		if (datum.Type() != EDatumType::EUnknown && datum.Type() != EDatumType::ETable)
		{
			throw std::exception("Given key already exists for a datum of a different type.");
		}

		Scope* scope = new Scope();
		datum.PushBack(scope);
		scope->mParent = this;
		return *scope;
	}




	void Scope::Adopt(Scope& childToAdopt, const std::string& key)
	{
		if (this == &childToAdopt)
		{
			throw std::exception("Invalid scope hierarchy modification.");
		}

		
		if (childToAdopt.mParent != nullptr)
		{
			childToAdopt.mParent->OrphanChild(childToAdopt);
		}

		Datum& datum = Append(key);

		datum.PushBack(&childToAdopt);

		childToAdopt.mParent = this;
	}




	Scope* Scope::GetParent() const
	{
		return mParent;
	}




	Datum& Scope::operator[](const std::string& key)
	{
		return Append(key);
	}




	Datum& Scope::operator[](const std::uint32_t& index) const
	{
		if (index >= mLookupTable.Size())
		{
			throw std::exception("Index out of bounds.");
		}

		return (*mPointersToLookupTable[index]).second;
	}




	bool Scope::operator==(const Scope& other) const
	{
		return (mLookupTable == other.mLookupTable);
	}




	bool Scope::operator!=(const Scope& other) const
	{
		return !(operator==(other));
	}




	bool Scope::CompareStructure(const Scope& other) const
	{
		if (mPointersToLookupTable.Size() == other.mPointersToLookupTable.Size())
		{
			auto i = mPointersToLookupTable.begin();
			auto j = other.mPointersToLookupTable.begin();
			for (; i != mPointersToLookupTable.end(); ++i, ++j)
			{
				if (*(*i) != *(*j))
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}




	std::string Scope::FindName(const Scope& scope) const
	{
		std::string name;

		for (std::uint32_t i = 0; i < mPointersToLookupTable.Size(); ++i)
		{
			Datum childDatum;
			childDatum = mPointersToLookupTable[i]->second;
			if (childDatum.Type() == EDatumType::ETable)
			{
				for (std::uint32_t j = 0; j < childDatum.Size(); ++j)
				{
					if (&childDatum[j] == &scope)
					{
						name = mPointersToLookupTable[i]->first;
						break;
					}
				}
			}
		}

		return name;
	}




	std::string Scope::FindContainedScope(const Scope& scope, Datum*& datum, std::uint32_t& index) const
	{
		std::string name;
		
		for (std::uint32_t i = 0; i < mPointersToLookupTable.Size(); ++i)
		{
			Datum& childDatum = mPointersToLookupTable[i]->second;
			if (childDatum.Type() == EDatumType::ETable)
			{
				for (std::uint32_t j = 0; j < childDatum.Size(); ++j)
				{
					if (&childDatum[j] == &scope)
					{
						name = mPointersToLookupTable[i]->first;
						datum = &childDatum;
						index = j;
						break;
					}
				}
			}
		}

		return name;

	}




	bool Scope::IsEmpty() const
	{
		return (mLookupTable.Size() == 0);
	}




	std::uint32_t Scope::Size() const
	{
		return mLookupTable.Size();
	}




	void Scope::OrphanChild(Scope& child)
	{
		if (child.mParent != this)
		{
			throw std::exception("Cannot orphan a scope that is not your child.");
		}

		std::string name;
		Datum* datum = nullptr;
		std::uint32_t index;
		name = FindContainedScope(child, datum, index);
		datum->RemoveByIndex(index);
		child.mParent = nullptr;
	}




	void Scope::Clear()
	{
		if (mParent != nullptr)
		{
			mParent->OrphanChild(*this);
		}

		for (std::uint32_t i = 0; i < mPointersToLookupTable.Size(); ++i)
		{
			Datum& datum = mPointersToLookupTable[i]->second;
			if (datum.Type() == EDatumType::ETable)
			{
				for (std::uint32_t j = 0; j < datum.Size(); ++j)
				{
					datum.Get<Scope*>(j)->mParent = nullptr;
					delete datum.Get<Scope*>(j);

				}
			}
		}
		
		mLookupTable.Clear();
		mPointersToLookupTable.Clear();
	}




	Scope::~Scope()
	{
		Clear();
	}

}