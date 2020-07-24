#pragma once

#include "system.h"

namespace strife {
    namespace main {
        
        class RenderSystem : core::System {
            
        using core::System::System;
        
        public:
            
            virtual void onUpdate(const core::UpdateEvent& updateEvent);
            
        };
        
    }
}