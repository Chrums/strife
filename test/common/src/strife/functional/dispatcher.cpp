#include "strife/functional/dispatcher.h"

using namespace std;
using namespace strife;

void Dispatcher::unsubscribe(void* const that) {
    for (auto& [type, callbacks] : callbacks_) {
        callbacks.erase(that);
    }
}