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

                Entities& operator=(const Entities& entities);
                
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

                Components& operator=(const Components& components);

                IStorage& at(const reflection::Type& type) const;
                
                Component& add(const reflection::Type& type, const Entity& entity);
                void remove(const Entity& entity);
                void remove(const reflection::Type& type, const Entity& entity);
                Component& at(const reflection::Type& type, const Entity& entity) const;
                Component* const find(const reflection::Type& type, const Entity& entity) const;

                std::map<const reflection::Type, IStorage* const>::const_iterator begin() const;
                std::map<const reflection::Type, IStorage* const>::const_iterator end() const;
                
                template <class C>
                Storage<C>& at() const {
                    const reflection::Type& type = reflection::Type::Of<C>();
                    IStorage& storage = at(type);
                    return static_cast<Storage<C>&>(storage);
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
            
            const Entities& entities() const;
            Entities& entities();

            const Components& components() const;
            Components& components();
            
            Scene();
            ~Scene() = default;

            Scene& operator=(const Scene& scene);

        private:

            Entities entities_;
            Components components_;
            
        };

		void to_json(serialization::Data& data, const Scene& scene);
		void from_json(const serialization::Data& data, Scene& scene);
        
    }
}