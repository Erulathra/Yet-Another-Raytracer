#pragma once

#include <cmath>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace SG
{

    class DivisionByZeroException : std::exception
    {
    public:
    private:
        [[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    template<typename T>
    class TVector3
    {
    public:
        T X;
        T Y;
        T Z;

        TVector3() : X(0), Y(0), Z(0) {}

        TVector3(T x) : X(x), Y(x), Z(x) {}

        TVector3(T X, T Y, T Z) : X(X), Y(Y), Z(Z) {}

        double Length()
        { return std::sqrt(X * X + Y * Y + Z * Z); }

        TVector3 Normal()
        {
            double Length = this->Length();
            if (Length == 0)
                throw DivisionByZeroException();

            return *this / Length;
        }

        double Dot(TVector3& rhs)
        { return X * rhs.X + Y * rhs.Y + Z * rhs.Z; }

        double Angle(TVector3& rhs)
        {
            return acos(this->Dot(rhs) / (this->Length() * rhs.Length()));
        }

        TVector3 Cross(TVector3 rhs)
        {
            return TVector3<T>(this->Y * rhs.Z - this->Z * rhs.Y, this->Z * rhs.X - this->X * rhs.Z,
                               this->X * rhs.Y - this->Y * rhs.X);
        }

        TVector3& operator=(TVector3 const& Another)
        {
            if (this == &Another)
            {
                return *this;
            }

            this->X = Another.X;
            this->Y = Another.Y;
            this->Z = Another.Z;
            return *this;
        }

        TVector3& operator-()
        {
            this->X = -this->X;
            this->Y = -this->Y;
            this->Z = -this->Z;
        }

        TVector3 operator+(TVector3 const& Another)
        {
            TVector3 Result;
            Result.X = this->X + Another.X;
            Result.Y = this->Y + Another.Y;
            Result.Z = this->Z + Another.Z;
            return Result;
        }

        TVector3 operator-(TVector3 const& Another)
        {
            TVector3 Result;
            Result.X = this->X - Another.X;
            Result.Y = this->Y - Another.Y;
            Result.Z = this->Z - Another.Z;
            return Result;
        }

        void operator+=(TVector3 const& Another)
        { this = this + Another; }

        void operator-=(TVector3 const& Another)
        { this = this - Another; }

        TVector3 operator*(T const& Scalar)
        {
            TVector3 Result;
            Result.X = this->X * Scalar;
            Result.Y = this->Y * Scalar;
            Result.Z = this->Z * Scalar;
            return Result;
        }
        
        friend TVector3 operator*(T Scalar, TVector3<T> Vector)
        {
            return Vector * Scalar;
        }

        TVector3 operator/(T const& Scalar)
        {
            if (Scalar == 0)
                throw DivisionByZeroException();

            TVector3 Result;
            Result.X = this->X / Scalar;
            Result.Y = this->Y / Scalar;
            Result.Z = this->Z / Scalar;
            return Result;
        }

        void operator*=(T const& Scalar)
        { *this = *this * Scalar; }

        void operator/=(T const& Scalar)
        { *this = *this / Scalar; }

        bool operator==(const TVector3& Rhs) const
        {
            return X == Rhs.X && Y == Rhs.Y && Z == Rhs.Z;
        }

        bool operator!=(const TVector3& Rhs) const
        { return !(Rhs == *this); }

        bool operator<(const TVector3& Rhs) const
        {
            return this->Length() < Rhs.Lenght();
        }

        bool operator>(const TVector3& Rhs) const
        { return Rhs < *this; }

        bool operator<=(const TVector3& Rhs) const
        { return !(Rhs < *this); }

        bool operator>=(const TVector3& Rhs) const
        { return !(*this < Rhs); }

        friend std::ostream& operator<<(std::ostream& Os, const TVector3& Vector3)
        {
            Os << "[" << Vector3.X << "," << Vector3.Y << "," << Vector3.Z << "]";
            return Os;
        }

        std::string str()
        {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
    };

} // namespace SG
