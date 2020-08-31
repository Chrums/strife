#include "strife/input/mouse_processor.h"

using namespace std;
using namespace strife::input;

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
            processWheel(event);
            break;
        }

    }
}

void MouseProcessor::processMotion(const SDL_Event& event) {
    position_ = pair(event.motion.x, event.motion.y);
}

void MouseProcessor::processButton(const SDL_Event& event) {
    int index = event.button.button;
    MouseButtonProcessor& mouseButtonProcessor = findMouseButtonProcessor(index);
    mouseButtonProcessor.process(event);
}

void MouseProcessor::processWheel(const SDL_Event& event) {
    
}