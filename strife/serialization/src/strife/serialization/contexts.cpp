#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::serialization;
using namespace strife::unique;

Context& Contexts::Instantiate(const Data& data) {
    Context context(data);
    const Identifier& id = context.id();
    return Contexts::Contexts_.insert({id, context}).first->second;
}

void Contexts::Dispose(const Context& context) {
    const Identifier& id = context.id();
    map<const Identifier, Context>::iterator iterator = Contexts::Contexts_.find(id);
    if (iterator != Contexts::Contexts_.end()) {
        Contexts::Contexts_.erase(iterator);
    }
}

void Contexts::Require(Data& data, string index) {
    if (data.is_null() || data.is_object()) {
        data[CONTEXT_INDEX] = Unique::Nil().id();
        Context::Require(data, index);
    }
}

Context& Contexts::Resolve(const Data& data) {
    const Identifier contextId = data[CONTEXT_INDEX].get<Identifier>();
    Context& context = Contexts::Contexts_.at(contextId);
    return context;
}

bool Contexts::Exists(const Data& data) {
    if (data.is_object() && !data[CONTEXT_INDEX].is_null()) {
        const Identifier contextId = data[CONTEXT_INDEX].get<Identifier>();
        map<const Identifier, Context>::const_iterator iterator = Contexts::Contexts_.find(contextId);
        return iterator != Contexts::Contexts_.end();
    } else {
        return false;
    }
}

map<const Identifier, Context> Contexts::Contexts_;