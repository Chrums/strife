#pragma once

#include <functional>
#include <memory>
#include "strife/functional/callback.h"

namespace strife {
    namespace functional {
            
        template <typename ...Args>
        class Token {

        public:

            Token()
                : callbackPointer_(nullptr) {}

            Token(std::shared_ptr<Callback<Args...>> callbackPointer)
                : callbackPointer_(callbackPointer) {}

            ~Token() {
                dispose();
            }

            void dispose() {
                callbackPointer_.reset();
            }

        private:

            std::shared_ptr<Callback<Args...>> callbackPointer_;

        };
    
    }
}