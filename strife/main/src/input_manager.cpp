#include "input_manager.h"

#include <iostream>

using namespace std;
using namespace strife::main;

const float InputManager::ButtonInput::value() const {
    return value_;
}

const bool InputManager::ButtonInput::isDown() const {
    return value_ != 0.0f;
}

void InputManager::KeyInput::process(const SDL_Event& event) {
    switch (event.type) {

        case SDL_KEYDOWN: {
            value_ = 1.0f;
            break;
        }

        case SDL_KEYUP: {
            value_ = 0.0f;
            break;
        }

    }
}

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

const InputManager::ButtonInput& InputManager::key(const SDL_Keycode keyCode) {
    return findKey(keyCode);
}

void InputManager::processMouse(const SDL_Event& event) {
    
}

void InputManager::processKey(const SDL_Event& event) {
    SDL_Keycode keyCode = event.key.keysym.sym;
    InputManager::KeyInput& keyInput = findKey(keyCode);
    keyInput.process(event);
}

InputManager::KeyInput& InputManager::findKey(const SDL_Keycode keyCode) {
    return keyInputs_.emplace(keyCode, InputManager::KeyInput {}).first->second;
}