#pragma once

#include "message.h"
#include "scene.h"
#include "timer.h"

namespace strife {
    namespace core {
        
        class SceneLoadEvent : public common::Message {
            
        public:
        
            Scene& scene;
            
            SceneLoadEvent(Scene& scene)
                : common::Message()
                , scene(scene) {}
            
        };
        
        class SceneUnloadEvent : public common::Message {
            
        public:
        
            Scene& scene;
            
            SceneUnloadEvent(Scene& scene)
                : common::Message()
                , scene(scene) {}
            
        };
        
        class SceneSwapEvent : public common::Message {
            
        public:
        
            Scene* const from;
            Scene* const to;
            
            SceneSwapEvent(Scene* const from, Scene* const to)
                : common::Message()
                , from(from)
                , to(to) {}
            
        };
        
        class UpdateEvent : public common::Message {
            
        public:
        
            UpdateEvent()
                : common::Message()  {}
            
        };
        
    }
}