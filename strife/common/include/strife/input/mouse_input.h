#pragma once

#include <map>
#include <SDL2/SDL.h>
#include "strife/input/button_input.h"
#include "strife/input/mouse_button_processor.h"
#include "strife/math/vector2.h"

namespace strife {
    namespace input {

        class MouseInput {

        public:

            enum Button {
                LEFT = 1,
                MIDDLE = 2,
                RIGHT = 3,
                MOUSE_4 = 4,
                MOUSE_5 = 5
            };
            
        public:

            MouseInput() = default;
            ~MouseInput() = default;

            const math::Vector2& position() const;
            const ButtonInput& button(const int index);

        protected:

            math::Vector2 position_;
            std::map<int, MouseButtonProcessor> mouseButtonProcessors_;

            MouseButtonProcessor& findMouseButtonProcessor(const int index);

        };

    }
}