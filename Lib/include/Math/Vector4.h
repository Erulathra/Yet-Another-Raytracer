#pragma once

#include <cmath>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include "Mat4.h"
#include "Vector3.h"

namespace YAR
{
    class Vector4
    {
    private:
        flt x;
        flt y;
        flt z;
        flt w;

    public:
        Vector4() : x(0), y(0), z(0), w(0){};
        Vector4(flt x, flt y, flt z, flt w) : x(x), y(y), z(z), w(w) {}

        double Length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        Vector4 Normal()
        {
            double length = this->Length();
            if (length < std::numeric_limits<float>::min())
                return {0.};

            return *this / length;
        }

        double Dot(Vector4 &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
        double Angle(Vector4 &rhs) const { return acos(this->Dot(rhs) / (this->Length() * rhs.Length())); }

        Vector4 &operator=(Vector4 const &another) {
            if (this == &another)
            {
                return *this;
            }

            this->x = another.x;
            this->y = another.y;
            this->z = another.z;
            this->w = another.w;
            return *this;
        }

        Vector4 operator-() const {
            Vector4 result;
            result.x = -this->x;
            result.y = -this->y;
            result.z = -this->z;
            result.w = -this->w;
            return result;
        }

        Vector4 operator+(Vector4 const &another) const {
            Vector4 result;
            result.x = this->x + another.x;
            result.y = this->y + another.y;
            result.z = this->z + another.z;
            result.w = this->w + another.w;
            return result;
        }

        Vector4 operator-(Vector4 const &another) const {
            Vector4 result = *this + (-another);
            return result;
        }

        void operator+=(Vector4 const &another) { *this = *this + another; }
        void operator-=(Vector4 const &another) { *this = *this - another; }

        Vector4 operator*(flt const &scalar) const {
            Vector4 result;
            result.x = this->x * scalar;
            result.y = this->y * scalar;
            result.z = this->z * scalar;
            result.w = this->w * scalar;
            return result;
        }

        Vector4 operator*(Mat4 matrix)
        {
            Vector4 result;
            result.x = x * matrix[{0, 0}] + y * matrix[{0, 1}] + z * matrix[{0, 2}] + w * matrix[{0, 3}];
            result.y = x * matrix[{1, 0}] + y * matrix[{1, 1}] + z * matrix[{1, 2}] + w * matrix[{1, 3}];
            result.z = x * matrix[{2, 0}] + y * matrix[{2, 1}] + z * matrix[{2, 2}] + w * matrix[{2, 3}];
            result.w = x * matrix[{3, 0}] + y * matrix[{3, 1}] + z * matrix[{3, 2}] + w * matrix[{3, 3}];

            return result;
        }

        Vector4 operator/(flt const &scalar)
        {
            Vector4 result;
            result.x = this->x / scalar;
            result.y = this->y / scalar;
            result.z = this->z / scalar;
            result.w = this->w / scalar;
            return result;
        }

        void operator*=(flt const &scalar) { *this = *this * scalar; }
        void operator/=(flt const &scalar) { *this = *this / scalar; }
        bool operator==(const Vector4 &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w = rhs.w; }
        operator!=(const Vector4 &rhs) const { return !(rhs == *this); }

        friend std::ostream &operator<<(std::ostream &os, const Vector4 &vector4)
        {
            os << "[" << vector4.x << "," << vector4.y << "," << vector4.z << "," << vector4.w << "]";
            return os;
        }

        std::string str() const {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
    };

} // namespace SG
