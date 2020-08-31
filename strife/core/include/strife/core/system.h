#pragma once

#include <functional>
#include <list>
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

            void configure(functional::Dispatcher& dispatcher);
            virtual void initialize() = 0;
            virtual void dispose() = 0;

        protected:

            const functional::Dispatcher& dispatcher() const;
            functional::Dispatcher& dispatcher();

        private:

            functional::Dispatcher* dispatcher_;

        };
        
        template <typename S>
        class System : ISystem {

            using ISystem::ISystem;
            
        public:

            virtual void initialize() {
                callback<events::SceneSwapEvent>(&System::onSceneSwap);
            }

            virtual void dispose() {}

            template <typename M, typename F>
            void callback(F&& callable) {
                S* const derived = static_cast<S* const>(this);
                functional::Callback<const M&> callback = std::bind(callable, derived, std::placeholders::_1);
                functional::Token<const functional::Message&> token = dispatcher().template subscribe<M>(callback);
                tokens_.push_back(token);
            }
            
        protected:

            const Scene* const scene() const {
                return scene_;
            }

            Scene* const scene() {
                return scene_;
            }

        private:

            std::list<functional::Token<const functional::Message&>> tokens_;
            Scene* scene_;
            
            void onSceneSwap(const events::SceneSwapEvent& sceneSwapEvent) {
                scene_ = sceneSwapEvent.to();
            }
            
        };
        
    }
}