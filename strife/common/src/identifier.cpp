#include "identifier.h"

#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace strife::common;

const string strife::common::ToString(const Identifier& id) {
    return boost::lexical_cast<std::string>(id);
}

const Identifier strife::common::ToIdentifier(const string& idString) {
    return boost::lexical_cast<Identifier>(idString);
}