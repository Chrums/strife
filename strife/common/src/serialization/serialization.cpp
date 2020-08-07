#include "serialization/serialization.h"

using namespace std;
using namespace strife::common;

Contexts& Serialization::Contexts() {
    return Serialization::Contexts_;
}

bool Serialization::IsReference(const Data& data) {
    return data.is_object() && data[REFERENCE].get<bool>();
}

void Serialization::Reference(Data& data, const Identifier& id) {
    data[REFERENCE] = true;
    data[IDENTIFIER] = strife::common::ToString(id);
}

const Identifier Serialization::Identify(const Data& data) {
    string id = data[IDENTIFIER].get<string>();
    return strife::common::ToIdentifier(id);
}

strife::common::Contexts Serialization::Contexts_;