#pragma once

#include "unique.h"
#include "strife/serialization/data.h"
#include "entity.h"

namespace strife {
    namespace core {
        
        class Component : public common::Unique {
            
        public:
        
            const Entity& entity();
            
            Component(const Entity& entity);
			virtual ~Component() = default;
            
            virtual const serialization::Data serialize() const;
            virtual void deserialize(const serialization::Data& data);

        private:

            const Entity entity_;

        };
        
    }
}