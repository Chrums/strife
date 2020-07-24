#pragma once

#include <SDL.h>
#include "system.h"

namespace strife {
    namespace main {
        
        class InputSystem : public core::System {
            
        using core::System::System;
        
        public:
            
            virtual void onUpdate(const core::UpdateEvent& updateEvent);
            
        private:

            void process(const SDL_Event& event);

        };
        
    }
}