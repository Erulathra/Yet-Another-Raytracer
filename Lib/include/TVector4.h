#ifndef S1NU5GRAPHICS_VECTOR3_H
#define S1NU5GRAPHICS_VECTOR3_H

#include <cmath>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace SG {

    class DivisionByZeroException : std::exception {
    public:
    private:
        [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    template<typename T>
    class TVector4 {
    private:
        T X;
        T Y;
        T Z;
        T W;

    public:
        TVector4() : X(0), Y(0), Z(0), W(0) {};

        TVector4(T X, T Y, T Z, T W) : X(X), Y(Y), Z(Z), W(W) {}

        double Length() { return std::sqrt(X * X + Y * Y + Z * Z + W * W); }

        TVector4 Normal() {
            double Length = this->Length();
            if (Length == 0)
                throw DivisionByZeroException();

            return *this / Length;
        }

        double Dot(TVector4 &rhs) { return X * rhs.X + Y * rhs.Y + Z * rhs.Z; }

        double Angle(TVector4 &rhs) {
            return acos(this->Dot(rhs) / (this->Length() * rhs.Length()));
        }

        TVector4 Cross(TVector4 rhs) {
            return TVector4<T>(this->Y * rhs.Z - this->Z * rhs.Y, this->Z * rhs.X - this->X * rhs.Z,
                               this->X * rhs.Y - this->Y * rhs.X);
        }

        TVector4 &operator=(TVector4 const &Another) {
            if (this == &Another) {
                return *this;
            }

            this->X = Another.X;
            this->Y = Another.Y;
            this->Z = Another.Z;
            this->W = Another.W;
            return *this;
        }

        TVector4 &operator-() {
            this->X = -this->X;
            this->Y = -this->Y;
            this->Z = -this->Z;
            this->W = -this->W;
        }

        TVector4 operator+(TVector4 const &Another) {
            TVector4 Result;
            Result.X = this->X + Another.X;
            Result.Y = this->Y + Another.Y;
            Result.Z = this->Z + Another.Z;
            Result.W = this->W + Another.W;
            return Result;
        }

        TVector4 operator-(TVector4 const &Another) {
            TVector4 Result = *this + (-Another);
            return Result;
        }

        void operator+=(TVector4 const &Another) { this = this + Another; }

        void operator-=(TVector4 const &Another) { this = this - Another; }

        TVector4 operator*(T const &Scalar) {
            TVector4 Result;
            Result.X = this->X * Scalar;
            Result.Y = this->Y * Scalar;
            Result.Z = this->Z * Scalar;
            Result.W = this->W * Scalar;
            return Result;
        }

        TVector4 operator/(T const &Scalar) {
            if (Scalar == 0)
                throw DivisionByZeroException();

            TVector4 Result;
            Result.X = this->X / Scalar;
            Result.Y = this->Y / Scalar;
            Result.Z = this->Z / Scalar;
            Result.W = this->W / Scalar;
            return Result;
        }

        void operator*=(T const &Scalar) { *this = *this * Scalar; }

        void operator/=(T const &Scalar) { *this = *this / Scalar; }

        bool operator==(const TVector4 &Rhs) const {
            return X == Rhs.X && Y == Rhs.Y && Z == Rhs.Z && W = Rhs.W;
        }

        bool operator!=(const TVector4 &Rhs) const { return !(Rhs == *this); }

        bool operator<(const TVector4 &Rhs) const {
            return this->Length() < Rhs.Lenght();
        }

        bool operator>(const TVector4 &Rhs) const { return Rhs < *this; }

        bool operator<=(const TVector4 &Rhs) const { return !(Rhs < *this); }

        bool operator>=(const TVector4 &Rhs) const { return !(*this < Rhs); }

        friend std::ostream &operator<<(std::ostream &Os, const TVector4 &Vector3) {
            Os << "[" << Vector3.X << "," << Vector3.Y << "," << Vector3.Z << "," << Vector3.Z << "]";
            return Os;
        }

        std::string str() {
            std::ostringstream result;
            result << *this;
            return result.str();
        }
    };

} // namespace SG

#endif // S1NU5GRAPHICS_VECTOR3_H
