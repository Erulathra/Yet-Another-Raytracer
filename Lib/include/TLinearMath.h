#pragma once

#include "TVector3.h"

namespace SG {

    template<typename T>
    struct TLine {
        TVector3<T> vector;
        TVector3<T> point;
    };

    template<typename T>
    class TLinearMath {
    public:

        static TVector3<T> FindIntersection(TLine<T> one, TLine<T> another) {
            TVector3<T> deltaPoints = another.point - one.point;

            if (std::abs(deltaPoints.Dot(one.vector.Cross(another.vector))) > 0.001) {
                throw std::exception();
            }

            T mag2 = one.vector.Cross(another.vector).Length();
            mag2 *= mag2;

            T s = deltaPoints.Cross(another.vector).Dot(one.vector.Cross(another.vector)) / mag2;

            return one.point + one.vector * s;
        }

        static T FindAngle(TLine<T> one, TLine<T> another) {
            return one.vector.Normal().Dot(another.vector.Normal());
        }

        static T Distance(TLine<T> one, TLine<T> another) {
            return (another.point - one.point).Cross(another.vector).Dot(one.vector.Cross(another.vector)) /
                   one.vector.Cross(another.vector).Dot((one.vector.Cross(another.vector)));
        }
    };
}
