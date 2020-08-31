#pragma once

#include <map>
#include <string>
#include "strife/serialization/data.h"
#include "strife/unique/unique.h"

#define ITEM_INDEX "__ITEM__"

namespace strife {
    namespace serialization {

        class Context : public unique::Unique {

        public:

            static void Require(Data& data, std::string index);

            const Data data;

            Context(const Data& data);
            ~Context();

            void dispose();

            template <class T>
            T& resolve(const Data& data) {
                std::string index = data[ITEM_INDEX].get<std::string>();

                std::map<const std::string, void* const>::iterator iterator = items_.find(index);
                if (iterator == items_.end()) {
                    int size = sizeof(T);
                    void* const block = malloc(size);

                    T* const item = new (block) T;

                    items_.insert({index, item});
                }
                
                void* const item = items_.at(index);
                return *static_cast<T* const>(item);
            }

        private:
            
            std::map<const std::string, void* const> items_;
            
            const Data apply(const Data& data) const;

        };

    }
}