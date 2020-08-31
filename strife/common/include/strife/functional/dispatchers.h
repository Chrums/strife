#pragma once

#include <functional>
#include <map>
#include "strife/functional/callback.h"
#include "strife/functional/message.h"
#include "strife/reflection/type.h"

namespace strife {
    namespace functional {

        class Dispatchers {

        public:

            template <typename M>
            class Binding {

            public:

                Binding(Callback<const M&> callback)
                    : callback_(callback) {}

                ~Binding() = default;

                void operator()(const Message& message) {
                    const M& value = static_cast<const M&>(message);
                    callback_(value);
                }

            private:

                Callback<const M&> callback_;

            };

        public:

            void emit(const Message& message);
            void emit(void* that, const Message& message);

            template <typename M, typename T, typename F> 
            void subscribe(T* const that, F&& callable) {
                const reflection::Type& type = reflection::Type::Of<M>();

                Callback<const M&> callback = std::bind(callable, that, std::placeholders::_1);
                Binding<M> binding(callback);

                std::map<void* const, Callback<const Message&>> callbacks = callbacks_[type];
                callbacks.insert({that, binding});
            }

            template <typename M, typename T>
            void unsubscribe(T* const that) {
                const reflection::Type& type = reflection::Type::Of<M>();

                std::map<void* const, Callback<const Message&>> callbacks = callbacks_[type];
                callbacks.erase(that);
            }

        private:

            std::map<const reflection::Type, std::map<void* const, Callback<const Message&>>> callbacks_;

        };
        
    }
}