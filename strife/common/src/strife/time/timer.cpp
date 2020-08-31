#include "strife/time/timer.h"

using namespace strife::time;

Timer::Timer()
    : initial(std::chrono::steady_clock::now())
    , current(std::chrono::steady_clock::now()) {}
    
Time Timer::update() {
    std::chrono::time_point<std::chrono::steady_clock> next = std::chrono::steady_clock::now();
    std::chrono::duration<float> total = next - initial;
    std::chrono::duration<float> delta = next - current;
    current = next;
    return Time(total.count(), delta.count());
}