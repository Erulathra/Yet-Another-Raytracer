#pragma once

#include <cmath>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

#include "Defines.h"

namespace YAM{
    class Vector3;
    
    class Vector4 {
    private:
        flt x;
        flt y;
        flt z;
        flt w;

    public:
        Vector4() : x(0), y(0), z(0), w(0) {};
        explicit Vector4(flt x) : x(x), y(x), z(x), w(x) {};
        Vector4(const Vector3& vec3, flt w);
        Vector4(flt x, flt y, flt z, flt w) : x(x), y(y), z(z), w(w) {}

        flt Length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        Vector4 Normal() const {
            double length = this->Length();
            if (length < std::numeric_limits<float>::min())
                return Vector4{0.};

            return *this / length;
        }

        flt Dot(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
        static flt Dot(const Vector4& a, Vector4& b) { return a.Dot(b); }

        flt Angle(Vector4& rhs) const { return acos(this->Dot(rhs) / (this->Length() * rhs.Length())); }

        Vector4& operator=(Vector4 const& another) {
            if (this == &another) {
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

        Vector4 operator+(Vector4 const& another) const {
            Vector4 result;
            result.x = this->x + another.x;
            result.y = this->y + another.y;
            result.z = this->z + another.z;
            result.w = this->w + another.w;
            return result;
        }

        flt operator[] (const uint8_t index) const {
            const flt values[] = {x, y, z, w};
            return values[index];
        }
        
        flt& operator[] (const uint8_t index) {
            flt* values[] = {&x, &y, &z, &w};
            return *values[index];
        }

        Vector4 operator-(Vector4 const& another) const {
            Vector4 result = *this + (-another);
            return result;
        }

        void operator+=(Vector4 const& another) { *this = *this + another; }
        void operator-=(Vector4 const& another) { *this = *this - another; }

        Vector4 operator*(flt const& scalar) const {
            Vector4 result;
            result.x = this->x * scalar;
            result.y = this->y * scalar;
            result.z = this->z * scalar;
            result.w = this->w * scalar;
            return result;
        }

        Vector4 operator/(flt const& scalar) const {
            Vector4 result;
            result.x = this->x / scalar;
            result.y = this->y / scalar;
            result.z = this->z / scalar;
            result.w = this->w / scalar;
            return result;
        }

        void operator*=(flt const& scalar) { *this = *this * scalar; }
        void operator/=(flt const& scalar) { *this = *this / scalar; }
        bool operator==(const Vector4& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
        bool operator!=(const Vector4& rhs) const { return !(rhs == *this); }

        friend std::ostream& operator<<(std::ostream& os, const Vector4& vector4) {
            os << "[" << vector4.x << "," << vector4.y << "," << vector4.z << "," << vector4.w << "]";
            return os;
        }

        std::string str() const {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
        
        friend class Mat4;
        friend class Vector3;
    };
} // namespace SG
