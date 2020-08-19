#include "strife/serialization/context.h"

#include "strife/serialization/contexts.h"

#include <iostream>

using namespace std;
using namespace strife::common;
using namespace strife::serialization;

void IContext::Require(Data& data) {
    if (data.is_null() || data.is_object()) {
        data[CONTEXT_INDEX] = Unique::Nil().id();
    }
}

IContext::IContext(const Data& data)
    : data(apply(data)) {}

void IContext::dispose() {
    Contexts::Dispose(*this);
}

const Data IContext::apply(const Data& data) const {
    Data other;

    if (data.is_array()) {
        for (const Data& item : data) {
            other += apply(item);
        }
    } else if (data.is_object()) {
        for (auto& [key, value] : data.items()) {
            other[key] = apply(value);
        }

        if (data.find(CONTEXT_INDEX) != data.end()) {
            other[CONTEXT_INDEX] = id();
        }
    } else {
        other = data;
    }

    return other;
}