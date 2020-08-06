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
            virtual Component* const get(const Entity entity) = 0;
            
        };
        
        template <class C>
        class Storage : public IStorage {
            
        public:
        
            class Iterator : public common::IIterator<Iterator, std::pair<const Entity, C&>> {
                
            public:
            
                Iterator(typename std::map<Entity, C>::iterator iterator)
                    : iterator_(iterator) {}

                ~Iterator() = default;
                
                Iterator& operator++() {
                    iterator_++;
                    return *this;
                }
                
                Iterator& operator++(int) {
                    ++iterator_;
                    return *this;
                }
                
                bool operator==(const Iterator& iterator) const {
                    return iterator_ == static_cast<const Iterator&>(iterator).iterator_;
                }
                
                bool operator!=(const Iterator& iterator) const {
                    return iterator_ != static_cast<const Iterator&>(iterator).iterator_;
                }
                
                std::pair<const Entity, C&> operator*() const {
                    return {iterator_->first, iterator_->second};
                }
                
            private:
            
                typename std::map<Entity, C>::iterator iterator_;
                
            };
            
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
            
            C* const get(const Entity entity) {
                auto iterator = components_.find(entity);
                return iterator != components_.end()
                    ? &iterator->second
                    : nullptr;
            }
            
            Iterator begin() {
                auto iterator = components_.begin();
                return Iterator(iterator);
            }
            
            Iterator end() {
                auto iterator = components_.end();
                return Iterator(iterator);
            }
            
        private:
            
            std::map<Entity, C> components_;
        
        };
        
    }
}