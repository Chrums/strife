#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::common;
using namespace strife::serialization;

IContext& Contexts::Instantiate(const Data& data) {
    return Contexts::Instantiate<void*>(data);
}

void Contexts::Dispose(const IContext& context) {
    const strife::common::Identifier& id = context.id();
    std::map<const strife::common::Identifier, IContext* const>::iterator iterator = Contexts::Contexts_.find(id);
    if (iterator != Contexts::Contexts_.end()) {
        Contexts::Contexts_.erase(iterator);
    }
}

IContext& Contexts::Resolve(const Data& data) {
    const strife::common::Identifier contextId = data[CONTEXT_INDEX].get<strife::common::Identifier>();
    IContext* const context = Contexts::Contexts_.at(contextId);
    return *context;
}

bool Contexts::Exists(const Data& data) {
    if (data.is_object() && !data[CONTEXT_INDEX].is_null()) {
        const strife::common::Identifier contextId = data[CONTEXT_INDEX].get<strife::common::Identifier>();
        std::map<const strife::common::Identifier, IContext* const>::const_iterator iterator = Contexts::Contexts_.find(contextId);
        return iterator != Contexts::Contexts_.end();
    } else {
        return false;
    }
}

std::map<const strife::common::Identifier, IContext* const> Contexts::Contexts_;