#pragma once

#include <functional>
#include <memory>

namespace strife {
    namespace functional {
        
        template <typename ...Args>
        using Callback = std::function<void (Args...)>;

    }
}