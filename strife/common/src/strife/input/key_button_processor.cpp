#include "strife/input/key_button_processor.h"

using namespace strife::input;

void KeyButtonProcessor::process(const SDL_Event& event) {
    switch (event.type) {

        case SDL_KEYDOWN: {
            value_ = 1.0f;
            break;
        }

        case SDL_KEYUP: {
            value_ = 0.0f;
            break;
        }

    }
}