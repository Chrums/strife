#include "input/mouse_button_processor.h"

using namespace strife::common;

void MouseButtonProcessor::process(const SDL_Event& event) {
    switch (event.type) {

        case SDL_MOUSEBUTTONDOWN: {
            value_ = 1.0f;
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            value_ = 0.0f;
            break;
        }

    }
}