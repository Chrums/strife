#pragma once

#include <functional>
#include <set>
#include "dispatch/dispatcher.h"
#include "events.h"
#include "scene.h"
#include "storage.h"

namespace strife {
    namespace core {
        
        class ISystem {
            
        public:
        
            ISystem() = default;
            virtual ~ISystem() = default;
            
            virtual void subscribe(common::Dispatcher& dispatcher) = 0;
            virtual void unsubscribe(common::Dispatcher& dispatcher) = 0;
            
        };
        
        class System : public ISystem {
            
        public:
        
            System();
            ~System() = default;
            
            virtual void subscribe(common::Dispatcher& dispatcher);
            virtual void unsubscribe(common::Dispatcher& dispatcher);
            
        protected:
            
            Scene* scene_;
        
            virtual void onUpdate(const UpdateEvent& updateEvent) = 0;
            
        private:
            
            void onSceneSwap(const SceneSwapEvent& sceneSwapEvent);
            
        };
        
    }
}