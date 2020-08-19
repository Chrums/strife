#pragma once

namespace strife {
    namespace input {

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