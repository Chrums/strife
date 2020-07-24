#pragma once

#include "unique.h"
#include "entity.h"

namespace strife {
    namespace core {
        
        class Component : public common::Unique {
            
        public:
        
            const Entity entity;
            
            Component(const Entity entity);
			virtual ~Component() = default;
            
        };
        
    }
}