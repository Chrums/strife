#include "strife/unique/identifier.h"

#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace strife::unique;

const string strife::unique::ToString(const Identifier& id) {
    return boost::lexical_cast<std::string>(id);
}

const Identifier strife::unique::ToIdentifier(const string& idString) {
    return boost::lexical_cast<Identifier>(idString);
}