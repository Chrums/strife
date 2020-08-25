#pragma once

#include <SDL2/SDL.h>
#include "strife/core/system.h"
#include "strife/events/update_event.h"
#include "strife/math/math.h"

namespace strife {
    namespace main {
        
        class RenderSystem : public core::System {
            
        public:

            RenderSystem(const math::Vector2i& windowDimensions);
            ~RenderSystem();
            void onUpdate(const events::UpdateEvent& updateEvent);
            
        private:

            SDL_Window* window_;
            SDL_Renderer* renderer_;

        };
        
    }
}