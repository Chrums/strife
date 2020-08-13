#pragma once

#include "emscripten.h"

#include <map>
#include <string>
#include <typeindex>
#include <SDL2/SDL.h>
#include "action.h"
#include "dispatch/dispatcher.h"
#include "time/timer.h"
#include "scene.h"
#include "system.h"
#include "storage.h"
#include "strife/reflection/type.h"

namespace strife {
    namespace core {
        
        class Engine {
        
        public:

            class Components {

            public:

                Components() = default;
                ~Components() = default;

                std::map<const reflection::Type, const IStorage* const>::iterator begin();
                std::map<const reflection::Type, const IStorage* const>::iterator end();

                template <class C>
                void add() {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    Storage<C>* const storage = new Storage<C>();
                    dummies_.insert({type, storage});
                }

                template <class C>
                void remove() {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    dummies_.erase(type);
                }

            private:

                std::map<const reflection::Type, const IStorage* const> dummies_;

            };
            
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
                
                template <class S, class ...Args>
                S& add(Args... args) {
                    std::type_index type(typeid(S));
                    S* const system = new S(args...);
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
                    ISystem* const system = systems_.at(type);
                    return static_cast<S&>(*system);
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
            common::Action<const SDL_Event&> inputEvent;
            
            Components components;
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