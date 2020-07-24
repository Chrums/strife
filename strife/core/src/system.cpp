#include "system.h"

using namespace strife::core;
using namespace strife::common;

System::System()
    : ISystem()
    , scene_(nullptr) {}

void System::subscribe(Dispatcher& dispatcher) {
    dispatcher.subscribe<SceneSwapEvent>(std::bind(&System::onSceneSwap, this, std::placeholders::_1));
    dispatcher.subscribe<UpdateEvent>(std::bind(&System::onUpdate, this, std::placeholders::_1));
}

void System::unsubscribe(Dispatcher& dispatcher) {
    dispatcher.unsubscribe<SceneSwapEvent>(std::bind(&System::onSceneSwap, this, std::placeholders::_1));
    dispatcher.unsubscribe<UpdateEvent>(std::bind(&System::onUpdate, this, std::placeholders::_1));
}
            
void System::onSceneSwap(const SceneSwapEvent& sceneSwapEvent) {
    scene_ = sceneSwapEvent.to;
}