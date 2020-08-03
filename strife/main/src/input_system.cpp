#include "input_system.h"

#include "engine.h"

#include <iostream>

using namespace strife::main;
using namespace strife::common;
using namespace strife::core;
     
void InputSystem::subscribe(Dispatcher& dispatcher) {
    Engine& engine = Engine::Instance();
    engine.inputEvent += std::bind(&InputSystem::process, this, std::placeholders::_1);
}

void InputSystem::unsubscribe(Dispatcher& dispatcher) {
    Engine& engine = Engine::Instance();
    engine.inputEvent -= std::bind(&InputSystem::process, this, std::placeholders::_1);
}

void InputSystem::process(const SDL_Event& event)
{
    inputManager.process(event);
}