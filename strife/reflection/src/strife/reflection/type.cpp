#include "strife/reflection/type.h"

using namespace std;
using namespace strife::reflection;

const Type& Type::Of(string name) {
    const type_index& typeIndex = Type::Inverse_.at(name);
    const Type& type = Type::Types_.at(typeIndex);
    return type;
}

const type_index& Type::index() const {
    return index_;
}

const string& Type::name() const {
    return name_;
}

Type::Type(const type_info& typeInfo)
    : index_(typeInfo)
    , name_(string(abi::__cxa_demangle(typeInfo.name(), 0, 0, &status_))) {
}

Type& Type::operator=(const Type& type) {
    status_ = type.status_;
    index_ = type.index_;
    name_ = type.name_;
    return *this;
}

bool Type::operator==(const Type& type) const {
    return index_ == type.index_;
}

bool Type::operator<(const Type& type) const {
    return index_ < type.index_;
}

map<const type_index, const Type> Type::Types_;
map<const string, const type_index> Type::Inverse_;