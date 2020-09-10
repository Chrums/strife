#pragma once

#include <map>
#include "strife/core/component.h"
#include "strife/core/entity.h"

namespace strife {

    class IStorage {

    public:

        IStorage() = default;
        virtual ~IStorage() = default;

        virtual IStorage* const copy() const = 0;
        
        virtual Component& add(const Entity& entity) = 0;
        virtual void remove(const Entity& entity) = 0;
        virtual Component* const find(const Entity& entity) = 0;

    };

    template <typename C>
    class Storage : public IStorage {

        using IStorage::IStorage;

    public:

        IStorage* const copy() const {
            return new Storage();
        }

        Component& add(const Entity& entity) {
            return entityComponentMap_.emplace(entity, entity).first->second;
        }

        void remove(const Entity& entity) {
            entityComponentMap_.erase(entity);
        }
        
        Component* const find(const Entity& entity) {
            typename std::map<const Entity, C>::iterator iterator = entityComponentMap_.find(entity);
            return iterator == entityComponentMap_.end()
                ? nullptr
                : &iterator->second;
        }

    private:

        std::map<const Entity, C> entityComponentMap_;

    };

}