#pragma once

#include <SDL2/SDL.h>
#include "strife/core/system.h"
#include "strife/input/input_manager.h"

namespace strife {
    namespace main {
        
        class InputSystem : public core::ISystem {
            
        public:

            input::InputManager inputManager;
            
            InputSystem() = default;
            ~InputSystem() = default;

            virtual void subscribe(functional::Dispatcher& dispatcher);
            virtual void unsubscribe(functional::Dispatcher& dispatcher);

        private:

            void process(const core::InputEvent& event);

        };
        
    }
}