#pragma once

#include <chrono>

namespace strife {
    namespace time {
        
        class Timer {
        
        public:
        
            class Value {
                
            public:
            
                const float& total() const;
                const float& delta() const;
            
                Value();
                Value(const float& total, const float& delta);
                ~Value() = default;

            private:

                float total_;
                float delta_;
                
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