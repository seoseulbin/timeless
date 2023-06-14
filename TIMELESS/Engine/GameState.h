#pragma once
#include <string>
#include "ComponentManager.h"

using namespace std;

class Component;
class ParticleEmitter;

class GameState
{
public:
	virtual void Load() = 0;
	virtual void Update(double dt) = 0;
	virtual void Unload() = 0;
	virtual void Draw() = 0;
	virtual string GetName() = 0;

	template <typename T>
	T *GetGSComponent()
	{
		return components.GetComponent<T>();
	}

protected:
	void AddGSComponent(Component *component)
	{
		components.AddGomponent(component);
	}
	void UpdateGSComponent(double dt)
	{
		components.UpdateAll(dt);
	}

	template <typename T>
	void RemoveGSComponent()
	{
		components.RemoveComponent<T>();
	}

	void ClearGSComponent()
	{
		components.Clear();
	}

private:
	ComponentManager components;
};