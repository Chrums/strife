#pragma once

#include "dispatch/message.h"
#include "scene.h"

namespace strife {
    namespace core {
        
        class SceneLoadEvent : public common::Message {
            
        public:
        
            Scene& scene() const {
                return scene_;
            }
            
            SceneLoadEvent(Scene& scene)
                : common::Message()
                , scene_(scene) {}

        private:

            Scene& scene_;
            
        };
        
        class SceneUnloadEvent : public common::Message {
            
        public:
        
            Scene& scene() const {
                return scene_;
            }
            
            SceneUnloadEvent(Scene& scene)
                : common::Message()
                , scene_(scene) {}

        private:

            Scene& scene_;
            
        };
        
        class SceneSwapEvent : public common::Message {
            
        public:

            Scene* const from() const {
                return from_;
            }

            Scene* const to() const {
                return to_;
            }
            
            SceneSwapEvent(Scene* const from, Scene* const to)
                : common::Message()
                , from_(from)
                , to_(to) {}

        private:
        
            Scene* const from_;
            Scene* const to_;
            
        };
        
        class UpdateEvent : public common::Message {
            
        public:
        
            UpdateEvent()
                : common::Message()  {}
            
        };
        
    }
}