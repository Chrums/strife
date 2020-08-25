#pragma once

#include <functional>
#include <set>
#include "strife/core/scene.h"
#include "strife/events/scene_swap_event.h"
#include "strife/events/update_event.h"
#include "strife/functional/dispatcher.h"

namespace strife {
    namespace core {
        
        class ISystem {
            
        public:
        
            ISystem() = default;
            virtual ~ISystem() = default;
            
            virtual void subscribe(functional::Dispatcher& dispatcher) = 0;
            virtual void unsubscribe(functional::Dispatcher& dispatcher) = 0;
            
        };
        
        class System : public ISystem {
            
        public:
        
            System();
            ~System() = default;
            
            virtual void subscribe(functional::Dispatcher& dispatcher);
            virtual void unsubscribe(functional::Dispatcher& dispatcher);
            
        protected:

            Scene* const scene() const;
        
            virtual void onUpdate(const events::UpdateEvent& updateEvent) = 0;
            
        private:
            
            Scene* scene_;
            
            void onSceneSwap(const events::SceneSwapEvent& sceneSwapEvent);
            
        };
        
    }
}