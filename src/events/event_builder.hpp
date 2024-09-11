#ifndef __EVENT_BUILDER__
#define __EVENT_BUILDER__

#include <SDL2/SDL.h>

#include "event.hpp"

Event* fromSdlEvent(const SDL_Event* event);

#endif
