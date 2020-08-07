#pragma once

#include <map>
#include "identifier.h"
#include "serialization/data.h"
#include "unique.h"

#define CONTEXT "__CONTEXT__"

namespace strife {
    namespace common {

        class Contexts {

        public:

            class IContext : public Unique {

            public:

                virtual void apply(Data& data) const = 0;
                virtual void dispose() = 0;

                IContext() = default;
                virtual ~IContext() = default;

            };
        
            template <class T>
            class Context : public IContext {

            public:

                T& items() {
                    return items_;
                }

                Context() = default;
                ~Context() = default;

                void apply(Data& data) const {
                    data[CONTEXT] = strife::common::ToString(id_);
                }

                void dispose() {
                    Contexts().dispose(*this);
                }

            private:

                T items_;

            };

        public:

            IContext& instantiate();
            void dispose(IContext& context);
            IContext& at(const Data& data) const;

            template <class T>
            Context<T>& instantiate() {
                Context<T>* context = new Context<T>();
                const Identifier id = context->id();
                contexts_.insert({id, context});
                return *context;
            }

            template <class T>
            Context<T>& at(const Data& data) const {
                IContext& context = at(data);
                return static_cast<Context<T>&>(context);
            }

        private:

            std::map<const Identifier, IContext* const> contexts_;
            
        };

    }
}