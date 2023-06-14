#include "DebugMode.h"

DebugModeTakeAllVision::DebugModeTakeAllVision() : F1_key(InputKey::Keyboard::F1)
{
	enabled = false;
}

void DebugModeTakeAllVision::Update(double)
{
	if (F1_key.IsKeyReleased())
	{
		enabled = !enabled;
	}
}

bool DebugModeTakeAllVision::IsEnabled()
{
	return enabled;
}

DebugModePlayerCheat::DebugModePlayerCheat() : F2_key(InputKey::Keyboard::F2)
{
	enabled = false;
}

void DebugModePlayerCheat::Update(double)
{
	if (F2_key.IsKeyReleased())
	{
		enabled = !enabled;
	}
}

bool DebugModePlayerCheat::IsEnabled()
{
	return enabled;
}

PauseGame::PauseGame() : F3_key(InputKey::Keyboard::F3)
{
	enabled = false;
}

void PauseGame::Update(double)
{
	if (F3_key.IsKeyReleased())
	{
		enabled = !enabled;
	}
}

bool PauseGame::IsEnabled()
{
	return enabled;
}