#pragma once

#include <SDL2/SDL.h>
#include "strife/core/scene.h"
#include "strife/functional/message.h"

namespace strife {
    namespace core {
        
        class SceneLoadEvent : public functional::Message {
            
        public:
        
            Scene& scene() const {
                return scene_;
            }
            
            SceneLoadEvent(Scene& scene)
                : functional::Message()
                , scene_(scene) {}

        private:

            Scene& scene_;
            
        };
        
        class SceneUnloadEvent : public functional::Message {
            
        public:
        
            Scene& scene() const {
                return scene_;
            }
            
            SceneUnloadEvent(Scene& scene)
                : functional::Message()
                , scene_(scene) {}

        private:

            Scene& scene_;
            
        };
        
        class SceneSwapEvent : public functional::Message {
            
        public:

            Scene* const from() const {
                return from_;
            }

            Scene* const to() const {
                return to_;
            }
            
            SceneSwapEvent(Scene* const from, Scene* const to)
                : functional::Message()
                , from_(from)
                , to_(to) {}

        private:
        
            Scene* const from_;
            Scene* const to_;
            
        };

        class InputEvent : public functional::Message {

        public:

            const SDL_Event& event() const {
                return event_;
            }

            InputEvent(SDL_Event& event)
                : functional::Message()
                , event_(event) {}

        private:

            const SDL_Event& event_;

        };
        
        class UpdateEvent : public functional::Message {
            
        public:
        
            UpdateEvent()
                : functional::Message()  {}
            
        };
        
    }
}