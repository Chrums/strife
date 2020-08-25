#include "strife/math/vector/vector4f.h"

using namespace strife::math;

Vector4f Vector4f::Zero(0.0f, 0.0f, 0.0f, 0.0f);
Vector4f Vector4f::One(1.0f, 1.0f, 1.0f, 0.0f);
Vector4f Vector4f::Left(-1.0f, 0.0f, 0.0f, 0.0f);
Vector4f Vector4f::Right(1.0f, 0.0f, 0.0f, 0.0f);
Vector4f Vector4f::Down(0.0f, -1.0f, 0.0f, 0.0f);
Vector4f Vector4f::Up(0.0f, 1.0f, 0.0f, 0.0f);
Vector4f Vector4f::Backward(0.0f, 0.0f, -1.0f, 0.0f);
Vector4f Vector4f::Forward(0.0f, 0.0f, 1.0f, 0.0f);