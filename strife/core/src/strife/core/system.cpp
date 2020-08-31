#include "strife/core/system.h"

using namespace std;
using namespace strife::core;
using namespace strife::events;
using namespace strife::functional;

void ISystem::configure(Dispatcher& dispatcher) {
    dispatcher_ = &dispatcher;
}

const Dispatcher& ISystem::dispatcher() const {
    return *dispatcher_;
}

Dispatcher& ISystem::dispatcher() {
    return *dispatcher_;
}