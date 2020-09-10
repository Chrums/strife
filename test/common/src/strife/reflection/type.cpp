#include "strife/reflection/type.h"

using namespace std;
using namespace strife;

#pragma region Static

const Type& Type::Of(string name) {
    const type_index& typeIndex = Type::NameIndexMap_.at(name);
    return Type::IndexTypeMap_.at(typeIndex);
}

map<const type_index, const Type> Type::IndexTypeMap_;
map<const string, const type_index> Type::NameIndexMap_;

#pragma endregion

#pragma region Non-Static

const string& Type::name() const {
    return name_;
}

const type_info& Type::info() const {
    return info_;
}

const type_index& Type::index() const {
    return index_;
}

Type::Type(const type_info& typeInfo)
    : name_(string(abi::__cxa_demangle(typeInfo.name(), 0, 0, &status_)))
    , info_(typeInfo)
    , index_(typeInfo) {}

bool Type::operator==(const Type& type) const {
    return info_ == type.info_;
}

bool Type::operator<(const Type& type) const {
    return index_ < type.index_;
}

#pragma endregion