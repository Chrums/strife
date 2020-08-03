#pragma once

#include <chrono>

namespace strife {
    namespace common {
        
        class Timer {
            
        public:
        
            class Value {
                
            public:
            
                float total;
                float delta;
            
                Value();
                Value(float total, float delta);
                ~Value() = default;
                
            };
            
        public:
        
            Timer();
            virtual ~Timer() = default;
            
            Timer::Value update();
            
        private:
        
            std::chrono::time_point<std::chrono::steady_clock> initial;
            std::chrono::time_point<std::chrono::steady_clock> current;
            
        };
        
    }
}