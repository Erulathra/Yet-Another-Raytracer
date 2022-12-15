#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TQuanternion.h"
#include "TLinearMath.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TLine<double> lineOne{{3, 1, 5}, {-2, 4, 0}};
    SG::TLine<double> lineTwo{{1, -5, 3}, {-2, 4, 0}};
    SG::TLine<double> lineThree{{3, -1, 2}, {-2, 2, -1}};

    SG::TPlane<double> planeOne = SG::TPlane<double>::FromGeneral(2, 3, 3, -8);

    SG::TPlane<double> planeTwo = SG::TPlane<double>::FromGeneral(2, -1, 1, -8);
    SG::TPlane<double> planeThree = SG::TPlane<double>::FromGeneral(4, 3, 1, 14);

    std::cout << "Zad 1.: " << SG::TLinearMath<double>::FindIntersection(lineOne, lineTwo) << std::endl;
    std::cout << "Zad 2.: " << SG::TLinearMath<double>::FindAngle(lineOne, lineTwo) << std::endl;
    std::cout << "Zad 3.: " << SG::TLinearMath<double>::FindIntersection(lineThree, planeOne) << std::endl;
    std::cout << "Zad 4.: " << SG::TLinearMath<double>::FindAngle(lineThree, planeOne) << std::endl;
    SG::TLine result = SG::TLinearMath<double>::FindIntersection(planeTwo, planeThree);
    std::cout << "Zad 5.: " << result << std::endl;
    std::cout << "Zad 6.: " << SG::TLinearMath<double>::FindAngle(planeTwo, planeThree) << std::endl;

    SG::TSegment<double> segmentOne({5, 5, 4}, {10, 10, 6});
    SG::TSegment<double> segmentTwo({5, 5, 5}, {10, 10, 3});
    std::cout << "Zad 7.: " << SG::TLinearMath<double>::FindIntersection(segmentOne, segmentTwo) << std::endl;

    SG::TLine<double> lineX = SG::TLine<double>::FromTwoPoints({3, -1, -2}, {5, 3, -4});
    SG::TSphere<double> sphere{{0, 0, 0}, std::sqrt(26)};
    auto resultTwo = SG::TLinearMath<double>::FindIntersection(lineX, sphere);
    std::cout << "Zad 8.: " << resultTwo[0] << " " << resultTwo[1] << std::endl;

    return 0;
}
