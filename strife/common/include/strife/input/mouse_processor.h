#pragma once

#include <SDL2/SDL.h>
#include "strife/input/mouse_input.h"

namespace strife {
    namespace input {
        
        class MouseProcessor : public MouseInput {

        public:
        
            void process(const SDL_Event& event);

        private:

            void processMotion(const SDL_Event& event);
            void processButton(const SDL_Event& event);
            void processWheel(const SDL_Event& event);

        };

    }
}