#pragma once

#include "unique.h"
#include "data.h"
#include "entity.h"

namespace strife {
    namespace core {
        
        class Component : public common::Unique {
            
        public:
        
            const Entity entity;
            
            Component(const Entity entity);
			virtual ~Component() = default;
            
            virtual common::Data serialize();
            virtual void deserialize(common::Data data);

        };
        
    }
}