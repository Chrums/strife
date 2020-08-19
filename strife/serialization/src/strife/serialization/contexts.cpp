#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::serialization;
using namespace strife::unique;

IContext& Contexts::Instantiate(const Data& data) {
    return Contexts::Instantiate<void*>(data);
}

void Contexts::Dispose(const IContext& context) {
    const Identifier& id = context.id();
    map<const Identifier, IContext* const>::iterator iterator = Contexts::Contexts_.find(id);
    if (iterator != Contexts::Contexts_.end()) {
        Contexts::Contexts_.erase(iterator);
    }
}

void Contexts::Require(Data& data) {
    if (data.is_null() || data.is_object()) {
        data[CONTEXT_INDEX] = Unique::Nil().id();
    }
}

IContext& Contexts::Resolve(const Data& data) {
    const Identifier contextId = data[CONTEXT_INDEX].get<Identifier>();
    IContext* const context = Contexts::Contexts_.at(contextId);
    return *context;
}

bool Contexts::Exists(const Data& data) {
    if (data.is_object() && !data[CONTEXT_INDEX].is_null()) {
        const Identifier contextId = data[CONTEXT_INDEX].get<Identifier>();
        map<const Identifier, IContext* const>::const_iterator iterator = Contexts::Contexts_.find(contextId);
        return iterator != Contexts::Contexts_.end();
    } else {
        return false;
    }
}

map<const Identifier, IContext* const> Contexts::Contexts_;