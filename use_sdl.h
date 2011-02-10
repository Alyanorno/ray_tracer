#pragma once

#include <Windows.h>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#define GET_COLOR_COMPONENT( Input, Component ) \
	((Uint8)((Input \
	 & screen->format->Component##mask) \
	>> screen->format->Component##shift) \
	<< screen->format->Component##loss)

namespace Color {
enum {  White = 0xFFFFFFFF,
	Black = 0xFF000000,
	Red = 0xFFFF0000,
	Blue = 0xFF0000FF,
	Green = 0xFF00FF00 }; }
