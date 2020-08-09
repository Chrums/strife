#pragma once

#include <map>
#include <set>
#include <string>
#include <typeindex>
#include <cxxabi.h>
#include "unique.h"
#include "strife/serialization/data.h"
#include "strife/reflection/type.h"
#include "storage.h"

namespace strife {
    namespace core {

        using ContextType = std::map<const common::Identifier, const Entity>;
        
        class Scene : public common::Unique {

        public:
        
            class Entities {
                
            public:
            
                Entities(Scene& scene);
                ~Entities() = default;
                
                const Entity add();
                void remove(const Entity entity);

                std::set<Entity>::const_iterator begin() const;
                std::set<Entity>::const_iterator end() const;
                
            private:
            
                Scene& scene_;
                
                std::set<Entity> entities_;
                
            };
            
            class Components {
                
            public:
            
                Components(Scene& scene);
                ~Components();

                IStorage& at(const reflection::Type& type) const;
                IStorage* const find(const reflection::Type& type) const;
                
                Component& add(const reflection::Type& type, const Entity& entity);
                void remove(const Entity& entity);
                void remove(const reflection::Type& type, const Entity& entity);
                Component& at(const reflection::Type& type, const Entity& entity) const;
                Component* const find(const reflection::Type& type, const Entity& entity) const;

                std::map<const reflection::Type, IStorage* const>::const_iterator begin() const;
                std::map<const reflection::Type, IStorage* const>::const_iterator end() const;
                
                template <class C>
                Storage<C>& add() {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    Storage<C>* const storage = new Storage<C>();
                    storages_.insert({type, storage});
                    return *storage;
                }
                
                template <class C>
                void remove() {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    storages_.erase(type);
                }
                
                template <class C>
                Storage<C>& at() const {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    IStorage& storage = at(type);
                    return static_cast<Storage<C>&>(storage);
                }

                template <class C>
                Storage<C>* const find() const {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    IStorage* const storage = find(type);
                    return static_cast<Storage<C>* const>(storage);
                }
                
                template <class C>
                C& add(const Entity entity) {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    Component& component = add(type, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                void remove(const Entity entity) {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    remove(type, entity);
                }
                
                template <class C>
                C& at(const Entity entity) const {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    Component& component = at(type, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                C* const find(const Entity entity) const {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    Component* const component = find(type, entity);
                    return static_cast<C* const>(component);
                }
                
            private:
            
                Scene& scene_;

                std::map<const reflection::Type, IStorage* const> storages_;
            
            };

        public:
            
            Entities& entities();
            Components& components();
            
            Scene();
            ~Scene() = default;

            const serialization::Data serialize() const;
            void deserialize(const serialization::Data& data);

        private:

            Entities entities_;
            Components components_;
            
        };
        
    }
}