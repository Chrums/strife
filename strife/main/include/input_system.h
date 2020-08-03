#pragma once

#include <SDL2/SDL.h>
#include "system.h"
#include "input/input_manager.h"

namespace strife {
    namespace main {
        
        class InputSystem : public core::ISystem {
            
        public:

            common::InputManager inputManager;
            
            InputSystem() = default;
            ~InputSystem() = default;

            virtual void subscribe(common::Dispatcher& dispatcher);
            virtual void unsubscribe(common::Dispatcher& dispatcher);

        private:

            void process(const SDL_Event& event);

        };
        
    }
}