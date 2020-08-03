#pragma once

#include <SDL2/SDL.h>
#include "input/button_input.h"

namespace strife {
    namespace common {
        
        class KeyButtonProcessor : public ButtonInput {

        public:

            KeyButtonProcessor() = default;
            ~KeyButtonProcessor() = default;
            
            void process(const SDL_Event& event);

        };

    }
}