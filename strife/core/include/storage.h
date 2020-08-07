#pragma once

#include <map>
#include "serialization/data.h"
#include "identifier.h"
#include "iterator.h"
#include "component.h"
#include "entity.h"

#include <iostream>

namespace strife {
    namespace core {
        
        class IStorage {

        public:
            
            IStorage() = default;
            virtual ~IStorage() = default;
            
            virtual Component& add(const Entity entity) = 0;
            virtual void remove(const Entity entity) = 0;
            virtual Component& at(const Entity entity) = 0;
            virtual Component* const find(const Entity entity) = 0;
            
        };
        
        template <class C>
        class Storage : public IStorage {

        public:

            using Iterator = typename std::map<Entity, C>::iterator;
            
        public:
        
            Storage()
                : IStorage() {}

            ~Storage() = default;
            
            C& add(const Entity entity) {
                return components_.emplace(entity, entity).first->second;
            }
            
            void remove(const Entity entity) {
                components_.erase(entity);
            }
            
            C& at(const Entity entity) {
                return components_.at(entity);
            }
            
            C* const find(const Entity entity) {
                auto iterator = components_.find(entity);
                return iterator != components_.end()
                    ? &iterator->second
                    : nullptr;
            }
            
            Iterator begin() {
                return components_.begin();
            }
            
            Iterator end() {
                return components_.end();
            }
            
        private:
            
            std::map<Entity, C> components_;
        
        };
        
    }
}