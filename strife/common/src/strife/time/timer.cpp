#include "strife/time/timer.h"

using namespace strife::time;

const float& Timer::Value::total() const {
    return total_;
}

const float& Timer::Value::delta() const {
    return delta_;
}

Timer::Value::Value()
    : total_(0.0f)
    , delta_(0.0f) {}

Timer::Value::Value(const float& total, const float& delta)
    : total_(total)
    , delta_(delta) {}

Timer::Timer()
    : initial(std::chrono::steady_clock::now())
    , current(std::chrono::steady_clock::now()) {}
    
Timer::Value Timer::update() {
    std::chrono::time_point<std::chrono::steady_clock> next = std::chrono::steady_clock::now();
    std::chrono::duration<float> total = next - initial;
    std::chrono::duration<float> delta = next - current;
    current = next;
    return Timer::Value(total.count(), delta.count());
}