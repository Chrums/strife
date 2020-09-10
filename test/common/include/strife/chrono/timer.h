#pragma once

#include <chrono>

namespace strife {

    class Timer {

#pragma region Value

    public:

        class Value {

        public:

            const float total;
            const float delta;

            Value();
            Value(const float& total, const float& delta);
            ~Value() = default;

        };

#pragma endregion

    public:

        Timer();
        virtual ~Timer() = default;
        
        const Timer::Value evaluate();
        
    private:
    
        std::chrono::time_point<std::chrono::steady_clock> initial_;
        std::chrono::time_point<std::chrono::steady_clock> current_;

    };

}