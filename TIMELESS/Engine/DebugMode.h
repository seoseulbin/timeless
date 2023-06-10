#pragma once
#include"Input.h"
#include"Component.h"

class DebugModeTakeAllVision : public Component
{
public:
	DebugModeTakeAllVision();
	void Update(double) override;
	bool IsEnabled();

private:
	bool enabled;
	InputKey F1_key;
};


class DebugModePlayerCheat : public Component
{
public:
	DebugModePlayerCheat();
	void Update(double) override;
	bool IsEnabled();

private:
	bool enabled;
	InputKey F2_key;
};


class PauseGame : public Component
{
public:
	PauseGame();
	void Update(double) override;
	bool IsEnabled();

private:
	bool enabled;
	InputKey F3_key;
};