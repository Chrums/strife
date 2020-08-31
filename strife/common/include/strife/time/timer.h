#pragma once

#include <chrono>
#include "strife/time/time.h"

namespace strife {
    namespace time {
        
        class Timer {
                    
        public:
        
            Timer();
            ~Timer() = default;
            
            Time update();
            
        private:
        
            std::chrono::time_point<std::chrono::steady_clock> initial;
            std::chrono::time_point<std::chrono::steady_clock> current;
            
        };
        
    }
}