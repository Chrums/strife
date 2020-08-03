#pragma once

#include <SDL2/SDL.h>
#include "input/button_input.h"

namespace strife {
    namespace common {
        
        class MouseButtonProcessor : public ButtonInput {

        public:

            MouseButtonProcessor() = default;
            ~MouseButtonProcessor() = default;

            void process(const SDL_Event& event);

        };

    }
}