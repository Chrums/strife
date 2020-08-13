#pragma once

#include <map>
#include <string>
#include "strife/serialization/context.h"
#include "strife/serialization/data.h"

#define CONTEXT "__CONTEXT__"

namespace strife {
    namespace serialization {

        class Contexts {

        public:

            static IContext& Instantiate();
            static void Dispose(const IContext& context);
            static IContext& Resolve(const Data& data);
            static bool Exists(const Data& data);

            template <class U>
            static Context<U>& Instantiate() {
                Context<U>* context = new Context<U>();
                const strife::common::Identifier& id = context->id();
                Contexts::Contexts_.insert({id, context});
                return *context;
            }

            template <class U>
            static Context<U>& Resolve(const Data& data) {
                IContext& context = Contexts::Resolve(data);
                return static_cast<Context<U>&>(context);
            }

            Contexts() = delete;
            ~Contexts() = delete;

        private:

            static std::map<const strife::common::Identifier, IContext* const> Contexts_;

        };

    }
}