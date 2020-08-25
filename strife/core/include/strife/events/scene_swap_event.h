#pragma once

#include "strife/core/scene.h"
#include "strife/functional/message.h"

namespace strife {
    namespace events {
        
        class SceneSwapEvent : public functional::Message {
            
        public:

            core::Scene* const from() const;
            core::Scene* const to() const;
            
            SceneSwapEvent(core::Scene* const from, core::Scene* const to);
            ~SceneSwapEvent() = default;

        private:
        
            core::Scene* const from_;
            core::Scene* const to_;
            
        };

    }
}