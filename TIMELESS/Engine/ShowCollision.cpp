#include "ShowCollision.h"

ShowCollision::ShowCollision() : tildeKey(InputKey::Keyboard::Tilde)
{
	enabled = false;
}

void ShowCollision::Update(double)
{
	if (tildeKey.IsKeyReleased())
	{
		enabled = !enabled;
	}
}

bool ShowCollision::IsEnabled()
{
	return enabled;
}