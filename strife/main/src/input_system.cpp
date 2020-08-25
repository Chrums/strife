#include "input_system.h"

using namespace std;
using namespace strife::core;
using namespace strife::events;
using namespace strife::main;
using namespace strife::functional;
     
void InputSystem::subscribe(Dispatcher& dispatcher) {
    dispatcher.subscribe<InputEvent>(bind(&InputSystem::process, this, placeholders::_1));
}

void InputSystem::unsubscribe(Dispatcher& dispatcher) {
    dispatcher.unsubscribe<InputEvent>(bind(&InputSystem::process, this, placeholders::_1));
}

void InputSystem::process(const InputEvent& inputEvent)
{
    const SDL_Event& event = inputEvent.event();
    inputManager.process(event);
}