#pragma once

#include <map>
#include "strife/common.h"
#include "strife/core/component.h"
#include "strife/core/entity.h"
#include "strife/core/storage.h"

namespace strife {

    class Scene {

#pragma region Entities

    public:

        class Entities {
        
        public:

            Entities(Scene& scene);
            ~Entities() = default;

            const Entity add();
            void remove(const Entity& entity);

        private:

            Scene& scene_;
            std::map<const Identifier, const Entity> identifierEntityMap_;

        };

#pragma endregion

#pragma region Components

    public:

        class Components {

        public:

            Components(Scene& scene);
            ~Components() = default;

            template <typename C>
            Storage<C>& add() {
                const Type& type = Type::Of<C>();
                Storage<C>* const storage = new Storage<C>();
                return *static_cast<Storage<C>* const>(typeStorageMap_.insert({type, storage}).first->second);
            }

            template <typename C>
            void remove() {
                const Type& type = Type::Of<C>();
                std::map<const Type, IStorage* const>::iterator iterator = typeStorageMap_.find(type);
                if (iterator != typeStorageMap_.end()) {
                    IStorage* const storage = iterator->second;
                    delete storage;
                    typeStorageMap_.erase(iterator);
                }
            }

            template <typename C>
            Storage<C>* const find() {
                const Type& type = Type::Of<C>();
                std::map<const Type, IStorage* const>::const_iterator iterator = typeStorageMap_.find(type);
                return iterator == typeStorageMap_.end()
                    ? nullptr
                    : static_cast<Storage<C>* const>(iterator->second);
            }

            std::map<const Type, Component* const> all(const Entity& entity);
            Component& add(const Type& type, const Entity& entity);
            void remove(const Type& type, const Entity& entity);
            Component* const find(const Type& type, const Entity& entity);

            template <typename C>
            C& add(const Entity& entity) {
                const Type& type = Type::Of<C>();
                Component& component = add(type, entity);
                return static_cast<C&>(component);
            }

            template <typename C>
            void remove(const Entity& entity) {
                const Type& type = Type::Of<C>();
                remove(type, entity);
            }

            template <typename C>
            C* const find(const Entity& entity) {
                const Type& type = Type::Of<C>();
                Component* const component = find(type, entity);

                if (component == nullptr) {
                    std::map<const Type, Component* const> components = all(entity);
                    for (auto& [type, component] : components) {
                        C* const value = dynamic_cast<C* const>(component);
                        if (value != nullptr) {
                            return value;
                        }
                    }

                    return nullptr;
                } else {
                    return static_cast<C* const>(component);
                }
            }

        private:

            Scene& scene_;
            std::map<const Type, IStorage* const> typeStorageMap_;
            std::map<const Entity, std::map<const Type, Component* const>> entityComponentsMap_;

        };

#pragma endregion

    public:

        const Entities& entities() const;
        Entities& entities();

        const Components& components() const;
        Components& components();

        Scene();
        ~Scene() = default;

    private:

        Entities entities_;
        Components components_;

    };

}