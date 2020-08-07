#include "serialization/contexts.h"

using namespace std;
using namespace strife::common;

Contexts::IContext& Contexts::instantiate() {
    Contexts::Context<void*>* context = new Contexts::Context<void*>();
    const Identifier id = context->id();
    contexts_.insert({id, context});
    return *context;
}

void Contexts::dispose(IContext& context) {
    const Identifier id = context.id();
    std::map<const Identifier, Contexts::IContext* const>::iterator iterator = contexts_.find(id);
    contexts_.erase(iterator);
}

Contexts::IContext& Contexts::at(const Data& data) const {
    const std::string idString = data[CONTEXT].get<std::string>();
    const Identifier id = strife::common::ToIdentifier(idString);
    Contexts::IContext* const context = contexts_.at(id);
    return *context;
}