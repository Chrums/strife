#pragma once

#include "emscripten.h"

#include <map>
#include <string>
#include <typeindex>
#include "dispatcher.h"
#include "scene.h"
#include "system.h"
#include "timer.h"

namespace strife {
    namespace core {
        
        class Engine {
            
        public:
            
            class Scenes {
                
            public:
            
                Scenes(Engine& engine);
                ~Scenes() = default;
                
                Scene& load(const std::string path);
                void unload(const std::string path);
                void swap(const std::string path);
                
            private:
            
                Engine& engine_;
                Scene* active_;
                std::map<const std::string, Scene> scenes_;
                
            };
        
            class Systems {
                
            public:
            
                Systems(Engine& engine);
                ~Systems();
                
                template <class S>
                S& add() {
                    std::type_index type(typeid(S));
                    S* const system = new S();
                    system->subscribe(engine_.dispatcher);
                    systems_.insert({type, system});
                    return *system;
                }
                
                template <class S>
                void remove() {
                    std::type_index type(typeid(S));
                    S* const system = systems_.at(type);
                    system->unsubscribe(engine_.dispatcher);
                    systems_.erase(type);
                }
                
                template <class S>
                S& at() {
                    std::type_index type(typeid(S));
                    return systems_.at(type);
                }
                
                template <class S>
                S* get() {
                    std::type_index type(typeid(S));
                    auto iterator = systems_.find(type);
                    return iterator != systems_.end()
                        ? &iterator->second
                        : nullptr;
                }
                
            private:
            
                Engine& engine_;
                
                std::map<const std::type_index, ISystem* const> systems_;
                
            };
        
        public:
            
            static Engine& Instance();
            
            common::Dispatcher dispatcher;
            common::Timer::Value time;
            
            Scenes scenes;
            Systems systems;
            
            ~Engine() = default;
            
            void run();
            void update();
            
        private:
            
			static Engine* instance_;
			
			common::Timer timer_;
			
			Engine();
            
        };
        
    }
}