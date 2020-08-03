#pragma once

namespace strife {
    namespace common {

        class ButtonInput {

        public:

            ButtonInput() = default;
            ~ButtonInput() = default;

            const float value() const;
            const bool isDown() const;

        protected:

            float value_;

        };
        
    }
}