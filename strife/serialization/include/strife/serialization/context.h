#pragma once

#include <map>
#include "strife/serialization/data.h"
#include "strife/unique/unique.h"

namespace strife {
    namespace serialization {

        class IContext : public unique::Unique {

        public:

            const Data data;

            void dispose();

        protected:

            IContext(const Data& data);
            ~IContext() = default;

        private:

            const Data apply(const Data& data) const;

        };

        template <class T>
        class Context : public IContext {

        public:

            const T& value() const {
                return value_;
            }

            T& value() {
                return value_;
            }

            Context(const Data& data)
                : IContext(data) {}
            ~Context() = default;

        private:

            T value_;

        };

    }
}