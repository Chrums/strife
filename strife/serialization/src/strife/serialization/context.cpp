#include "strife/serialization/context.h"

#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::common;
using namespace strife::serialization;

void IContext::Apply(Data& data) {
    if (data.is_null() || data.is_object()) {
        data[CONTEXT] = string();
    }
}

bool IContext::Is(const Data& data) {
    return data.is_object() && data[CONTEXT].is_string();
}

void IContext::dispose() {
    Contexts::Dispose(*this);
}

void IContext::apply(Data& data) const {
    if (IContext::Is(data)) {
        data[CONTEXT] = strife::common::ToString(id_);
    }
}