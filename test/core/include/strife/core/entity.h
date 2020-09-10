#pragma once

#include "strife/common.h"
#include "strife/core/component.h"

namespace strife {

    class Scene;

    class Entity {

#pragma region Components

    public:

        class Components {

        public:

            Components(Entity& entity);
            ~Components() = default;

            Component& add(const Type& type);
            void remove(const Type& type);
            Component* const find(const Type& type);

            template <typename C>
            C& add() {
                const Type& type = Type::Of<C>();
                Component& component = add(type);
                return static_cast<C&>(component);
            }

            template <typename C>
            void remove() {
                const Type& type = Type::Of<C>();
                remove(type);
            }

            template <typename C>
            C* const find() {
                const Type& type = Type::Of<C>();
                Component* const component = find(type);
                return static_cast<C* const>(component);
            }

        private:

            Entity& entity_;

        };

#pragma endregion

    public:

        const Scene& scene() const;
        Scene& scene();

        const Identifier& identifier() const;
        Identifier& identifier();

        const Components& components() const;
        Components& components();

        Entity();
        Entity(Scene& scene);
        ~Entity() = default;

        Entity& operator=(const Entity& entity);
        bool operator==(const Entity& entity) const;
        bool operator<(const Entity& entity) const;

    private:

        Scene* scene_;
        Identifier identifier_;
        Components components_;

    };

}