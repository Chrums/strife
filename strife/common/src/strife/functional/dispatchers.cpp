#include "strife/functional/dispatchers.h"

using namespace std;
using namespace strife::reflection;
using namespace strife::functional;

void Dispatchers::emit(const Message& message) {
    const Type& type = Type::Of(message);
    map<void* const, Callback<const Message&>> callbacks = callbacks_[type];
    for (auto& [that, callback] : callbacks) {
        callback(message);
    }
}

void Dispatchers::emit(void* that, const Message& message) {
    const Type& type = Type::Of(message);
    map<void* const, Callback<const Message&>> callbacks = callbacks_[type];
    map<void* const, Callback<const Message&>>::iterator iterator = callbacks.find(that);
    if (iterator != callbacks.end()) {
        Callback<const Message&>& callback = iterator->second;
        callback(message);
    }
}