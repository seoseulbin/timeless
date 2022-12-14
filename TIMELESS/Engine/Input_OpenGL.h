#pragma once

#include "Input.h"
#include "Engine.h"			// GetLogger, GetInput


InputKey::Keyboard OpenGLkeyToEngine(SDL_Keysym key);
void KeyPressed(SDL_Keysym key);
void KeyReleased(SDL_Keysym key);