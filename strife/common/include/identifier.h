#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include "serialization/data.h"

namespace strife {
    namespace common {
        
        using Identifier = boost::uuids::uuid;

        const std::string ToString(const Identifier& id);
        const Identifier ToIdentifier(const std::string& idString);
        
    }
}