#pragma once

#include <SDL2/SDL.h>
#include "strife/functional/message.h"

namespace strife {
    namespace events {
        
        class InputEvent : public functional::Message {

        public:

            const SDL_Event& event() const;

            InputEvent(const SDL_Event& event);
            ~InputEvent() = default;

        private:

            const SDL_Event& event_;

        };

    }
}