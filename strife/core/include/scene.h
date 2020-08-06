#pragma once

#include <map>
#include <set>
#include <string>
#include <typeindex>
#include <cxxabi.h>
#include "storage.h"
#include "unique.h"

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
                
                template <class C>
                Storage<C>& add() {
                    std::type_index type(typeid(C));
                    Storage<C>* const storage = new Storage<C>();
                    
                    // TODO: Extract this to a reflection library?
                    int status;
                    std::string typeName = std::string(abi::__cxa_demangle(type.name(), 0, 0, &status));
                    types_.insert({typeName, type});

                    components_.insert({type, storage});
                    return *storage;
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
                Storage<C>& at() const {
                    std::type_index type(typeid(C));
                    IStorage& storage = *components_.at(type);
                    return static_cast<Storage<C>&>(storage);
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
                C* const get(const Entity entity) const {
                    std::type_index type(typeid(C));
                    Component* const component = get(type, entity);
                    return static_cast<C* const>(component);
                }
                
                Component& add(const std::type_index type, const Entity entity);
                void remove(const Entity entity);
                void remove(const std::type_index type, const Entity entity);
                Component& at(const std::type_index type, const Entity entity) const;
                Component* const get(const std::type_index type, const Entity entity) const;

                std::map<const std::type_index, IStorage* const>::const_iterator begin() const;
                std::map<const std::type_index, IStorage* const>::const_iterator end() const;

                const common::Data serialize() const;
                void deserialize(const common::Data data);
                
            private:
            
                Scene& scene_;
                std::map<const std::string, std::type_index> types_;
                std::map<const std::type_index, IStorage* const> components_;
            
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