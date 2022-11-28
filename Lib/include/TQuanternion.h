#pragma once

#include "TVector3.h"

namespace SG
{
    template <typename T>
    class TQuanternion
    {
    private:
        T Scalar;
        TVector3<T> Vector;

    public:
        TQuanternion(T a, T i, T j, T k)
            : Scalar(a), Vector(i, j, k) {}

        TQuanternion(T a, TVector3<T> Vector)
            : Scalar(a), Vector(Vector) {}

        TQuanternion operator=(TQuanternion const &another)
        {
            if (this == *another)
                return *this;

            this->Scalar = another.Scalar;
            this->Vector = another.Vector;

            return *this;
        }

        TQuanternion &operator-()
        {
            this->Scalar = -this->Scalar;
            this->Vector = -this->Vector;
        }

        TQuanternion operator+(TQuanternion const &another)
        {
            TQuanternion Result;
            Result.Scalar = this->Scalar + another.Scalar;
            Result.Vector = this->Vector + another.Vector;
            return Result;
        }

        TQuanternion operator-(TQuanternion const &another)
        {
            TQuanternion Result = *this + (-another);
            return Result;
        }

        void operator+=(TQuanternion const &another)
        {
            this = this + another;
        }

        void operator-=(TQuanternion const &another)
        {
            this = this - another;
        }

        TQuanternion<T> operator*(TQuanternion<T> const &another)
        {
            TQuanternion Result;
            Result.Scalar = this->Scalar * another.Scalar - this->Vector.dot(another.Vector);
            Result.Vector = this->Scalar * another.Vector + another.Scalar * this->Vector +
                            this->Vector.Cross(another.Vector);
            return Result;
        }

        TQuanternion<T> operator/(TQuanternion<T> const &another)
        {
            T factor = 1/(std::pow(another.Scalar, 2), another.Vector.Dot(another.Vector));

            return this * (factor * another);
        }
        
        void operator*=(TQuanternion const &another)
        {
            this = this * another;
        }

        void operator/=(TQuanternion const &another)
        {
            this = this / another;
        }
        
        static TQuanternion<T> GetRotationQuanternion(T Angle, TVector3<T> Axis)
        {
            T factor = std::sin(Angle/2) * (1 / std::sqrt(Axis.X * Axis.X + Axis.Y * Axis.Y + Axis.Z * Axis.Z));
            return TQuanternion<T>(std::cos(Angle/2), Axis * factor);
        }
        
        TVector3<T> Rotate(TVector3<T> vector)
        {

            return 2. * this->Vector.Dot(vector) * this->Vector
                     + (Scalar * Scalar - this->Vector.Dot(this->Vector)) * vector
                     + 2. * Scalar * this->Vector.Cross(vector);
        }

        friend std::ostream &operator<<(std::ostream &Os, const TQuanternion &Quanternion)
        {
            Os << "(" << Quanternion.Scalar << " + " << Quanternion.Vector << ")";
            return Os;
        }
    };

} // namespace SG
