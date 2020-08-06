#pragma once

#include <map>
#include <set>
#include <string>
#include <typeindex>
#include <cxxabi.h>
#include "unique.h"
#include "entity.h"
#include "component.h"

namespace strife {
    namespace core {
        
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

                const common::Data serialize() const;
                const common::Data deserialize(const common::Data data);
                
            private:
            
                Scene& scene_;
                
                std::set<Entity> entities_;
                
            };
            
            class Components {
                
            public:
            
                Components(Scene& scene);
                ~Components();
                
                Component& add(const std::type_index type, const Entity entity);
                void remove(const Entity entity);
                void remove(const std::type_index type, const Entity entity);
                Component& at(const std::type_index type, const Entity entity) const;
                Component* const find(const std::type_index type, const Entity entity) const;

                std::map<const std::type_index, std::map<Entity, Component>* const>::const_iterator begin() const;
                std::map<const std::type_index, std::map<Entity, Component>* const>::const_iterator end() const;

                const common::Data serialize() const;
                void deserialize(const common::Data data);
                
                template <class C>
                std::map<Entity, C>& add() {
                    std::type_index type(typeid(C));
                    std::map<Entity, C>* const components = new std::map<Entity, C>();
                    
                    // TODO: Extract this to a reflection library?
                    int status;
                    std::string typeName = std::string(abi::__cxa_demangle(type.name(), 0, 0, &status));
                    types_.insert({typeName, type});

                    components_.insert({type, components});
                    return *components;
                }
                
                template <class C>
                void remove() {
                    std::type_index type(typeid(C));

                    // TODO: Extract this to a reflection library?
                    int status;
                    std::string typeName = std::string(abi::__cxa_demangle(type.name(), 0, 0, &status));
                    types_.erase(typeName);

                    components_.erase(type);
                }
                
                template <class C>
                std::map<Entity, C>& at() const {
                    std::type_index type(typeid(C));
                    std::map<Entity, Component>* components = components_.at(type);
                    return dynamic_cast<std::map<Entity, C>&>(components);
                }
                
                template <class C>
                C& add(const Entity entity) {
                    std::type_index type(typeid(C));
                    Component& component = add(type, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                void remove(const Entity entity) {
                    std::type_index type(typeid(C));
                    remove(type, entity);
                }
                
                template <class C>
                C& at(const Entity entity) const {
                    std::type_index type(typeid(C));
                    Component& component = at(type, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                C* const find(const Entity entity) const {
                    std::type_index type(typeid(C));
                    Component* const component = find(type, entity);
                    return static_cast<C* const>(component);
                }
                
            private:
            
                Scene& scene_;
                std::map<const std::string, std::type_index> types_;
                std::map<const std::type_index, std::map<Entity, Component>* const> components_;
            
            };
            
        public:
            
            Entities entities;
            Components components;
            
            Scene();
            ~Scene() = default;

            const common::Data serialize() const;
            void deserialize(const common::Data data);
            
        };
        
    }
}