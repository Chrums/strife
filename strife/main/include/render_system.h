#pragma once

#include <SDL2/SDL.h>
#include "strife/core/system.h"
#include "strife/math/vector2.h"

namespace strife {
    namespace main {
        
        class RenderSystem : public core::System {
            
        public:

            RenderSystem(const math::Vector2& windowDimensions);
            ~RenderSystem();
            virtual void onUpdate(const core::UpdateEvent& updateEvent);
            
        private:

            SDL_Window* window_;
            SDL_Renderer* renderer_;

        };
        
    }
}