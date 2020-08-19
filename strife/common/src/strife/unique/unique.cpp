#include "strife/unique/unique.h"

using namespace std;
using namespace boost::uuids;
using namespace strife::unique;

nil_generator Unique::NilGenerator;
random_generator Unique::RandomGenerator;

Unique Unique::Nil() {
	Identifier identifier = Unique::NilGenerator();
	return Unique(identifier);
}

Unique Unique::Random() {
	Identifier identifier = Unique::RandomGenerator();
	return Unique(identifier);
}
            
const Identifier Unique::id() const {
	return id_;
}

Unique::Unique()
    : id_(Unique::RandomGenerator()) {}

Unique::Unique(const Unique& unique)
    : id_(unique.id_) {}

Unique::Unique(const Identifier& id)
    : id_(id) {}

Unique& Unique::operator=(const Unique& unique) {
	id_ = unique.id_;
	return *this;
}

bool Unique::operator==(const Unique& unique) const {
	return id_ == unique.id_;
};

bool Unique::operator<(const Unique& unique) const {
	return id_ < unique.id_;
}

void Unique::id(const Identifier& id) {
	id_ = id;
}