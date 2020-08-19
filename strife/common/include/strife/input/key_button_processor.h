#pragma once

#include <SDL2/SDL.h>
#include "strife/input/button_input.h"

namespace strife {
    namespace input {
        
        class KeyButtonProcessor : public ButtonInput {

        public:

            KeyButtonProcessor() = default;
            ~KeyButtonProcessor() = default;
            
            void process(const SDL_Event& event);

        };

    }
}