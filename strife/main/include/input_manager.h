#pragma once

#include <map>
#include <SDL2/SDL.h>
#include "vector2.h"

namespace strife {
    namespace main {

        class InputManager {

        public:

            class ButtonInput {

            public:

                ButtonInput() = default;
                ~ButtonInput() = default;

                const float value() const;
                const bool isDown() const;

            protected:

                float value_;

            };

            class MouseInput {

            public:

                MouseInput() = default;
                ~MouseInput() = default;

                const math::Vector2& position() const;
                const InputManager::ButtonInput& button(const int index);

            private:

                math::Vector2 position_;
                std::map<int, InputManager::ButtonInput> buttonInputs_;

            };

            class KeyInput : public ButtonInput {

                friend class InputManager;

            public:

                KeyInput() = default;
                ~KeyInput() = default;

            protected:
            
                void process(const SDL_Event& event);

            };

        public:

            InputManager() = default;
            ~InputManager() = default;

            void process(const SDL_Event& event);

            const InputManager::MouseInput& mouse();
            const InputManager::ButtonInput& key(const SDL_Keycode keyCode);

        private:

            std::map<SDL_Keycode, InputManager::KeyInput> keyInputs_;
            
            void processMouse(const SDL_Event& event);
            void processKey(const SDL_Event& event);
            InputManager::KeyInput& findKey(const SDL_Keycode keyCode);

        };

    }
}