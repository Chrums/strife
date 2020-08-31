#pragma once

#include <map>
#include <string>
#include "strife/serialization/context.h"
#include "strife/serialization/data.h"
#include "strife/reflection/type.h"

#define CONTEXT_INDEX "__CONTEXT__"

namespace strife {
    namespace serialization {

        class Contexts {

        public:

            static Context& Instantiate(const Data& data);
            static void Dispose(const Context& context);

            static void Require(Data& data, std::string index);
            static Context& Resolve(const Data& data);
            static bool Exists(const Data& data);

            template <class T>
            static void Require(Data& data) {
                std::string index = reflection::Type::Of<T>().name();
                Require(data, index);
            }

            template <class T>
            static T& Resolve(const Data& data) {
                Context& context = Contexts::Resolve(data);
                return context.resolve<T>(data);
            }

            Contexts() = delete;
            ~Contexts() = delete;

        private:

            static std::map<const unique::Identifier, Context> Contexts_;

        };

    }
}