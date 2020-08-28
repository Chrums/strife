#pragma once

#include "strife/core/entity.h"
#include "strife/serialization/data.h"
#include "strife/unique/unique.h"

namespace strife {
    namespace core {
        
        class Component : public unique::Unique {
            
        public:
        
            const Entity& entity();
            
            Component(const Entity& entity);
			virtual ~Component();
            
            virtual void initialize();
            virtual void dispose();
            
            virtual const serialization::Data serialize() const;
            virtual void deserialize(const serialization::Data& data);

        private:

            Entity entity_;

        };
        
    }
}