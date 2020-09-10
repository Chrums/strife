#pragma once

#include <functional>
#include <map>
#include "strife/functional/message.h"
#include "strife/reflection/type.h"

namespace strife {

    class Dispatcher {

#pragma region Callback

    public:

        template <typename M>
        using Callback = std::function<void (M)>;

#pragma endregion

#pragma region Binding

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

#pragma endregion

    public:

        template <typename M>
        void emit(const M& message) {
            const Type& type = Type::Of(message);
            std::map<void* const, Callback<const Message&>>& callbacks = callbacks_[type];
            for (auto& [that, callback] : callbacks) {
                callback(message);
            }
        }

        template <typename M>
        void emit(void* that, const M& message) {
            const Type& type = Type::Of(message);
            std::map<void* const, Callback<const Message&>>& callbacks = callbacks_[type];
            std::map<void* const, Callback<const Message&>>::iterator iterator = callbacks.find(that);
            if (iterator != callbacks.end()) {
                Callback<const Message&>& callback = iterator->second;
                callback(message);
            }
        }

        template <typename M, typename T, typename F> 
        void subscribe(T* const that, F&& callable) {
            const Type& type = Type::Of<M>();

            Callback<const M&> callback = std::bind(callable, that, std::placeholders::_1);
            Binding<M> binding(callback);

            std::map<void* const, Callback<const Message&>>& callbacks = callbacks_[type];
            callbacks.insert({that, binding});
        }

        void unsubscribe(void* const that);

        template <typename M>
        void unsubscribe(void* const that) {
            const Type& type = Type::Of<M>();

            std::map<void* const, Callback<const Message&>>& callbacks = callbacks_[type];
            callbacks.erase(that);
        }

    private:

        std::map<const Type, std::map<void* const, Callback<const Message&>>> callbacks_;

    };

}