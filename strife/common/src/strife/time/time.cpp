#include "strife/time/time.h"

using namespace strife::time;

const float& Time::total() const {
    return total_;
}

const float& Time::delta() const {
    return delta_;
}

Time::Time()
    : total_(0.0f)
    , delta_(0.0f) {}

Time::Time(const float& total, const float& delta)
    : total_(total)
    , delta_(delta) {}