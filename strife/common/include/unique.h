#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "identifier.h"

namespace strife {
    namespace common {
        
        class Unique {
            
        public:
            
            static boost::uuids::nil_generator NilGenerator;
            static boost::uuids::random_generator RandomGenerator;
            
            static Unique Nil();
            static Unique Random();
            
            Identifier id;
            
            Unique();
            Unique(const Unique& unique);
            Unique(const Identifier id);
            ~Unique() = default;
            
            bool operator==(const Unique& unique) const;
            bool operator<(const Unique& unique) const;
            
        };
        
    }
}