#pragma once

#include <functional>
#include <list>
#include <memory>
#include "strife/functional/callback.h"
#include "strife/functional/token.h"

namespace strife {
    namespace functional {
        
        template <typename ...Args>
        class Action {
            
        public:

            const int count() const {
                return callbackPointers_.size();
            }
        
            Action() = default;
            ~Action() = default;

            void operator()(Args... args) {
                invoke(args...);
            }

            void invoke(Args... args) {
                for (typename std::list<std::weak_ptr<Callback>>::iterator iterator = callbackPointers_.begin(); iterator != callbackPointers_.end(); ++iterator) {
                    std::weak_ptr<Callback>& callbackPointer = *iterator;
                    if (callbackPointer.expired()) {
                        callbackPointers_.erase(iterator);
                    } else {
                        Callback& callback = *callbackPointer.lock();
                        callback(args...);
                    }
                }
            }
        
            Token<Args...> subscribe(Callback callback) {
                std::shared_ptr<Callback> callbackPointer = std::make_shared<Callback>(callback);
                callbackPointers_.push_back(callbackPointer);
                Token token(callbackPointer);
                return token;
            }
            
            void unsubscribe(Token& token) {
                token.dispose();
            }
            
		private:
		
			std::list<std::weak_ptr<Callback>> callbackPointers_;
            
        };
        
    }
}