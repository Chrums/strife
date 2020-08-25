#include "strife/serialization/context.h"

#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::serialization;
using namespace strife::unique;

void Context::Require(Data& data, string index) {
    data[ITEM_INDEX] = index;
}

Context::Context(const Data& data)
    : data(apply(data)) {}

Context::~Context() {
    for (auto& [index, item] : items_) {
        free(item);
    }
}

void Context::dispose() {
    Contexts::Dispose(*this);
}

const Data Context::apply(const Data& data) const {
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