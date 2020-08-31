#pragma once

namespace strife {
    namespace time {

        class Time {
                
        public:
        
            const float& total() const;
            const float& delta() const;
        
            Time();
            Time(const float& total, const float& delta);
            ~Time() = default;

        private:

            float total_;
            float delta_;
                
        };

    }
}