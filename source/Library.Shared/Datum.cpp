#include "pch.h"
#include "Scope.h"
#include "Datum.h"


namespace FieaGameEngine
{
	const size_t Datum::TypeToSizeMapping[static_cast<std::uint32_t>(EDatumType::ENumberOfSupportedDatatypes)]
	{
		0,
		sizeof(std::int32_t),
		sizeof(std::float_t),
		sizeof(glm::vec4),
		sizeof(glm::mat4x4),
		sizeof(Scope*),
		sizeof(std::string),
		sizeof(RTTI*),
	};




	Datum::Datum() : mSize(0), mCapacity(0), mDatumType(EDatumType::EUnknown), mIsInternalStorage(true)
	{

	}

	Datum::Datum(const Datum& other) : mSize(0), mCapacity(0), mDatumType(other.mDatumType), mIsInternalStorage(other.mIsInternalStorage)
	{
		if (mIsInternalStorage)
		{
			Reserve(other.mCapacity);

			if (mDatumType == EDatumType::EString)
			{
				for (std::uint32_t i = 0; i < other.mSize; ++i)
				{
					new (mData.s + i) std::string(other.mData.s[i]);
				}
			}
			else
			{
				memcpy_s(mData.vp, (TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)] * other.mSize), other.mData.vp, (TypeToSizeMapping[static_cast<std::uint32_t>(other.mDatumType)] * other.mSize));
			}

