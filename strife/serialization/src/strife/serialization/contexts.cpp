#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::common;
using namespace strife::serialization;

IContext& Contexts::Instantiate() {
    return Contexts::Instantiate<void*>();
}

void Contexts::Dispose(const IContext& context) {
    const strife::common::Identifier& id = context.id();
    std::map<const strife::common::Identifier, IContext* const>::iterator iterator = Contexts::Contexts_.find(id);
    if (iterator != Contexts::Contexts_.end()) {
        Contexts::Contexts_.erase(iterator);
    }
}

IContext& Contexts::Resolve(const Data& data) {
    const std::string idString = data[CONTEXT].get<std::string>();
    const strife::common::Identifier id = strife::common::ToIdentifier(idString);
    IContext* const context = Contexts::Contexts_.at(id);
    return *context;
}

bool Contexts::Exists(const Data& data) {
    if (data.is_object() && data[CONTEXT].is_string()) {
        const std::string idString = data[CONTEXT].get<std::string>();
        const strife::common::Identifier id = strife::common::ToIdentifier(idString);
        std::map<const strife::common::Identifier, IContext* const>::iterator iterator = Contexts::Contexts_.find(id);
        return iterator != Contexts::Contexts_.end();
    } else {
        return false;
    }
}

std::map<const strife::common::Identifier, IContext* const> Contexts::Contexts_;