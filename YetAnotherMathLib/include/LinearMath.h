#pragma once

#include "Vector3.h"
#include <cmath>
#include <ostream>
#include <vector>
#include <cstdint>


namespace YAM{
    struct Ray {
        Vector3 direction;
        Vector3 point;

    public:
        Ray(const Vector3& direction, const Vector3& point)
            : direction(direction),
              point(point) {}

        static Ray FromTwoPoints(const Vector3& pointA, const Vector3& pointB) {
            const Vector3 foundVector = pointB - pointA;
            return {foundVector.Normal(), pointA};
        }

        friend std::ostream& operator<<(std::ostream& os, const Ray& line) {
            os << line.point << " + " << line.direction << "t";
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
              , line(Ray::FromTwoPoints(start, end)) {}
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
            }
            else if (b != 0) {
                point = {0, -d / b, c};
            }

            return Plane{foundNormalVector, point, a, b, c, d};
        }
    };

    struct Triangle {
        Vector3 posA;
        Vector3 posB;
        Vector3 posC;
        
        Vector3 norA;
        Vector3 norB;
        Vector3 norC;

        Triangle(
            const Vector3& posA, const Vector3& posB, const Vector3& posC,
            const Vector3& norA, const Vector3& norB, const Vector3& norC)
            : posA(posA)
              , posB(posB)
              , posC(posC)
              , norA(norA)
              , norB(norB)
              , norC(norC)
        {}
    };

    union Color {
        uint32_t hex;
        uint8_t bytes[4];

        static Color FromVector(Vector3 vector3) {
            Color result{};
            
            result.bytes[3] = 255;
            result.bytes[2] = 255.f * vector3.x;
            result.bytes[1] = 255.f * vector3.y;
            result.bytes[0] = 255.f * vector3.z;

            return result;
        }
    };

    struct HitInfo {
        Vector3 hitPoint;
        Vector3 normal;
        flt distance;
        uint32_t color;
    };

    class LinearMath {
    public:
        static bool FindIntersection(const Ray& one, const Ray& another, Vector3& Result) {
            Vector3 deltaPoints = another.point - one.point;

            if (std::abs(deltaPoints.Dot(one.direction.Cross(another.direction))) > 0.001) {
                return false;
            }

            flt mag2 = one.direction.Cross(another.direction).Length();
            mag2 *= mag2;

            const flt s = deltaPoints.Cross(another.direction).Dot(one.direction.Cross(another.direction)) / mag2;

            Result = one.point + one.direction * s;
            return true;
        }

        static flt FindAngle(const Ray& one, const Ray& another) {
            return std::acos(one.direction.Normal().Dot(another.direction.Normal()));
        }

        static flt FindLinesDistance(const Ray& one, const Ray& another) {
            return (another.point - one.point).Cross(another.direction).Dot(one.direction.Cross(another.direction)) /
                one.direction.Cross(another.direction).Dot((one.direction.Cross(another.direction)));
        }

        static bool FindIntersection(const Ray& line, const Plane& plane, Vector3& result) {
            const flt distance = plane.normalVector.Dot(plane.point) * -1.f;
            const flt t = -(line.point.Dot(plane.normalVector) + distance) / line.direction.Dot(plane.normalVector);
            result = line.point + (line.direction * t);
            return true;
        }

        static bool FindIntersection(const Plane& planeOne, const Plane& planeTwo, Ray& result) {
            result.direction = planeOne.normalVector.Cross(planeTwo.normalVector);
            flt directionLength = result.direction.SquaredLength();

            if (directionLength == 0.f)
                return false;

            result.point = (result.direction.Cross(planeTwo.normalVector) * planeOne.d +
                planeOne.normalVector.Cross(result.direction) * planeTwo.d) / directionLength;
            return true;
        }

        static flt FindAngle(const Ray& ray, const Plane& plane) {
            return std::asin(ray.direction.Normal().Dot(plane.normalVector.Normal()));
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

        static bool FindIntersection(const Ray& ray, const Sphere& sphere, std::vector<Vector3>& result) {
            const Vector3 centerToRayVector = ray.point - sphere.center;
            const flt a = ray.direction.Dot(ray.direction);
            const flt b = 2. * centerToRayVector.Dot(ray.direction);
            const flt c = centerToRayVector.Dot(centerToRayVector) - sphere.radius * sphere.radius;
            const flt delta = b * b - 4 * a * c;

            if (delta < 0.f)
                return false;

            const flt solutionOne = (-b - std::sqrt(delta)) / (2. * a);
            const flt solutionfltwo = (-b + std::sqrt(delta)) / (2. * a);

            result = {ray.point + ray.direction * solutionOne, ray.point + ray.direction * solutionfltwo};

            return true;
        }

        static bool FindIntersection(const Ray& ray, const Triangle& tri, HitInfo& hitInfo) {
            Vector3 edgeAB = tri.posB - tri.posA;
            Vector3 edgeAC = tri.posC - tri.posA;

            Vector3 triangleNormal = Vector3::Cross(edgeAB, edgeAC);

            Vector3 aRayPoint = ray.point - tri.posA;
            Vector3 daRayPoint = Vector3::Cross(aRayPoint, ray.direction);

            flt det = -Vector3::Dot(ray.direction, triangleNormal);
            if (-det < SmallNumber)
                return false;
            
            flt invDet = 1 / det;

            // Calculate distance to triangle and baricentric cooridinates
            flt distance = Vector3::Dot(aRayPoint, triangleNormal) * invDet;
            if (distance < SmallNumber)
                return false;
            
            flt barU = Vector3::Dot(edgeAC, daRayPoint) * invDet;
            flt barV = -Vector3::Dot(edgeAB, daRayPoint) * invDet;
            flt barW = 1 - barU - barV;

            if (barU >= 0.f && barV >= 0.f && barW >= 0.f) {
                hitInfo.hitPoint = ray.point + ray.direction * distance;
                hitInfo.distance = distance;
                hitInfo.normal = (tri.norA * barW + tri.norB * barU + tri.norC * barV).Normal();

                const Vector3 lightDir =  {-1.f, 1.f, 1.f};
                const Color color = Color::FromVector(Vector3{1.f} * Vector3::Dot(hitInfo.normal, lightDir.Normal()));
                hitInfo.color = color.hex;

                return true;
            }

            return false;
        }
    };
}
