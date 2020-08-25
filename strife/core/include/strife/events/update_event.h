#pragma once

#include "strife/functional/message.h"

namespace strife {
    namespace events {
        
        class UpdateEvent : public functional::Message {
            
        public:
        
            UpdateEvent() = default;
            ~UpdateEvent() = default;
            
        };

    }
}