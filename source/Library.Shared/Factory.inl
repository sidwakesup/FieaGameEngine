#include "pch.h"
#include "Factory.h"

namespace FieaGameEngine
{

	template<typename AbstractProductType>
	HashMap<std::string, Factory<AbstractProductType>*> Factory<AbstractProductType>::ConcreteFactories(20);




	template<typename AbstractProductType>
	Factory<AbstractProductType>* Factory<AbstractProductType>::Find(const std::string& concreteFactoryName)
	{
		auto it = ConcreteFactories.Find(concreteFactoryName);

		if (it == ConcreteFactories.end())
		{
			return nullptr;
		}

		return (*it).second;
	}




	template<typename AbstractProductType>
	AbstractProductType* Factory<AbstractProductType>::Create(const std::string& concreteFactoryName)
	{
		return ConcreteFactories.At(concreteFactoryName)->Create();
	}




	template<typename AbstractProductType>
	typename HashMap<std::string, Factory<AbstractProductType>*>::Iterator Factory<AbstractProductType>::begin()
	{
		return ConcreteFactories.begin();
	}




	template<typename AbstractProductType>
	typename HashMap<std::string, Factory<AbstractProductType>*>::Iterator Factory<AbstractProductType>::end()
	{
		return ConcreteFactories.end();
	}




	template<typename AbstractProductType>
	void Factory<AbstractProductType>::Add(Factory<AbstractProductType>& concreteFactory)
	{
		ConcreteFactories.Insert(std::make_pair(concreteFactory.ClassName(), &concreteFactory));
	}




	template<typename AbstractProductType>
	void Factory<AbstractProductType>::Remove(const Factory<AbstractProductType>& concreteFactory)
	{
		ConcreteFactories.Remove(concreteFactory.ClassName());
	}

}