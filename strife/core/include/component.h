#pragma once

#include "unique.h"
#include "serialization/data.h"
#include "entity.h"

namespace strife {
    namespace core {
        
        class Component : public common::Unique {
            
        public:
        
            const Entity entity;
            
            Component(const Entity entity);
			virtual ~Component() = default;
            
            virtual const common::Data serialize() const;
            virtual void deserialize(const common::Data data);

        };
        
    }
}