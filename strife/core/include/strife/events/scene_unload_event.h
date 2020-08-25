#pragma once

#include "strife/core/scene.h"
#include "strife/functional/message.h"

namespace strife {
    namespace events {
            
        class SceneUnloadEvent : public functional::Message {
            
        public:
        
            core::Scene& scene() const;
            
            SceneUnloadEvent(core::Scene& scene);
            ~SceneUnloadEvent() = default;

        private:

            core::Scene& scene_;
            
        };

    }
}