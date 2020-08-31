#pragma once

#include <SDL2/SDL.h>
#include "strife/core/system.h"
#include "strife/events/input_event.h"
#include "strife/input/input_manager.h"

namespace strife {
    namespace main {
        
        class InputSystem : public core::System<InputSystem> {
            
        public:

            input::InputManager inputManager;
            
            InputSystem();
            ~InputSystem() = default;

        private:

            void process(const events::InputEvent& event);

        };
        
    }
}