#pragma once

#include <cxxabi.h>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace strife {

    class Type {

#pragma region Statics

    public:

        static const Type& Of(std::string name);

        template <class Derived>
        static const bool Is(const Type& type, const Derived& object) {
            return type.info() == typeid(object);
        }

        template <class T>
        static const Type& Of(const T& object) {
            return Type::Of<T>();
        }

        template <class T>
        static const Type& Of() {
            const std::type_index& typeIndex = typeid(T);
            const std::type_info& typeInfo = typeid(T);
            return Type::IndexTypeMap_.emplace(typeIndex, typeInfo).first->second;
        }

        template <class Base, class Derived>
        static const bool Is(const Derived& object) {
            return typeid(Base) == typeid(object);
        }

        template <class T>
        static void Index() {
            const Type& type = Type::Of<T>();
            Type::NameIndexMap_.insert({ type.name_, type.index_ });
        }

        template <class T>
        static void Deindex() {
            const Type& type = Type::Of<T>();
            Type::NameIndexMap_.erase(type.name_);
        }

    private:

        static std::map<const std::type_index, const Type> IndexTypeMap_;
        static std::map<const std::string, const std::type_index> NameIndexMap_;

#pragma endregion

#pragma region Non-Static

    public:

        const std::string& name() const;
        const std::type_info& info() const;
        const std::type_index& index() const;

        Type(const std::type_info& typeInfo);
        ~Type() = default;

        bool operator==(const Type& type) const;
        bool operator<(const Type& type) const;

        template <class T>
        const bool is(const T& object) const {
            return info_ == typeid(object);
        }

    private:

        int status_;
        const std::string name_;
        const std::type_info& info_;
        const std::type_index index_;

#pragma endregion

    };

}