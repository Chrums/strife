#include "unique.h"

using namespace std;
using namespace boost::uuids;
using namespace strife::common;

nil_generator Unique::NilGenerator;
random_generator Unique::RandomGenerator;

Unique Unique::Nil() {
	uuid id = Unique::NilGenerator();
	return Unique(id);
}

Unique Unique::Random() {
	uuid id = Unique::RandomGenerator();
	return Unique(id);
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