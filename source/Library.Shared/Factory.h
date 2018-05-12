#pragma once

#include "HashMap.h"

/**
*	@brief	The namespace under which the game engine is implemented.
*/
namespace FieaGameEngine
{
	/**
	*	@brief	The factory class is a templated class that
	*			serves as the asbtract factory suitable for use
	*			with any interface class that has a default
	*			constructor.
	*/
	template<typename AbstractProductType>
	class Factory
	{
	public:

		/**
		*	@brief	The default constructor has no special functionality,
		*			and hence, is defaulted.
		*/
		Factory() = default;

		/**
		*	@brief	The copy constructor is deleted.
		*/
		Factory(const Factory& other) = delete;

		/**
		*	@brief	The move constructor is deleted.
		*/
		Factory(const Factory&& other) = delete;

		/**
		*	@brief	The copy assignment operator is deleted.
		*/
		Factory& operator=(const Factory& other) = delete;

		/**
		*	@brief	The move assignment operator is deleted.
		*/
		Factory& operator=(const Factory&& other) = delete;

		/**
		*	@brief	The destructor is defaulted.
		*/
		~Factory() = default;

		/**
		*	@brief	Static method to find a concrete factory for the product
		*			you want to instantiate.
		*	@param	concreteFactoryName the name of the concrete factory
		*	@return	pointer to the concrete factory if it was found, nullptr
		*			otherwise.
		*/
		static Factory* Find(const std::string& concreteFactoryName);

		/**
		*	@brief	Static method to create a product from a concrete factory using
		*			the interface of the abstract factory.
		*	@param	concreteFactoryName name of the concrete factory
		*	@return	pointer to the product if the concrete factory for it exists, nullptr
		*			otherwise.
		*/
		static AbstractProductType* Create(const std::string& concreteFactoryName);

		/**
		*	@brief	Method to get the first concrete factory in the list of factories
		*	@return	An iterator corresponding to the beginning of the hashmap
		*/
		static typename HashMap<std::string, Factory<AbstractProductType>*>::Iterator begin();

		/**
		*	@brief	Method to get the end of the list of factories
		*	@return	An iterator corresponding to the end of the hashmap
		*/
		static typename HashMap<std::string, Factory<AbstractProductType>*>::Iterator end();
		
		/**
		*	@brief	Given a reference to the concrete factory, this method adds it to
		*			the hashmap of concrete factories
		*	@param	concreteFactory reference to the factory that is to be added
		*/
		static void Add(Factory& concreteFactory);

		/**
		*	@brief	Given a reference to the concrete factory, this method removes it
		*			from the hashmap of concrete factories
		*	@param	concreteFactory reference to the factory that is to be removed
		*/
		static void Remove(const Factory& concreteFactory);

		/**
		*	@brief	This is a non-static method that returns a concrete product associated
		*			with the concrete factory class that extends this factory class. This
		*			method must always be overriden in the derived concrete factory classes.
		*	@return	pointer to the created abstract product type, nullptr otherwise
		*/
		virtual AbstractProductType* Create() = 0;

		/**
		*	@brief	Non-static method that returns the name of the product that the concrete
		*			factory instantiates
		*	@return	String representing the name of the product class
		*/
		virtual const std::string ClassName() const = 0;

	private:

		static HashMap<std::string, Factory<AbstractProductType>*> ConcreteFactories;	/**<	Container for all the concrete factories.	*/

	};



/**
*	@brief	Macro to generate a concrete factory class given the concrete product type and the corresponding
*			abstract product type it derives from.
*	@param	ConcreteProductType the concrete product type for which the concrete factory is being generated
*	@param	AbstractProductType the abstract product type that the concrete product type inherits from
*/
#define ConcreteFactory(ConcreteProductType, AbstractProductType)										\
	class ConcreteProductType##Factory final : public FieaGameEngine::Factory<AbstractProductType>		\
	{																									\
	public:																								\
																										\
		ConcreteProductType##Factory()																	\
		{																								\
			FieaGameEngine::Factory<AbstractProductType>::Add(*this);									\
		}																								\
																										\
		ConcreteProductType* Create() override															\
		{																								\
			return new ConcreteProductType();															\
		}																								\
																										\
		const std::string ClassName() const override													\
		{																								\
			return std::string(#ConcreteProductType);													\
		}																								\
																										\
		~ConcreteProductType##Factory()																	\
		{																								\
			FieaGameEngine::Factory<AbstractProductType>::Remove(*this);								\
		}																								\
	};

}

#include "Factory.inl"