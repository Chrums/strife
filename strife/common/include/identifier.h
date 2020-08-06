#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include "serialization/data.h"

namespace strife {
    namespace common {
        
        using Identifier = boost::uuids::uuid;

        // std::string to_string(const Identifier& identifier) {
        //     return boost::lexical_cast<std::string>(identifier);
        // }

        // void to_json(Data& data, const Identifier& identifier) {
        //     data = boost::lexical_cast<std::string>(identifier);
        // }

        // void from_json(const Data& data, Identifier& identifier) {
        //     std::string value = data.get<std::string>();
        //     identifier = boost::lexical_cast<Identifier>(value);
        // }
        
    }
}