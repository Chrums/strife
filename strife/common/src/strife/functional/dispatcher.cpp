#include "strife/functional/dispatcher.h"

using namespace std;
using namespace strife::functional;

void Dispatcher::emit(const Message& message) {
    const type_index type(typeid(message));
    vector<Callback<Message>> callbacks = callbacks_[type];
    for (Callback<Message> callback : callbacks) {
        callback(message);
    }
}