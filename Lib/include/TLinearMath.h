#pragma once

#include "TVector3.h"

namespace SG {

    template<typename T>
    struct TLine {
        TVector3<T> vector;
        TVector3<T> point;

        static TLine<T> FromTwoPoints(TVector3<T> pointA, TVector3<T> pointB) {
            TVector3 foundVector = pointB - pointA;
            return {foundVector, pointA};
        }
    };

    template<typename T>
    struct TPlane {
        TVector3<T> normalVector;
        TVector3<T> point;

        static TPlane<T> FromGeneral(T a, T b, T c, T w) {
            TVector3<T> foundNormalVector = {a, b, c};
            TVector3<T> point;

            if (c != 0) {
                point = {0, 0, -w / c};
            } else if (b != 0) {
                point = {0, -w / b, c};
            }

            return TPlane{foundNormalVector, point};
        }
    };


    template<typename T>
    class TLinearMath {
    public:

        static TVector3 <T> FindIntersection(TLine <T> one, TLine <T> another) {
            TVector3 < T > deltaPoints = another.point - one.point;

            if (std::abs(deltaPoints.Dot(one.vector.Cross(another.vector))) > 0.001) {
                throw std::exception();
            }

            T mag2 = one.vector.Cross(another.vector).Length();
            mag2 *= mag2;

            T s = deltaPoints.Cross(another.vector).Dot(one.vector.Cross(another.vector)) / mag2;

            return one.point + one.vector * s;
        }

        static T FindAngle(TLine <T> one, TLine <T> another) {
            return one.vector.Normal().Dot(another.vector.Normal());
        }

        static T FindLinesDistance(TLine <T> one, TLine <T> another) {
            return (another.point - one.point).Cross(another.vector).Dot(one.vector.Cross(another.vector)) /
                   one.vector.Cross(another.vector).Dot((one.vector.Cross(another.vector)));
        }

        static TVector3 <T> FindIntersection(TLine <T> line, TPlane<T> plane) {
            T distance = plane.normalVector.Dot(plane.point) * -1.f;
            T t = -(line.point.Dot(plane.normalVector) + distance) / line.vector.Dot(plane.normalVector);
            return line.point + (plane.normalVector * t);
        }
    };
}
