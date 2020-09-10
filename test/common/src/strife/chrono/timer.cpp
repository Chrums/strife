#include "strife/chrono/timer.h"

using namespace std;
using namespace strife;

#pragma region Value

Timer::Value::Value()
    : total(0.0f)
    , delta(0.0f) {}

Timer::Value::Value(const float& total, const float& delta)
    : total(total)
    , delta(delta) {}

#pragma endregion

Timer::Timer()
    : initial_(std::chrono::steady_clock::now())
    , current_(std::chrono::steady_clock::now()) {}
    
const Timer::Value Timer::evaluate() {
    std::chrono::time_point<std::chrono::steady_clock> next = std::chrono::steady_clock::now();
    std::chrono::duration<float> total = next - initial_;
    std::chrono::duration<float> delta = next - current_;
    current_ = next;
    return Value(total.count(), delta.count());
}