			mSize = other.mSize;
		}
		else
		{
			mData = other.mData;
			mSize = other.mSize;
			mCapacity = other.mCapacity;
		}
	}

	Datum::Datum(Datum&& other) : mSize(other.mSize), mCapacity(other.mCapacity), mDatumType(other.mDatumType), mData(other.mData), mIsInternalStorage(other.mIsInternalStorage)
	{
		other.mSize = 0;
		other.mCapacity = 0;
		other.mDatumType = EDatumType::EUnknown;
		other.mData.vp = nullptr;
		other.mIsInternalStorage = true;
	}

	Datum::Datum(const std::int32_t& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::EInteger), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(const std::float_t& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::EFloat), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(const glm::vec4& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::EVector4), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(const glm::mat4x4& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::EMatrix4x4), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(Scope* const& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::ETable), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(const std::string& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::EString), mIsInternalStorage(true)
	{
		PushBack(other);
	}

	Datum::Datum(RTTI* const& other) : mSize(0), mCapacity(0), mDatumType(EDatumType::ERTTIPointer), mIsInternalStorage(true)
	{
		PushBack(other);
	}




	Datum& Datum::operator=(const Datum& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (this != &other)
		{
			Clear();
			mDatumType = other.mDatumType;
			if(mDatumType != EDatumType::EUnknown)
			{
				Reserve(other.mCapacity);

				if (mDatumType == EDatumType::EString)
				{
					for (std::uint32_t i = 0; i < other.mSize; ++i)
					{
						PushBack(other.mData.s[i]);
					}
				}
				else
				{
					memcpy_s(mData.vp, (TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)] * other.mSize), other.mData.vp, (TypeToSizeMapping[static_cast<std::uint32_t>(other.mDatumType)] * other.mSize));
				}
				mSize = other.mSize;
			}
		}
		return *this;
	}

	Datum& Datum::operator=(Datum&& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (this != &other)
		{
			Clear();
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mDatumType = other.mDatumType;
			mData = other.mData;
			mIsInternalStorage = other.mIsInternalStorage;

			other.mSize = 0;
			other.mCapacity = 0;
			other.mDatumType = EDatumType::EUnknown;
			other.mData.vp = nullptr;
			other.mIsInternalStorage = true;
		}

		return *this;
	}

	Datum& Datum::operator=(const std::int32_t& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::EInteger;
		}
		if (mDatumType != EDatumType::EInteger)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(const std::float_t& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::EFloat;
		}
		if (mDatumType != EDatumType::EFloat)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::EVector4;
		}
		if (mDatumType != EDatumType::EVector4)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4x4& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::EMatrix4x4;
		}
		if (mDatumType != EDatumType::EMatrix4x4)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(Scope* const& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::ETable;
		}
		if (mDatumType != EDatumType::ETable)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(const std::string& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::EString;
		}
		if (mDatumType != EDatumType::EString)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}

	Datum& Datum::operator=(RTTI* const& other)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}

		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = EDatumType::ERTTIPointer;
		}
		if (mDatumType != EDatumType::ERTTIPointer)
		{
			throw std::exception("Invalid datum type.");
		}

		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other, 0);
		}

		return *this;
	}



	
	bool Datum::operator==(const Datum& other) const
	{
		if ((mSize == other.mSize) && (mDatumType == other.mDatumType))
		{
			if (mDatumType != EDatumType::EUnknown)
			{
				if (mDatumType == EDatumType::EString)
				{
					for (std::uint32_t i = 0; i < mSize; ++i)
					{
						if (mData.s[i] != other.mData.s[i])
						{
							return false;
						}
					}
				}
				else if (mDatumType == EDatumType::ETable)
				{
					for (std::uint32_t i = 0; i < mSize; ++i)
					{
						if (!mData.t[i]->Equals(other.mData.t[i]))
						{
							return false;
						}
					}
				}
				else if (mDatumType == EDatumType::ERTTIPointer)
				{
					for (std::uint32_t i = 0; i < mSize; ++i)
					{
						if (!mData.r[i]->Equals(other.mData.r[i]))
						{
							return false;
						}
					}
				}
				else
				{
					return (std::memcmp(mData.vp, other.mData.vp, (TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)] * mSize)) == 0);
				}
			}
			return true;
		}
		return false;
	}

	bool Datum::operator==(const std::int32_t& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::EInteger) && (mData.i[0] == other));
	}

	bool Datum::operator==(const std::float_t& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::EFloat) && (mData.f[0] == other));
	}

	bool Datum::operator==(const glm::vec4& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::EVector4) && (mData.v[0] == other));
	}

	bool Datum::operator==(const glm::mat4x4& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::EMatrix4x4) && (mData.m[0] == other));
	}

	bool Datum::operator==(Scope* const& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::ETable) && (mData.t[0] != nullptr && mData.t[0]->Equals(other)));
	}

	bool Datum::operator==(const std::string& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::EString) && (mData.s[0] == other));
	}

	bool Datum::operator==(RTTI* const& other) const
	{
		return ((mSize == 1) && (mDatumType == EDatumType::ERTTIPointer) && (mData.r[0] != nullptr && mData.r[0]->Equals(other)));
	}



	bool Datum::operator!=(const Datum& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const std::int32_t& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const std::float_t& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const glm::vec4& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const glm::mat4x4& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(Scope* const& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const std::string& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(RTTI* const& other) const
	{
		return !(operator==(other));
	}




	Scope& Datum::operator[](const std::uint32_t index) const
	{
		return *(Get<Scope*>(index));
	}




	EDatumType Datum::Type() const
	{
		return mDatumType;
	}




	void Datum::SetType(const EDatumType datumType)
	{
		if ((datumType >= EDatumType::ENumberOfSupportedDatatypes) || (datumType <= EDatumType::EUnknown))
		{
			throw std::exception("Invalid data type.");
		}
		else if (mSize > 0 && mDatumType != datumType)
		{
			throw std::exception("Cannot explicitly change datum type if it is populated.");
		}

		mDatumType = datumType;
	}




	std::uint32_t Datum::Size() const
	{
		return mSize;
	}




	void Datum::Resize(const std::uint32_t size)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify external storage.");
		}
		else if (mDatumType == EDatumType::EUnknown)
		{
			throw std::exception("Invalid datum type.");
		}

		Reserve(size);

		size_t typeSize = TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)];
		if (mDatumType == EDatumType::EString)
		{
			for (std::uint32_t i = size; i < mSize; ++i)
			{
				mData.s[i].~basic_string();
			}
		}
		mData.vp = realloc(mData.vp, (typeSize * size));
		if (mDatumType == EDatumType::EString)
		{
			for (std::uint32_t i = mSize; i < size; ++i)
			{
				new (mData.s + i) std::string();
			}
		}

		mSize = size;
		mCapacity = size;

	}




	void Datum::Clear()
	{
		if (mIsInternalStorage)
		{
			if ((mDatumType != EDatumType::EUnknown) && (mCapacity != 0))
			{
				if (mDatumType == EDatumType::EString)
				{
					for (std::uint32_t i = 0; i < mSize; ++i)
					{
						mData.s[i].~basic_string();
					}
				}
				free(mData.vp);
			}
		}
		mData.vp = nullptr;
		mSize = 0;
		mCapacity = 0;
	}




	void Datum::RemoveByIndex(const std::uint32_t index)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}
		else if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		memmove_s((static_cast<char*>(mData.vp) + (index * TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)])), 
			(TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)] * (mSize - index)),
			(static_cast<char*>(mData.vp) + (index * TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)]) + TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)]),
			(TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)] * (mSize - index)));
		--mSize;
	}




	void Datum::Remove(const std::int32_t& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::EInteger))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.i + index), (sizeof(std::int32_t) * (mSize - index)), (mData.i + index + 1), (sizeof(std::int32_t) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(const std::float_t& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::EFloat))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.f + index), (sizeof(std::float_t) * (mSize - index)), (mData.f + index + 1), (sizeof(std::float_t) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(const glm::vec4& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::EVector4))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.v + index), (sizeof(glm::vec4) * (mSize - index)), (mData.v + index + 1), (sizeof(glm::vec4) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(const glm::mat4x4& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::EMatrix4x4))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.m + index), (sizeof(glm::mat4x4) * (mSize - index)), (mData.m + index + 1), (sizeof(glm::mat4x4) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(Scope* const& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::ETable))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.t + index), (sizeof(Scope*) * (mSize - index)), (mData.t + index + 1), (sizeof(Scope*) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(const std::string& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::EString))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				mData.s[index].~basic_string();
				memmove_s((mData.s + index), (sizeof(std::string) * (mSize - index)), (mData.s + index + 1), (sizeof(std::string) * (mSize - index)));
				--mSize;
			}
		}
	}

	void Datum::Remove(RTTI* const& data)
	{
		if (RemoveMethodExceptionHandler(EDatumType::ERTTIPointer))
		{
			std::uint32_t index = Find(data);
			if (index < mSize)
			{
				memmove_s((mData.r + index), (sizeof(RTTI*) * (mSize - index)), (mData.r + index + 1), (sizeof(RTTI*) * (mSize - index)));
				--mSize;
			}
		}
	}

	bool Datum::RemoveMethodExceptionHandler(const EDatumType datumType) const
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}
		else if (mDatumType != datumType)
		{
			throw std::exception("Datum type mismatch.");
		}

		return true;
	}




	std::uint32_t Datum::Find(const std::int32_t& data)
	{
		if (FindMethodExceptionHandler(EDatumType::EInteger))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.i[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(const std::float_t& data)
	{
		if (FindMethodExceptionHandler(EDatumType::EFloat))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.f[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(const glm::vec4& data)
	{
		if (FindMethodExceptionHandler(EDatumType::EVector4))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.v[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(const glm::mat4x4& data)
	{
		if (FindMethodExceptionHandler(EDatumType::EMatrix4x4))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.m[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(Scope* const& data)
	{
		if (FindMethodExceptionHandler(EDatumType::ETable))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.t[i]->Equals(data))
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(const std::string& data)
	{
		if (FindMethodExceptionHandler(EDatumType::EString))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.s[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	std::uint32_t Datum::Find(RTTI* const& data)
	{
		if (FindMethodExceptionHandler(EDatumType::ERTTIPointer))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.r[i]->Equals(data))
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}




	const std::uint32_t Datum::Find(const std::int32_t& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::EInteger))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.i[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	const std::uint32_t Datum::Find(const std::float_t& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::EFloat))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.f[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	const std::uint32_t Datum::Find(const glm::vec4& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::EVector4))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.v[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	const std::uint32_t Datum::Find(const glm::mat4x4& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::EMatrix4x4))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.m[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	const std::uint32_t Datum::Find(Scope* const& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::ETable))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.t[i] == data)
				{
					break;
				}
			}

			return i;
		}
		
		return mSize;
	}

	const std::uint32_t Datum::Find(const std::string& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::EString))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.s[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	const std::uint32_t Datum::Find(RTTI* const& data) const
	{
		if (FindMethodExceptionHandler(EDatumType::ERTTIPointer))
		{
			std::uint32_t i;
			for (i = 0; i < mSize; ++i)
			{
				if (mData.r[i] == data)
				{
					break;
				}
			}

			return i;
		}

		return mSize;
	}

	bool Datum::FindMethodExceptionHandler(const EDatumType datumType) const
	{
		if (mDatumType != datumType)
		{
			throw std::exception("Datum type mismatch.");
		}

		return true;
	}

	


	void Datum::SetStorage(std::int32_t* data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::EInteger, size))
		{
			mData.i = data;
			mSize = size;
			mCapacity = size;
		}
	}

	void Datum::SetStorage(std::float_t* data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::EFloat, size))
		{
			mData.f = data;
			mSize = size;
			mCapacity = size;
		}
	}

	void Datum::SetStorage(glm::vec4* data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::EVector4, size))
		{
			mData.v = data;
			mSize = size;
			mCapacity = size;
		}
	}

	void Datum::SetStorage(glm::mat4x4* data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::EMatrix4x4, size))
		{
			mData.m = data;
			mSize = size;
			mCapacity = size;
		}
	}

	void Datum::SetStorage(std::string* data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::EString, size))
		{
			mData.s = data;
			mSize = size;
			mCapacity = size;
		}
	}

	void Datum::SetStorage(RTTI** data, const std::uint32_t size)
	{
		if (SetStorageMethodExceptionHandler(EDatumType::ERTTIPointer, size))
		{
			mData.r = data;
			mSize = size;
			mCapacity = size;
		}
	}

	bool Datum::SetStorageMethodExceptionHandler(const EDatumType datumType, const std::uint32_t size)
	{
		if (mDatumType == EDatumType::EUnknown)
		{
			mIsInternalStorage = false;
			mDatumType = datumType;
		}
		if (mDatumType != datumType)
		{
			throw std::exception("Datum type mismatch");
		}
		if (mIsInternalStorage)
		{
			throw std::exception("Cannot convert from internal storage to external storage.");
		}
		if (size == 0)
		{
			throw std::exception("External storage datum cannot point to empty array.");
		}

		return true;
	}




	void Datum::Reserve(const std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			if (!mIsInternalStorage)
			{
				throw std::exception("Cannot modify external storage.");
			}
			if (mDatumType == EDatumType::EUnknown)
			{
				throw std::exception("Invalid datum type.");
			}

			size_t size = TypeToSizeMapping[static_cast<std::uint32_t>(mDatumType)];

			if (mCapacity == 0)
			{
				mData.vp = malloc(size * capacity);
			}
			else
			{
				mData.vp = realloc(mData.vp, (size * capacity));
			}
			
			mCapacity = capacity;
		}
	}




	void Datum::Set(const std::int32_t& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::EInteger, index))
		{
			mData.i[index] = data;
		}
	}

	void Datum::Set(const std::float_t& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::EFloat, index))
		{
			mData.f[index] = data;
		}
	}

	void Datum::Set(const glm::vec4& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::EVector4, index))
		{
			mData.v[index] = data;
		}
	}

	void Datum::Set(const glm::mat4x4& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::EMatrix4x4, index))
		{
			mData.m[index] = data;
		}
	}

	void Datum::Set(Scope* const& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::ETable, index))
		{
			mData.t[index] = data;
		}
	}

	void Datum::Set(const std::string& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::EString, index))
		{
			mData.s[index] = data;
		}
	}

	void Datum::Set(RTTI* const& data, const std::uint32_t index)
	{
		if (SetMethodExceptionHandler(EDatumType::ERTTIPointer, index))
		{
			mData.r[index] = data;
		}
	}

	bool Datum::SetMethodExceptionHandler(const EDatumType datumType, const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}
		if (mDatumType != datumType)
		{
			throw std::exception("Invalid datum type.");
		}

		return true;
	}
	


	void Datum::PushBack(const std::int32_t& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::EInteger))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.i[mSize] = data;
			++mSize;
		}
	}

	void Datum::PushBack(const std::float_t& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::EFloat))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.f[mSize] = data;
			++mSize;
		}
	}

	void Datum::PushBack(const glm::vec4& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::EVector4))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.v[mSize] = data;
			++mSize;
		}
	}

	void Datum::PushBack(const glm::mat4x4& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::EMatrix4x4))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.m[mSize] = data;
			++mSize;
		}
	}

	void Datum::PushBack(Scope* const& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::ETable))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.t[mSize] = data;
			++mSize;
		}
	}

	void Datum::PushBack(const std::string& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::EString))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			new (mData.s + mSize) std::string(data);
			++mSize;
		}
	}

	void Datum::PushBack(RTTI* const& data)
	{
		if (PushBackMethodExceptionHandler(EDatumType::ERTTIPointer))
		{
			if (mSize >= mCapacity)
			{
				Reserve(mCapacity + 5);
			}

			mData.r[mSize] = data;
			++mSize;
		}
	}

	bool Datum::PushBackMethodExceptionHandler(const EDatumType datumType)
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}
		if (mDatumType == EDatumType::EUnknown)
		{
			mDatumType = datumType;
		}
		if (mDatumType != datumType)
		{
			throw std::exception("Invalid datum type.");
		}

		return true;
	}




	void Datum::GetMethodExceptionHandler(const EDatumType datumType, const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}
		if (mDatumType != datumType)
		{
			throw std::exception("Invalid datum type.");
		}
	}




	void Datum::PopBackMethodExceptionHandler(const EDatumType datumType) const
	{
		if (!mIsInternalStorage)
		{
			throw std::exception("Cannot modify data in external storage.");
		}
		if (mDatumType != datumType)
		{
			throw std::exception("Invalid datum type.");
		}
		if (mSize == 0)
		{
			throw std::exception("No items left to pop.");
		}
	}


	
	
	void Datum::SetFromString(const std::string data, const std::uint32_t index)
	{
		if (mDatumType == EDatumType::EUnknown)
		{
			throw std::exception("Invalid datum type.");
		}
		else if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		std::stringstream ss(data);
		switch (mDatumType)
		{
		case EDatumType::EInteger:
			{
				ss >> mData.i[index];
				break;
			}
		case EDatumType::EFloat:
			{
				ss >> mData.f[index];
				break;
			}
		case EDatumType::EVector4:
			{
				sscanf_s(data.c_str(), "vec4(%f, %f, %f, %f)", &mData.v[index][0], &mData.v[index][1], &mData.v[index][2], &mData.v[index][3]);
				break;
			}
		case EDatumType::EMatrix4x4:
			{
				sscanf_s(data.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
					&mData.m[index][0][0], &mData.m[index][1][0], &mData.m[index][2][0], &mData.m[index][3][0],
					&mData.m[index][0][1], &mData.m[index][1][1], &mData.m[index][2][1], &mData.m[index][3][1],
					&mData.m[index][0][2], &mData.m[index][1][2], &mData.m[index][2][2], &mData.m[index][3][2],
					&mData.m[index][0][3], &mData.m[index][1][3], &mData.m[index][2][3], &mData.m[index][3][3]);
				break;
			}
		case EDatumType::EString:
			{
				mData.s[index] = ss.str();
				break;
			}
		default:
			{
				throw std::exception("Cannot convert data to string.");
				break;
			}
		}
	}




	std::string Datum::ToString(const std::uint32_t index)
	{
		if (mDatumType == EDatumType::EUnknown)
		{
			throw std::exception("Invalid datum type.");
		}
		else if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		std::string value;
		std::stringstream ss;
		switch (mDatumType)
		{
		case EDatumType::EInteger:
			{
				value = std::to_string(Get<std::int32_t>(index));
				break;
			}
		case EDatumType::EFloat:
			{
				value = std::to_string(Get<std::float_t>(index));
				break;
			}
		case EDatumType::EVector4:
			{
				value = glm::to_string(Get<glm::vec4>(index));
				break;
			}
		case EDatumType::EMatrix4x4:
			{
				value = glm::to_string(Get<glm::mat4x4>(index));
				break;
			}
		case EDatumType::ETable:
			{
				if (mData.t[index] != nullptr)
				{
					value = Get<Scope*>(index)->ToString();
				}
				break;
			}
		case EDatumType::EString:
			{
				value = Get<std::string>(index);
				break;
			}
		case EDatumType::ERTTIPointer:
			{
				if (mData.r[index] != nullptr)
				{
					value = Get<RTTI*>(index)->ToString();
				}
				break;
			}
		default:
			{
				throw std::exception("Cannot convert data to string.");
				break;
			}
		}

		return value;
	}




	bool Datum::IsExternalStorage() const
	{
		return !mIsInternalStorage;
	}




	Datum::~Datum()
	{
		Clear();
	}
}