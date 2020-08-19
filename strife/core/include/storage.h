#pragma once

#include <map>
#include "component.h"
#include "entity.h"
#include "strife/serialization/data.h"
#include "strife/serialization/context.h"
#include "strife/serialization/contexts.h"

#include <iostream>

#define ENTITY_INDEX "__ENTITY__"
#define COMPONENT_INDEX "__COMPONENT__"

namespace strife {
    namespace core {
        
        class IStorage {

        public:
            
            IStorage() = default;
            virtual ~IStorage() = default;

            virtual IStorage* copy() const = 0;
            
            virtual Component& add(const Entity& entity) = 0;
            virtual void remove(const Entity& entity) = 0;
            virtual Component& at(const Entity& entity) = 0;
            virtual Component* const find(const Entity& entity) = 0;

            virtual const serialization::Data serialize() const;
            virtual void deserialize(const serialization::Data& data);
            
        };
        
        template <class C>
        class Storage : public IStorage {
            
        public:
        
            Storage() = default;
            ~Storage() = default;

            IStorage* copy() const {
                // TODO: Copy the components into the new Storage...
                return new Storage();
            }
            
            C& add(const Entity& entity) {
                return components_.emplace(entity, entity).first->second;
            }
            
            void remove(const Entity& entity) {
                components_.erase(entity);
            }
            
            C& at(const Entity& entity) {
                return components_.at(entity);
            }
            
            C* const find(const Entity& entity) {
                typename std::map<const Entity, C>::iterator iterator = components_.find(entity);
                return iterator != components_.end()
                    ? &iterator->second
                    : nullptr;
            }
            
            const serialization::Data serialize() const {
                serialization::Data data;

                for (auto& [entity, component] : components_) {
                    serialization::Data pairData;

                    pairData[ENTITY_INDEX] = entity;
                    pairData[COMPONENT_INDEX] = component.serialize();

                    data += pairData;
                }

                return data;
            }

            void deserialize(const serialization::Data& data) {
                for (const serialization::Data& pairData : data) {
                    const serialization::Data& entityData = pairData[ENTITY_INDEX];
                    const Entity entity = entityData.get<Entity>();

                    const serialization::Data& componentData = pairData[COMPONENT_INDEX];
                    C& component = add(entity);
                    component.deserialize(componentData);
                }
            }
            
            typename std::map<const Entity, C>::iterator begin() {
                return components_.begin();
            }
            
            typename std::map<const Entity, C>::iterator end() {
                return components_.end();
            }
            
        private:
            
            std::map<const Entity, C> components_;
        
        };
        
    }
}