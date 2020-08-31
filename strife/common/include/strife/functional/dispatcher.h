#pragma once

#include <functional>
#include <list>
#include <map>
#include <typeindex>
#include "strife/functional/callback.h"
#include "strife/functional/message.h"
#include "strife/functional/token.h"
#include "strife/reflection/type.h"

namespace strife {
    namespace functional {
        
        class Dispatcher {
            
        protected:
            
            template <class M>
            class Binding {
            
            public:
            
                Binding(Callback<M> callback)
                    : callback_(callback) {}
                    
                ~Binding() = default;
                    
                void operator()(const Message& message) {
                    const M& typedMessage = static_cast<const M&>(message);
                    callback_(typedMessage);
                }
                
            private:
            
                const Callback<const M&> callback_;
            
            };
            
        public:
        
            Dispatcher() = default;
            ~Dispatcher() = default;
        
            void emit(const Message& message);
            void unsubscribe(Token<const Message&>& token);
            
            template <class M>
            Token<const Message&> subscribe(Callback<const M&> callback) {
                const reflection::Type type = reflection::Type::Of<M>();

                Binding<M> binding(callback);
                std::shared_ptr<Callback<const Message&>> callbackPointer = std::make_shared<Callback<const Message&>>(binding);

                std::list<std::weak_ptr<Callback<const Message&>>>& callbacks = callbackPointers_[type];
                callbacks.push_back(callbackPointer);
                
                Token<const Message&> token(callbackPointer);
                return token;
            }
            
		private:
		
			std::map<const reflection::Type, std::list<std::weak_ptr<Callback<const Message&>>>> callbackPointers_;
            
        };
        
    }
}