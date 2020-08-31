#pragma once

#include <map>
#include <SDL2/SDL.h>
#include "strife/input/button_input.h"
#include "strife/input/mouse_button_processor.h"

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

            const std::pair<int, int>& position() const;
            const ButtonInput& button(const int index);

        protected:

            std::pair<int, int> position_;
            std::map<int, MouseButtonProcessor> mouseButtonProcessors_;

            MouseButtonProcessor& findMouseButtonProcessor(const int index);

        };

    }
}