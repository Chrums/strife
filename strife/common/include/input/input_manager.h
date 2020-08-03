#pragma once

#include <map>
#include <SDL2/SDL.h>
#include "input/button_input.h"
#include "input/key_button_processor.h"
#include "input/mouse_input.h"
#include "input/mouse_processor.h"

namespace strife {
    namespace common {

        class InputManager {
        
        public:

            InputManager() = default;
            ~InputManager() = default;

            void process(const SDL_Event& event);

            const MouseInput& mouse();
            const ButtonInput& key(const SDL_Keycode keyCode);

        private:

            MouseProcessor mouseProcessor_;
            std::map<SDL_Keycode, KeyButtonProcessor> keyButtonProcessors_;
            
            void processMouse(const SDL_Event& event);
            void processKey(const SDL_Event& event);

            KeyButtonProcessor& findKey(const SDL_Keycode keyCode);

        };

    }
}