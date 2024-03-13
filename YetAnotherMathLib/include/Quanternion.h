#pragma once

#include "Math/Vector3.h"

namespace YAM
{
    class Quanternion
    {
    private:
        flt scalar;
        Vector3 vector;

        Quanternion()
        : scalar(0) { }
    public:
        Quanternion(flt a, flt i, flt j, flt k) : scalar(a), vector(i, j, k) {}
        Quanternion(flt a, Vector3 vector) : scalar(a), vector(vector) {}

        Quanternion &operator=(Quanternion const &another)
        {
            if (this == *another)
                return *this;

            this->scalar = another.scalar;
            this->vector = another.vector;

            return *this;
        }

        bool operator==(Quanternion const &another)
        {
            if(this->Scalar == another.Scalar && this->Vector == another.Vector){
                return true;
            }

            return false;
        }

        Quanternion operator-()
        {
            Quanternion<T> result;
            result.scalar = -this->scalar;
            result.vector = -this->vector;
            return result;
        }

        Quanternion operator+(Quanternion const &another)
        {
            Quanternion result;
            result.scalar = this->scalar + another.scalar;
            result.vector = this->vector + another.vector;
            return result;
        }

        Quanternion operator-(Quanternion another)
        {
            return *this + (-another);
        }

        void operator+=(Quanternion const &another)
        {
            this = this + another;
        }

        void operator-=(Quanternion const &another)
        {
            this = this - another;
        }

        Quanternion<T> operator*(Quanternion<T> another)
        {
            Quanternion result;
            result.scalar = this->scalar * another.scalar - this->vector.Dot(another.vector);
            result.vector = this->scalar * another.vector + another.scalar * this->vector +
                            this->vector.Cross(another.vector);
            return result;
        }

        Quanternion<T> operator*(double scalar)
        {
            Quanternion result;
            result.scalar = scalar * scalar;
            result.vector = scalar * vector;
            return result;
        }

        friend Quanternion<T> operator*(T scalar, Quanternion<T> Quanternion)
        {
            Quanternion result;
            result.scalar = scalar * Quanternion.scalar;
            result.vector = scalar * Quanternion.vector;
            return result;
        }

        Quanternion<T> operator/(Quanternion<T> another)
        {
            Quanternion<T> result;
            T factor = 1/(another.scalar * another.scalar + another.vector.Dot(another.vector));
            result.scalar = (scalar * another.scalar + vector.Dot(another.vector)) * factor;
            result.vector = factor * (-scalar * another.vector + another.scalar * vector - vector.Cross(another.vector));

            return result;
        }
        
        void operator*=(Quanternion const &another)
        {
            this = this * another;
        }

        void operator/=(Quanternion const &another)
        {
            this = this / another;
        }
        
        static Quanternion<T> GetRotationQuanternion(T Angle, Vector3<T> Axis)
        {
            T factor = std::sin(Angle/2) * (1 / std::sqrt(Axis.x * Axis.x + Axis.y * Axis.y + Axis.z * Axis.z));
            return Quanternion<T>(std::cos(Angle/2), Axis * factor);
        }
        
        Vector3<T> Rotate(Vector3<T> vector)
        {
            return 2. * this->vector.Dot(vector) * this->vector
                     + (scalar * scalar - this->vector.Dot(this->vector)) * vector
                     + 2. * scalar * this->vector.Cross(vector);
        }

        friend std::ostream &operator<<(std::ostream &Os, const Quanternion &Quanternion)
        {
            Os << "(" << Quanternion.scalar << " + " << Quanternion.vector << ")";
            return Os;
        }
    };

} // namespace SG
