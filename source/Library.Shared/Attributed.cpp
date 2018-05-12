#include "pch.h"
#include "Attributed.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Attributed)




	HashMap<std::uint64_t, Vector<std::string>> Attributed::mPrescribedAttributes(50);




	Attributed::Attributed() : Scope::Scope()
	{
		(*this)["this"] = static_cast<RTTI*>(this);
	}




	Attributed::Attributed(const Attributed& other) : Scope::Scope(other)
	{
		(*this)["this"] = static_cast<RTTI*>(this);
	}




	Attributed::Attributed(Attributed&& other) : Scope::Scope(std::move(other))
	{
		(*this)["this"] = static_cast<RTTI*>(this);
	}




	Scope* Attributed::Clone()
	{
		return new Attributed(*this);
	}




	Attributed& Attributed::operator=(const Attributed& other)
	{
		if (this != &other)
		{
			Scope::operator=(other);
			(*this)["this"] = static_cast<RTTI*>(this);
		}

		return *this;
	}




	Attributed& Attributed::operator=(Attributed&& other)
	{
		if (this != &other)
		{
			Scope::operator=(std::move(other));
			(*this)["this"] = static_cast<RTTI*>(this);
		}

		return *this;
	}




	bool Attributed::IsAttribute(const std::string& key) const
	{
		if (Find(key) != nullptr)
		{
			return true;
		}

		return false;
	}




	bool Attributed::IsPrescribedAttribute(const std::string& key) const
	{
		auto it = mPrescribedAttributes.Find(TypeIdInstance());
		if (it != mPrescribedAttributes.end())
		{
			Vector<std::string>& foundVector = it.operator*().second;

			if (foundVector.Find(key) != foundVector.end())
			{
				return true;
			}

		}

		return false;
	}




	bool Attributed::IsAuxiliaryAttribute(const std::string& key) const
	{
		return ((IsAttribute(key)) && !(IsPrescribedAttribute(key)));
	}




	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& key)
	{
		if (IsPrescribedAttribute(key))
		{
			throw std::exception("Key corresponds to a prescribed attribute.");
		}
		return Append(key);
	}




	const Vector<std::pair<std::string, Datum>*>& Attributed::GetAttributes() const
	{
		return mPointersToLookupTable;
	}




	Vector<std::pair<std::string, Datum>*> Attributed::GetPrescribedAttributes() const
	{
		Vector<std::pair<std::string, Datum>*> prescribedAttributes = mPointersToLookupTable;

		auto& prescribedAttributeKeys = mPrescribedAttributes.Find(TypeIdInstance()).operator*().second;

		for (std::int32_t i = (prescribedAttributes.Size() - 1); i >= 0; --i)
		{
			if (prescribedAttributeKeys.Find(prescribedAttributes[i]->first) == prescribedAttributeKeys.end())
			{
				prescribedAttributes.Remove(prescribedAttributes[i]);
			}
		}

		return prescribedAttributes;

	}




	Vector<std::pair<std::string, Datum>*> Attributed::GetAuxiliaryAttributes() const
	{
		Vector<std::pair<std::string, Datum>*> auxiliaryAttributes = mPointersToLookupTable;

		auto& prescribedAttributeKeys = mPrescribedAttributes.Find(TypeIdInstance()).operator*().second;

		for (std::int32_t i = (auxiliaryAttributes.Size() - 1); i >= 0; --i)
		{
			if (prescribedAttributeKeys.Find(auxiliaryAttributes[i]->first) != prescribedAttributeKeys.end())
			{
				auxiliaryAttributes.Remove(auxiliaryAttributes[i]);
			}
		}

		return auxiliaryAttributes;
	}




	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, const std::int32_t& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, const std::float_t& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, const glm::vec4& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);
		
		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, const glm::mat4x4& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, Scope* const& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);


		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, const std::string& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddInternalPrescribedAttribute(const std::string& name, RTTI* const& defaultValue, std::uint32_t& count)
	{
		Datum& d = Append(name);

		for (std::uint32_t i = 0; i < count; ++i)
		{
			d.PushBack(defaultValue);
		}

		AddToPrescribedAttributes(name);
		
		return &d;
	}




	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, std::int32_t* externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, std::float_t* externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, glm::vec4* externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, glm::mat4x4* externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);

		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, std::string* externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);
		
		AddToPrescribedAttributes(name);

		return &d;
	}

	Datum* Attributed::AddExternalPrescribedAttribute(const std::string& name, RTTI** externalData, const std::uint32_t size)
	{
		Datum& d = Append(name);
		d.SetStorage(externalData, size);

		AddToPrescribedAttributes(name);

		return &d;
	}




	void Attributed::AddToPrescribedAttributes(const std::string& name)
	{
		auto it = mPrescribedAttributes.Find(TypeIdInstance());
		if (it == mPrescribedAttributes.end())
		{
			it = mPrescribedAttributes.Insert(std::make_pair(TypeIdInstance(), Vector<std::string>()));
		}

		if ((*it).second.Find(name) == (*it).second.end())
		{
			(*it).second.PushBack(name);
		}
	}




	void Attributed::InitializeAttributes()
	{
		//do nothing
	}




	void Attributed::UpdatePrescribedAttributes()
	{
		//do nothing
	}

}