#pragma once

#include <cxxabi.h>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace strife {
    namespace reflection {
        
        class Type {

        public:

            template <class T>
            static void Register() {
                const Type& type = Type::Of<T>();
            }

            template <class T>
            static const Type& Of() {
                const std::type_index& typeIndex = typeid(T);
                const std::type_info& typeInfo = typeid(T);
                const std::pair<std::map<const std::type_index, const Type>::iterator, bool> pair = Type::Types_.emplace(typeIndex, typeInfo);
                const Type& type = pair.first->second;
                
                bool isRegister = pair.second;
                if (isRegister) {
                    Type::Inverse_.insert({ type.name_, type.index_ });
                }
                
                return type;
            }

            static const Type& Of(std::string name);

            const std::type_index& index() const;
            const std::string& name() const;
            
            Type(const std::type_info& typeInfo);
            ~Type() = default;

            Type& operator=(const Type& type);
            bool operator==(const Type& type) const;
            bool operator<(const Type& type) const;

        private:

            static std::map<const std::type_index, const Type> Types_;
            static std::map<const std::string, const std::type_index> Inverse_;

            int status_;
            std::type_index index_;
            std::string name_;

        };
        
    }
}