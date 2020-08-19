#pragma once

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>

namespace strife {
    namespace unique {
        
        using Identifier = boost::uuids::uuid;

        const std::string ToString(const Identifier& id);
        const Identifier ToIdentifier(const std::string& idString);
        
    }
}

namespace nlohmann {

    template <>
    struct adl_serializer<strife::unique::Identifier> {

        static void to_json(nlohmann::json& json, const strife::unique::Identifier& id) {
            std::string value = boost::lexical_cast<std::string>(id);
            json = value;
        }

        static void from_json(const nlohmann::json& json, strife::unique::Identifier& id) {
            std::string value = json.get<std::string>();
            id = boost::lexical_cast<strife::unique::Identifier>(value);
        }

    };
    
}