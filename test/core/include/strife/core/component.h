#pragma once

#include "strife/common.h"

namespace strife {

    class Entity;

    class Component {

    public:

        const Entity& entity() const;
        Entity& entity();

        Component();
        Component(const Entity& entity);
        virtual ~Component();

    private:

        Entity* entity_;
        Identifier identifier_;

    };

}