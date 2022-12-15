#pragma once

#include "TVector3.h"
#include <cmath>
#include <ostream>

namespace SG {
    class NoIntersectionException : std::exception {
    };

    template<typename T>
    struct TLine {
        TVector3 <T> vector;
        TVector3 <T> point;

    public:
        static TLine<T> FromTwoPoints(TVector3 <T> pointA, TVector3 <T> pointB) {
            TVector3 foundVector = pointB - pointA;
            return {foundVector, pointA};
        }

        friend std::ostream& operator<<(std::ostream& os, const TLine& line) {
            os << line.vector << " + " << line.point << "t";
            return os;
        }
    };

    template<typename T>
    struct TSphere {
        TVector3 <T> center;
        T radius;
    };

    template<typename T>
    struct TSegment {
        TVector3 <T> pointOne;
        TVector3 <T> pointTwo;
        TLine <T> line;

        TSegment(TVector3 <T> start, TVector3 <T> end)
                : pointOne(start), pointTwo(end), line(TLine < T > ::FromTwoPoints(start, end)) {

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

        static TVector3 <T> FindIntersection(TLine<T> one, TLine<T> another) {
            TVector3 < T > deltaPoints = another.point - one.point;

            if (std::abs(deltaPoints.Dot(one.vector.Cross(another.vector))) > 0.001) {
                throw NoIntersectionException();
            }

            T mag2 = one.vector.Cross(another.vector).Length();
            mag2 *= mag2;

            T s = deltaPoints.Cross(another.vector).Dot(one.vector.Cross(another.vector)) / mag2;

            return one.point + one.vector * s;
        }

        static T FindAngle(TLine<T> one, TLine<T> another) {
            return std::acos(one.vector.Normal().Dot(another.vector.Normal()));
        }

        static T FindLinesDistance(TLine<T> one, TLine<T> another) {
            return (another.point - one.point).Cross(another.vector).Dot(one.vector.Cross(another.vector)) /
                   one.vector.Cross(another.vector).Dot((one.vector.Cross(another.vector)));
        }

        static TVector3 <T> FindIntersection(TLine<T> line, TPlane <T> plane) {
            T distance = plane.normalVector.Dot(plane.point) * -1.f;
            T t = -(line.point.Dot(plane.normalVector) + distance) / line.vector.Dot(plane.normalVector);
            return line.point + (plane.normalVector * t);
        }

        static TLine<T> FindIntersection(TPlane <T> planeOne, TPlane <T> planeTwo) {
            TVector3 < T > thirdPlaneNormal = planeOne.normalVector.Cross(planeTwo.normalVector);
            T det = thirdPlaneNormal.SquaredLength();

            if (det == 0.f)
                throw NoIntersectionException();

            TLine<T> result;
            result.point = ((thirdPlaneNormal.Cross(planeTwo.normalVector).Dot(planeOne.point))
                            + (planeOne.normalVector.Cross(thirdPlaneNormal).Dot(planeTwo.point))) / det;
            result.vector = thirdPlaneNormal;
            return result;
        }

        static T FindAngle(TLine<T> line, TPlane <T> plane) {
            return std::asin(line.vector.Normal().Dot(plane.normalVector.Normal()));
        }

        static T FindAngle(TPlane <T> planeOne, TPlane <T> planeTwo) {
            return std::acos(planeOne.normalVector.Normal().Dot(planeTwo.normalVector.Normal()));
        }

        static TVector3 <T> FindIntersection(TSegment <T> SegmentOne, TSegment <T> SegmentTwo) {
            TVector3 < T > result = FindIntersection(SegmentOne.line, SegmentTwo.line);
            if ((SegmentOne.pointTwo - SegmentOne.pointOne).Dot(result - SegmentOne.pointOne) < 0 ||
                (SegmentTwo.pointTwo - SegmentTwo.pointOne).Dot(result - SegmentTwo.pointOne) < 0) {
                throw NoIntersectionException();
            }

            return result;
        }

        static std::vector<TVector3<T>> FindIntersection(TLine<T> line, TSphere<T> sphere) {
            TVector3<T> centerToLineVector = line.point - sphere.center;
            T a = line.vector.Dot(line.vector);
            T b = 2. * centerToLineVector.Dot(line.vector);
            T c = centerToLineVector.Dot(centerToLineVector) - sphere.radius * sphere.radius;
            T delta = b*b - 4*a*c;
            if (delta < 0.f)
                throw NoIntersectionException();

            T solutionOne = (-b - sqrt(delta) / 2. * a);
            T solutionTwo = (-b + sqrt(delta) / 2. * a);

            return {line.point + line.vector * solutionOne, line.point + line.vector * solutionTwo};
        }
    };
}
