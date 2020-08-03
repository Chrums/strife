#include "input/mouse_processor.h"

using namespace strife::common;
using namespace strife::math;

void MouseProcessor::process(const SDL_Event& event) {
    switch (event.type) {

        case SDL_MOUSEMOTION: {
            processMotion(event);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            processButton(event);
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            processButton(event);
            break;
        }

        case SDL_MOUSEWHEEL: {
            
            break;
        }

    }
}

void MouseProcessor::processMotion(const SDL_Event& event) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    position_.x = x;
    position_.y = y;
}

void MouseProcessor::processButton(const SDL_Event& event) {
    
}

void MouseProcessor::processWheel(const SDL_Event& event) {
    
}