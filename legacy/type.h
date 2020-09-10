#pragma once

#include <cxxabi.h>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace strife {

    struct Type {

#pragma region Statics

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
            return Type::IndexTypeMap_.emplace(typeIndex, typeInfo).first->second;
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

        inline const std::string name() const;
        inline const std::type_index index() const;

        Type(const std::type_info& typeInfo);
        ~Type() = default;

        Type& operator=(const Type& type);
        bool operator==(const Type& type) const;
        bool operator<(const Type& type) const;

    private:

        int status_;
        std::string name_;
        std::type_index index_;

#pragma endregion

    };

}