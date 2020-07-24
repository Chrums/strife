#include "unique.h"

using namespace strife::common;

boost::uuids::nil_generator Unique::NilGenerator;
boost::uuids::random_generator Unique::RandomGenerator;

Unique Unique::Nil() {
	return Unique(NilGenerator());
}

Unique Unique::Random() {
	return Unique(RandomGenerator());
}

Unique::Unique()
    : id(Unique::RandomGenerator()) {}

Unique::Unique(const Unique& unique)
    : id(unique.id) {}

Unique::Unique(const Identifier id)
    : id(id) {}

bool Unique::operator==(const Unique& unique) const {
	return id == unique.id;
};

bool Unique::operator<(const Unique& unique) const {
	return id < unique.id;
}