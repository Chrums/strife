#pragma once

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace strife {

    class Identifier {

#pragma region Static

    public:

        static Identifier Nil();
        static Identifier Random();

    private:

        static boost::uuids::nil_generator NilGenerator;
        static boost::uuids::random_generator RandomGenerator;

#pragma endregion

#pragma region Non-Static

    public:

        Identifier();
        Identifier(const Identifier& identifier);
        ~Identifier() = default;

        Identifier& operator=(const Identifier& identifier);
        bool operator==(const Identifier& identifier) const;
        bool operator<(const Identifier& identifier) const;
        
        Identifier& operator=(const std::string& value);
        operator std::string() const;

    private:

        boost::uuids::uuid uuid_;

        Identifier(const boost::uuids::uuid& uuid);

#pragma endregion

    };

}