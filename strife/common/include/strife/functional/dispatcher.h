#pragma once

#include <functional>
#include <map>
#include <typeindex>
#include <vector>
#include "strife/functional/message.h"

namespace strife {
    namespace functional {
        
        class Dispatcher {
        
        public:
        
            template <class M>
            using Callback = std::function<void (const M&)>;
            
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
            
                const Callback<M> callback_;
            
            };
            
        public:
        
            Dispatcher() = default;
            ~Dispatcher() = default;
        
            void emit(const Message& message);
            
            template <class M>
            void subscribe(Callback<M> callback) {
                const std::type_index type(typeid(M));
                std::vector<Callback<Message>>& callbacks = callbacks_[type];
                Binding<M> binding(callback);
                callbacks.push_back(binding);
            }
            
            template <class M>
            void unsubscribe(Callback<M> callback) {
                const std::type_index type(typeid(M));
                std::vector<Callback<Message>>& callbacks = callbacks_[type];
                // TODO: Implement this...
            }
            
		private:
		
			std::map<const std::type_index, std::vector<Callback<Message>>> callbacks_;
            
        };
        
    }
}