#pragma once

#include <functional>
#include <vector>

namespace strife {
    namespace common {
        
        template <class ...Args>
        class Action {
            
        public:
        
            using Callback = std::function<void (Args...)>;
            
        public:
        
            Action() = default;
            ~Action() = default;

            void operator()(Args... args) {
                invoke(args...);
            }

            Action<Args...>& operator+=(Callback callback) {
                subscribe(callback);
                return *this;
            }

            Action<Args...>& operator-=(Callback callback) {
                unsubscribe(callback);
                return *this;
            }
        
            void subscribe(Callback callback) {
                callbacks_.push_back(callback);
            }
            
            void unsubscribe(Callback callback) {
                // typename std::vector<Callback>::iterator iterator = std::find(callbacks_.begin(), callbacks_.end(), callback);
                // callbacks_.erase(iterator);

                // TODO: Implement this...
                // The above method doesn't work becuase std::function are not comparable
            }

            void invoke(Args... args) {
                for (Callback callback : callbacks_) {
                    callback(args...);
                }
            }
            
		private:
		
			std::vector<Callback> callbacks_;
            
        };
        
    }
}