#pragma once

#include <map>
#include "unique.h"
#include "strife/serialization/data.h"

namespace strife {
    namespace serialization {

        class IContext : public common::Unique {

        public:

            static void Apply(Data& data);
            static bool Is(const Data& data);

            void dispose();
            void apply(Data& data) const;

        protected:

            IContext() = default;
            ~IContext() = default;

        };

        template <class T>
        class Context : public IContext {

        public:

            T& items() {
                return items_;
            }

            Context() = default;
            ~Context() = default;

        private:

            T items_;

        };

    }
}