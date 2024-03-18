#include "Vector4.h"

#include "Vector3.h"

YAM::Vector4::Vector4(const Vector3& vec3, flt w)
    : x(vec3.x)
      , y(vec3.y)
      , z(vec3.z)
      , w(w) {}
