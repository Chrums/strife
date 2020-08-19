#include "strife/core/system.h"

using namespace std;
using namespace strife::core;
using namespace strife::functional;

System::System()
    : ISystem()
    , scene_(nullptr) {}

void System::subscribe(Dispatcher& dispatcher) {
    dispatcher.subscribe<SceneSwapEvent>(bind(&System::onSceneSwap, this, placeholders::_1));
    dispatcher.subscribe<UpdateEvent>(bind(&System::onUpdate, this, placeholders::_1));
}

void System::unsubscribe(Dispatcher& dispatcher) {
    dispatcher.unsubscribe<SceneSwapEvent>(bind(&System::onSceneSwap, this, placeholders::_1));
    dispatcher.unsubscribe<UpdateEvent>(bind(&System::onUpdate, this, placeholders::_1));
}
            
void System::onSceneSwap(const SceneSwapEvent& sceneSwapEvent) {
    scene_ = sceneSwapEvent.to();
}