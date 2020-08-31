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
            
            static const Type& Of(std::string name);

            template <class T>
            static const Type& Of(const T& object) {
                return Type::Of<T>();
            }

            template <class T>
            static const Type& Of() {
                const std::type_index& typeIndex = typeid(T);
                const std::type_info& typeInfo = typeid(T);
                return Type::Types_.emplace(typeIndex, typeInfo).first->second;
            }

            template <class T>
            static void Register() {
                const Type& type = Type::Of<T>();
                Type::Inverse_.insert({ type.name_, type.index_ });
            }

            template <class T>
            static void Unregister() {
                const Type& type = Type::Of<T>();
                Type::Inverse_.erase(type.name_);
            }

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