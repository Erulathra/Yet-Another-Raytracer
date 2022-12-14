#pragma once

#include <cmath>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include "TMat4.h"
#include "TVector3.h"

namespace SG
{
    template <typename T>
    class TVector4
    {
    private:
        T x;
        T y;
        T z;
        T w;

    public:
        TVector4() : x(0), y(0), z(0), w(0){};

        TVector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        double Length() { return std::sqrt(x * x + y * y + z * z + w * w); }

        TVector4 Normal()
        {
            double length = this->Length();
            if (length == 0)
                throw DivisionByZeroException();

            return *this / length;
        }

        double Dot(TVector4 &rhs) { return x * rhs.x + y * rhs.y + z * rhs.z; }

        double Angle(TVector4 &rhs)
        {
            return acos(this->Dot(rhs) / (this->Length() * rhs.Length()));
        }

        TVector4 Cross(TVector4 rhs)
        {
            return TVector4<T>(this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z,
                               this->x * rhs.y - this->y * rhs.x);
        }

        TVector4 &operator=(TVector4 const &another)
        {
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

        TVector4 operator-()
        {
            TVector4<T> result;
            result.x = -this->x;
            result.y = -this->y;
            result.z = -this->z;
            result.w = -this->w;
            return result;
        }

        TVector4 operator+(TVector4 const &another)
        {
            TVector4 result;
            result.x = this->x + another.x;
            result.y = this->y + another.y;
            result.z = this->z + another.z;
            result.w = this->w + another.w;
            return result;
        }

        TVector4 operator-(TVector4 const &another)
        {
            TVector4 result = *this + (-another);
            return result;
        }

        void operator+=(TVector4 const &another) { this = this + another; }

        void operator-=(TVector4 const &another) { this = this - another; }

        TVector4<T> operator*(T const &scalar)
        {
            TVector4<T> result;
            result.x = this->x * scalar;
            result.y = this->y * scalar;
            result.z = this->z * scalar;
            result.w = this->w * scalar;
            return result;
        }

        TVector4<T> operator*(TMat4<T> matrix)
        {
            TVector4<T> result;
            result.x = x * matrix[{0, 0}] + y * matrix[{0, 1}] + z * matrix[{0, 2}] + w * matrix[{0, 3}];
            result.y = x * matrix[{1, 0}] + y * matrix[{1, 1}] + z * matrix[{1, 2}] + w * matrix[{1, 3}];
            result.z = x * matrix[{2, 0}] + y * matrix[{2, 1}] + z * matrix[{2, 2}] + w * matrix[{2, 3}];
            result.w = x * matrix[{3, 0}] + y * matrix[{3, 1}] + z * matrix[{3, 2}] + w * matrix[{3, 3}];

            return result;
        }

        TVector4<T> operator/(T const &scalar)
        {
            if (scalar == 0)
                throw DivisionByZeroException();

            TVector4 result;
            result.x = this->x / scalar;
            result.y = this->y / scalar;
            result.z = this->z / scalar;
            result.w = this->w / scalar;
            return result;
        }

        void operator*=(T const &scalar) { *this = *this * scalar; }

        void operator/=(T const &scalar) { *this = *this / scalar; }

        bool operator==(const TVector4 &rhs) const
        {
            return x == rhs.x && y == rhs.y && z == rhs.z && w = rhs.w;
        }

        bool operator!=(const TVector4 &rhs) const { return !(rhs == *this); }

        bool operator<(const TVector4 &rhs) const
        {
            return this->Length() < rhs.Lenght();
        }

        bool operator>(const TVector4 &rhs) const { return rhs < *this; }

        bool operator<=(const TVector4 &rhs) const { return !(rhs < *this); }

        bool operator>=(const TVector4 &rhs) const { return !(*this < rhs); }

        friend std::ostream &operator<<(std::ostream &os, const TVector4 &vector4)
        {
            os << "[" << vector4.x << "," << vector4.y << "," << vector4.z << "," << vector4.w << "]";
            return os;
        }

        std::string str()
        {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
    };

} // namespace SG
