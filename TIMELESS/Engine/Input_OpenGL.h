#pragma once

#include "Input.h"
#include "Engine.h" // GetLogger, GetInput

InputKey::Keyboard OpenGLkeyToEngine(SDL_Keysym key);

InputMouse::Mouse OpenGLButtonToEngine(Uint8 button);
void KeyPressed(SDL_Keysym key);
void KeyReleased(SDL_Keysym key);

void MousePressed(Uint8 button);
void MouseReleased(Uint8 button);
