#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include "Component.h"

class ComponentManager
{
public:
	~ComponentManager()
	{

		Clear();
	}

	void UpdateAll(double dt)
	{
		for (Component *component : components)
		{
			component->Update(dt);
		}
	}

	template <typename T>
	T *GetComponent()
	{
		for (Component *component : components)
		{
			T *ptr = dynamic_cast<T *>(component);
			if (ptr != nullptr)
			{
				return ptr;
			}
		}
		return nullptr;
	}

	void AddGomponent(Component *component)
	{
		components.push_back(component);
	}

	template <typename T>
	T *RemoveComponent()
	{

		Clear();
		// auto it = std::find_if_not(components.begin(), components.end(), [](Component* element)
		//	{
		//		return (dynamic_cast<T*>(element) != nullptr);
		//	}
		//);
		// delete* it;
		// components.erase(it);
		return nullptr;
	}
	void Clear()
	{
		for (Component *component : components)
		{
			delete component;
		}
		components.clear();
	}

private:
	std::vector<Component *> components;
};