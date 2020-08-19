#include "strife/time/timer.h"

using namespace strife::time;

Timer::Value::Value()
    : total(0.0f)
    , delta(0.0f) {}

Timer::Value::Value(float total, float delta)
    : total(total)
    , delta(delta) {}

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