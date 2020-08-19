#pragma once

#include <functional>
#include <set>
#include "strife/core/events.h"
#include "strife/core/scene.h"
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
            
            Scene* scene_;
        
            virtual void onUpdate(const UpdateEvent& updateEvent) = 0;
            
        private:
            
            void onSceneSwap(const SceneSwapEvent& sceneSwapEvent);
            
        };
        
    }
}