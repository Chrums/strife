#pragma once

#include <map>
#include <string>
#include "strife/serialization/context.h"
#include "strife/serialization/data.h"

#define CONTEXT_INDEX "__CONTEXT__"

namespace strife {
    namespace serialization {

        class Contexts {

        public:

            static IContext& Instantiate(const Data& data);
            static void Dispose(const IContext& context);

            static void Require(Data& data);
            static IContext& Resolve(const Data& data);
            static bool Exists(const Data& data);

            template <class U>
            static Context<U>& Instantiate(const Data& data) {
                Context<U>* context = new Context<U>(data);
                const strife::unique::Identifier& id = context->id();
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

            static std::map<const strife::unique::Identifier, IContext* const> Contexts_;

        };

    }
}