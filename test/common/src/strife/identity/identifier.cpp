#include "strife/identity/identifier.h"

using namespace std;
using namespace boost;
using namespace strife;

#pragma region Static

Identifier Identifier::Nil() {
    const uuids::uuid uuid = Identifier::NilGenerator();
    return Identifier(uuid);
}

Identifier Identifier::Random() {
    const uuids::uuid uuid = Identifier::RandomGenerator();
    return Identifier(uuid);
}

uuids::nil_generator Identifier::NilGenerator;
uuids::random_generator Identifier::RandomGenerator;

#pragma endregion

#pragma region Non-Static

Identifier::Identifier()
    : uuid_(Identifier::NilGenerator()) {}

Identifier::Identifier(const Identifier& identifier)
    : uuid_(identifier.uuid_) {}

Identifier& Identifier::operator=(const Identifier& identifier) {
    uuid_ = identifier.uuid_;
    return *this;
}

bool Identifier::operator==(const Identifier& identifier) const {
    return uuid_ == identifier.uuid_;
}

bool Identifier::operator<(const Identifier& identifier) const {
    return uuid_ < identifier.uuid_;
}

Identifier& Identifier::operator=(const string& value) {
    uuid_ = lexical_cast<uuids::uuid>(value);
    return *this;
}

Identifier::operator std::string() const {
    return lexical_cast<string>(uuid_);
}

Identifier::Identifier(const uuids::uuid& uuid)
    : uuid_(uuid) {}

#pragma endregion