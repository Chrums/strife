#pragma once

#include <map>
#include "unique.h"
#include "strife/serialization/data.h"

namespace strife {
    namespace serialization {

        class IContext : public common::Unique {

        public:

            static void Require(Data& data);

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