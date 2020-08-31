#include "strife/functional/dispatcher.h"

using namespace std;
using namespace strife::functional;
using namespace strife::reflection;

void Dispatcher::emit(const Message& message) {
    const Type type = Type::Of(message);
    list<weak_ptr<Callback<const Message&>>> callbackPointers = callbackPointers_[type];
    for (typename std::list<std::weak_ptr<Callback<const Message&>>>::iterator iterator = callbackPointers.begin(); iterator != callbackPointers.end(); ++iterator) {
        std::weak_ptr<Callback<const Message&>>& callbackPointer = *iterator;
        if (callbackPointer.expired()) {
            callbackPointers.erase(iterator);
        } else {
            Callback<const Message&>& callback = *callbackPointer.lock();
            callback(message);
        }
    }
}

void Dispatcher::unsubscribe(Token<const Message&>& token) {
    token.dispose();
}