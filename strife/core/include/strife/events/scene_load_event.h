#pragma once

#include "strife/core/scene.h"
#include "strife/functional/message.h"

namespace strife {
    namespace events {
        
        class SceneLoadEvent : public functional::Message {
            
        public:
        
            core::Scene& scene() const;
            
            SceneLoadEvent(core::Scene& scene);
            ~SceneLoadEvent() = default;

        private:

            core::Scene& scene_;
            
        };

    }
}