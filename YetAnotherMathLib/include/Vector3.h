#pragma once

#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include "Defines.h"

namespace YAM
{
    class Vector3
    {
    public:
        flt x;
        flt y;
        flt z;

        Vector3() : x(0), y(0), z(0) {}

        Vector3(flt x) : x(x), y(x), z(x) {}

        Vector3(flt X, flt Y, flt Z) : x(X), y(Y), z(Z) {}

        double Length() const { return std::sqrt(x * x + y * y + z * z); }

        double SquaredLength() const { return x * x + y * y + z * z; }

        Vector3 Normal() const {
            const double length = this->Length();
            if (length == 0)
                return {0.};

            return *this / length;
        }

        bool IsNear(const Vector3& vector3, flt error) const {
            return std::abs(this->Length() - vector3.Length()) < error;
        }

        flt Dot(Vector3 rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

        [[nodiscard]] flt Angle(Vector3 rhs) const {
            return acos(this->Dot(rhs) / (this->Length() * rhs.Length()));
        }

        [[nodiscard]] Vector3 Cross(Vector3 rhs) const {
            return {this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z,
                               this->x * rhs.y - this->y * rhs.x};
        }

        Vector3& operator=(Vector3 const& another)
        {
            if (this == &another)
            {
                return *this;
            }

            this->x = another.x;
            this->y = another.y;
            this->z = another.z;
            return *this;
        }

        Vector3 operator-() const {
            Vector3 result;
            result.x = -this->x;
            result.y = -this->y;
            result.z = -this->z;
            return result;
        }

        Vector3 operator+(Vector3 const& another) const {
            Vector3 result;
            result.x = this->x + another.x;
            result.y = this->y + another.y;
            result.z = this->z + another.z;
            return result;
        }

        Vector3 operator-(Vector3 const& another) const {
            Vector3 result;
            result.x = this->x - another.x;
            result.y = this->y - another.y;
            result.z = this->z - another.z;
            return result;
        }

        void operator+=(Vector3 const& another) { *this = *this + another; }
        void operator-=(Vector3 const& another) { *this = *this - another; }

        Vector3 operator*(flt const& scalar) const {
            Vector3 result;
            result.x = this->x * scalar;
            result.y = this->y * scalar;
            result.z = this->z * scalar;
            return result;
        }

        friend Vector3 operator*(flt scalar, Vector3 vector)
        {
            return vector * scalar;
        }

        Vector3 operator/(flt const& scalar) const {
            Vector3 result;
            result.x = this->x / scalar;
            result.y = this->y / scalar;
            result.z = this->z / scalar;
            return result;
        }

        void operator*=(flt const& scalar) { *this = *this * scalar; }
        void operator/=(flt const& scalar) { *this = *this / scalar; }
        bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

        bool operator!=(const Vector3& rhs) const { return !(rhs == *this); }
        bool operator<(const Vector3& rhs) const { return this->Length() < rhs.Length(); }

        bool operator>(const Vector3& rhs) const { return rhs < *this; }
        bool operator<=(const Vector3& rhs) const { return !(rhs < *this); }
        bool operator>=(const Vector3& rhs) const { return !(*this < rhs); }

        friend std::ostream& operator<<(std::ostream& Os, const Vector3& vector3)
        {
            Os << "[" << vector3.x << "," << vector3.y << "," << vector3.z << "]";
            return Os;
        }

        std::string str() const {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
    };

} // namespace SG
