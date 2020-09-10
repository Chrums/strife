#pragma once

#include "strife/common.h"

namespace strife {

    class ISystem {

    public:
    
        ISystem(Dispatcher& dispatcher);
        virtual ~ISystem() = default;

        virtual void initialize() = 0;
        virtual void dispose() = 0;

    protected:

        Dispatcher& dispatcher_;

    };

    template <class Derived>
    class System {

        using ISystem::ISystem;

    public:

        virtual void initialize() {}
        virtual void dispose() {}
            
    protected:
        
        template <typename M, typename F>
        void subscribe(F&& callable) {
            Derived* const that = derived();
            dispatcher_.subscribe<M>(that, callable);
        }

        template <typename M>
        virtual void unsubscribe() {
            Derived* const that = derived();
            dispatcher_.unsubscribe<M>(that);
        }

    private:

        Derived* const derived() const {
            return static_cast<Derived* const>(*this);
        }
        
    };

}