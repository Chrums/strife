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
                
            private:
            
                Scene& scene_;
                
                std::set<Entity> entities_;
                
            };
            
            class Components {
                
            public:
            
                Components(Scene& scene);
                ~Components();

                const std::type_index type(std::string typeName) const;

                IStorage& at(const std::type_index type) const;
                IStorage* const find(const std::type_index type) const;
                
                Component& add(const std::type_index type, const Entity entity);
                void remove(const Entity entity);
                void remove(const std::type_index type, const Entity entity);
                Component& at(const std::type_index type, const Entity entity) const;
                Component* const find(const std::type_index type, const Entity entity) const;

                std::map<const std::type_index, IStorage* const>::const_iterator begin() const;
                std::map<const std::type_index, IStorage* const>::const_iterator end() const;
                
                template <class C>
                Storage<C>& add() {
                    std::type_index type(typeid(C));
                    Storage<C>* const storage = new Storage<C>();
                    
                    // TODO: Extract this to a reflection library?
                    int status;
                    std::string typeName = std::string(abi::__cxa_demangle(type.name(), 0, 0, &status));
                    types_.insert({typeName, type});

                    storages_.insert({type, storage});
                    return *storage;
                }
                
                template <class C>
                void remove() {
                    std::type_index type(typeid(C));

                    // TODO: Extract this to a reflection library?
                    int status;
                    std::string typeName = std::string(abi::__cxa_demangle(type.name(), 0, 0, &status));
                    types_.erase(typeName);

                    storages_.erase(type);
                }
                
                template <class C>
                Storage<C>& at() const {
                    std::type_index type(typeid(C));
                    IStorage& storage = at(type);
                    return static_cast<Storage<C>&>(storage);
                }

                template <class C>
                Storage<C>* const find() const {
                    std::type_index type(typeid(C));
                    IStorage* const storage = find(type);
                    return static_cast<Storage<C>* const>(storage);
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
                std::map<const std::type_index, IStorage* const> storages_;
            
            };

        public:
            
            Entities entities;
            Components components;
            
            Scene();
            ~Scene() = default;

            const common::Data serialize() const;
            void deserialize(const common::Data& data);
            
        };
        
    }
}