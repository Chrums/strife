#include "input/input_manager.h"

using namespace strife::common;

void InputManager::process(const SDL_Event& event) {
    switch (event.type) {

        case SDL_MOUSEMOTION: {
            processMouse(event);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            processMouse(event);
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            processMouse(event);
            break;
        }

        case SDL_MOUSEWHEEL: {
            processMouse(event);
            break;
        }

        case SDL_KEYDOWN: {
            processKey(event);
            break;
        }

        case SDL_KEYUP: {
            processKey(event);
            break;
        }

    }
}

const MouseInput& InputManager::mouse() {
    return mouseProcessor_;
}

const ButtonInput& InputManager::key(const SDL_Keycode keyCode) {
    return findKey(keyCode);
}

void InputManager::processMouse(const SDL_Event& event) {
    mouseProcessor_.process(event);
}

void InputManager::processKey(const SDL_Event& event) {
    SDL_Keycode keyCode = event.key.keysym.sym;
    KeyButtonProcessor& keyButtonProcessor = findKey(keyCode);
    keyButtonProcessor.process(event);
}

KeyButtonProcessor& InputManager::findKey(const SDL_Keycode keyCode) {
    return keyButtonProcessors_.emplace(keyCode, KeyButtonProcessor {}).first->second;
}