#include "strife/math/vector/vector4i.h"

using namespace strife::math;

Vector4i Vector4i::Zero(0, 0, 0, 0);
Vector4i Vector4i::One(1, 1, 1, 0);
Vector4i Vector4i::Left(-1, 0, 0, 0);
Vector4i Vector4i::Right(1, 0, 0, 0);
Vector4i Vector4i::Down(0, -1, 0, 0);
Vector4i Vector4i::Up(0, 1, 0, 0);
Vector4i Vector4i::Backward(0, 0, -1, 0);
Vector4i Vector4i::Forward(0, 0, 1, 0);