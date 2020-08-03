#pragma once

#include <map>
#include <SDL2/SDL.h>
#include "input/button_input.h"
#include "input/mouse_button_processor.h"
#include "vector2.h"

namespace strife {
    namespace common {

        class MouseInput {

        public:

            MouseInput() = default;
            ~MouseInput() = default;

            const math::Vector2& position() const;
            const ButtonInput& button(const int index);

        protected:

            math::Vector2 position_;
            std::map<int, MouseButtonProcessor> mouseButtonProcessors_;

        };

    }
}