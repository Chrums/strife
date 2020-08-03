#include "dispatch/dispatcher.h"

using namespace strife::common;
using namespace std;

void Dispatcher::emit(const Message& message) {
    const type_index type(typeid(message));
    vector<Callback<Message>> callbacks = callbacks_[type];
    for (Callback<Message> callback : callbacks) {
        callback(message);
    }
}