#pragma once

#include <SDL2/SDL.h>

#include "event.hpp"

Event* fromSdlEvent(const SDL_Event* event);
