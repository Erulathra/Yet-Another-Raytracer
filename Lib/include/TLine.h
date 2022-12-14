#pragma once

#include "TVector3.h"

namespace SG {

    class ParallelLinesException : std::exception {
    };

    template<typename T>
    class TLine {
    private:
        TVector3<T> vector;
        TVector3<T> point;
    public:
        TLine(const TVector3<T> &vector, const TVector3<T> &point) : vector(vector), point(point) {}

        TVector3<T> FindIntersection(TLine<T> another) {
            TVector3<T> deltaPoints = another.point - point;

            if (std::abs(deltaPoints.Dot(vector.Cross(another.vector))) > 0.001) {
                throw ParallelLinesException();
            }

            T mag2 = vector.Cross(another.vector).Length();
            mag2 *= mag2;

            T s = deltaPoints.Cross(another.vector).Dot(vector.Cross(another.vector)) / mag2;

            return point + vector * s;
        }

        T Distance(TLine<T> another) {
            return (another.point - point).Cross(another.vector).Dot(vector.Cross(another.vector)) /
                   vector.Cross(another.vector).Dot((vector.Cross(another.vector)));
        }
    };
}
