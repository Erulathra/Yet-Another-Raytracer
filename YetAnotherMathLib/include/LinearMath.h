#pragma once

#include "Vector3.h"
#include <cmath>
#include <ostream>
#include <vector>


namespace YAM {
    struct Ray {
        Vector3 vector;
        Vector3 point;

    public:
        static Ray FromTwoPoints(const Vector3& pointA, const Vector3& pointB) {
            const Vector3 foundVector = pointB - pointA;
            return {foundVector, pointA};
        }

        friend std::ostream& operator<<(std::ostream& os, const Ray& line) {
            os << line.point << " + " << line.vector << "t";
            return os;
        }
    };

    struct Sphere {
        Vector3 center;
        flt radius;
    };

    struct Segment {
        Vector3 pointOne;
        Vector3 pointTwo;
        Ray line;

        Segment(const Vector3& start, const Vector3& end)
            : pointOne(start)
              , pointTwo(end)
              , line(Ray::FromTwoPoints(start, end)) {
        }
    };

    struct Plane {
        Vector3 normalVector;
        Vector3 point;

        flt a;
        flt b;
        flt c;
        flt d;

        static Plane FromGeneral(flt a, flt b, flt c, flt d) {
            const Vector3 foundNormalVector = {a, b, c};
            Vector3 point;

            if (c != 0) {
                point = {0, 0, -d / c};
            } else if (b != 0) {
                point = {0, -d / b, c};
            }

            return Plane{foundNormalVector, point, a, b, c, d};
        }
    };


    class LinearMath {
    public:
        static bool FindIntersection(const Ray& one, const Ray& another, Vector3& Result) {
            Vector3 deltaPoints = another.point - one.point;

            if (std::abs(deltaPoints.Dot(one.vector.Cross(another.vector))) > 0.001) {
                return false;
            }

            flt mag2 = one.vector.Cross(another.vector).Length();
            mag2 *= mag2;

            const flt s = deltaPoints.Cross(another.vector).Dot(one.vector.Cross(another.vector)) / mag2;

            Result = one.point + one.vector * s;
            return true;
        }

        static flt FindAngle(const Ray& one, const Ray& another) {
            return std::acos(one.vector.Normal().Dot(another.vector.Normal()));
        }

        static flt FindLinesDistance(const Ray& one, const Ray& another) {
            return (another.point - one.point).Cross(another.vector).Dot(one.vector.Cross(another.vector)) /
                   one.vector.Cross(another.vector).Dot((one.vector.Cross(another.vector)));
        }

        static bool FindIntersection(const Ray& line, const Plane& plane, Vector3& result) {
            const flt distance = plane.normalVector.Dot(plane.point) * -1.f;
            const flt t = -(line.point.Dot(plane.normalVector) + distance) / line.vector.Dot(plane.normalVector);
            result = line.point + (line.vector * t);
            return true;
        }

        static bool FindIntersection(const Plane& planeOne, const Plane& planeTwo, Ray& result) {
            result.vector = planeOne.normalVector.Cross(planeTwo.normalVector);
            flt directionLength = result.vector.SquaredLength();

            if (directionLength == 0.f)
                return false;

            result.point = (result.vector.Cross(planeTwo.normalVector) * planeOne.d +
                            planeOne.normalVector.Cross(result.vector) * planeTwo.d) / directionLength;
            return true;
        }

        static flt FindAngle(const Ray& line, const Plane& plane) {
            return std::asin(line.vector.Normal().Dot(plane.normalVector.Normal()));
        }

        static flt FindAngle(const Plane& planeOne, const Plane& planefltwo) {
            return std::acos(planeOne.normalVector.Normal().Dot(planefltwo.normalVector.Normal()));
        }

        static bool FindIntersection(const Segment& SegmentOne, const Segment& SegmentTwo, Vector3& result) {
            if (!FindIntersection(SegmentOne.line, SegmentTwo.line, result)) {
                return false;
            }

            if ((SegmentOne.pointTwo - SegmentOne.pointOne).Dot(result - SegmentOne.pointOne) < 0 ||
                (SegmentTwo.pointTwo - SegmentTwo.pointOne).Dot(result - SegmentTwo.pointOne) < 0) {
                return false;
            }

            return true;
        }

        static bool FindIntersection( const Ray& line, const Sphere& sphere, std::vector<Vector3>& result) {
            const Vector3 centerfltoLineVector = line.point - sphere.center;
            const flt a = line.vector.Dot(line.vector);
            const flt b = 2. * centerfltoLineVector.Dot(line.vector);
            const flt c = centerfltoLineVector.Dot(centerfltoLineVector) - sphere.radius * sphere.radius;
            const flt delta = b * b - 4 * a * c;

            if (delta < 0.f)
                return false;

            const flt solutionOne = (-b - std::sqrt(delta)) / (2. * a);
            const flt solutionfltwo = (-b + std::sqrt(delta)) / (2. * a);

            result = {line.point + line.vector * solutionOne, line.point + line.vector * solutionfltwo};

            return true;
        }
    };
}
