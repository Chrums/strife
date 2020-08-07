#pragma once

#include <map>
#include "identifier.h"
#include "serialization/data.h"
#include "unique.h"
#include "serialization/contexts.h"

#define REFERENCE "__REFERENCE__"
#define IDENTIFIER "__IDENTIFIER__"

namespace strife {
    namespace common {

        class Serialization {
            
        public:
        
            static strife::common::Contexts& Contexts();

            static bool IsReference(const Data& data);
            static void Reference(Data& data, const Identifier& identifier);
            static const Identifier Identify(const Data& data);

            Serialization() = delete;
            ~Serialization() = delete;

        private:

            static strife::common::Contexts Contexts_;

        };

    }
}