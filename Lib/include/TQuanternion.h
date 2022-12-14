#pragma once

#include "TVector3.h"

namespace SG
{
    template <typename T>
    class TQuanternion
    {
    private:
        T scalar;
        TVector3<T> vector;

        TQuanternion() {};
    public:
        TQuanternion(T a, T i, T j, T k)
            : scalar(a), vector(i, j, k) {}

        TQuanternion(T a, TVector3<T> vector)
            : scalar(a), vector(vector) {}

        TQuanternion &operator=(TQuanternion const &another)
        {
            if (this == *another)
                return *this;

            this->scalar = another.scalar;
            this->vector = another.vector;

            return *this;
        }

        bool operator==(TQuanternion const &another)
        {
            if(this->Scalar == another.Scalar && this->Vector == another.Vector){
                return true;
            }

            return false;
        }

        TQuanternion operator-()
        {
            TQuanternion<T> result;
            result.scalar = -this->scalar;
            result.vector = -this->vector;
            return result;
        }

        TQuanternion operator+(TQuanternion const &another)
        {
            TQuanternion result;
            result.scalar = this->scalar + another.scalar;
            result.vector = this->vector + another.vector;
            return result;
        }

        TQuanternion operator-(TQuanternion another)
        {
            return *this + (-another);
        }

        void operator+=(TQuanternion const &another)
        {
            this = this + another;
        }

        void operator-=(TQuanternion const &another)
        {
            this = this - another;
        }

        TQuanternion<T> operator*(TQuanternion<T> another)
        {
            TQuanternion result;
            result.scalar = this->scalar * another.scalar - this->vector.Dot(another.vector);
            result.vector = this->scalar * another.vector + another.scalar * this->vector +
                            this->vector.Cross(another.vector);
            return result;
        }

        TQuanternion<T> operator*(double scalar)
        {
            TQuanternion result;
            result.scalar = scalar * scalar;
            result.vector = scalar * vector;
            return result;
        }

        friend TQuanternion<T> operator*(T scalar, TQuanternion<T> Quanternion)
        {
            TQuanternion result;
            result.scalar = scalar * Quanternion.scalar;
            result.vector = scalar * Quanternion.vector;
            return result;
        }

        TQuanternion<T> operator/(TQuanternion<T> another)
        {
            TQuanternion<T> result;
            T factor = 1/(another.scalar * another.scalar + another.vector.Dot(another.vector));
            result.scalar = (scalar * another.scalar + vector.Dot(another.vector)) * factor;
            result.vector = factor * (-scalar * another.vector + another.scalar * vector - vector.Cross(another.vector));

            return result;
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
            T factor = std::sin(Angle/2) * (1 / std::sqrt(Axis.x * Axis.x + Axis.y * Axis.y + Axis.z * Axis.z));
            return TQuanternion<T>(std::cos(Angle/2), Axis * factor);
        }
        
        TVector3<T> Rotate(TVector3<T> vector)
        {
            return 2. * this->vector.Dot(vector) * this->vector
                     + (scalar * scalar - this->vector.Dot(this->vector)) * vector
                     + 2. * scalar * this->vector.Cross(vector);
        }

        friend std::ostream &operator<<(std::ostream &Os, const TQuanternion &Quanternion)
        {
            Os << "(" << Quanternion.scalar << " + " << Quanternion.vector << ")";
            return Os;
        }
    };

} // namespace SG
