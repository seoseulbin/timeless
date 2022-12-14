#pragma once
#include"Input.h"
#include"Component.h"

class ShowCollision : public Component
{
public:
	ShowCollision();
	void Update(double) override;
	bool IsEnabled();

private:
	bool enabled;
	InputKey tildeKey;
};