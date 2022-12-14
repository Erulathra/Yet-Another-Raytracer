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

    std::cout << "Test: " << planeOne.normalVector.Normal() << std::endl;

    std::cout << "Zad 1.: " << SG::TLinearMath<double>::FindIntersection(lineOne, lineTwo) << std::endl;
    std::cout << "Zad 2.: " << SG::TLinearMath<double>::FindAngle(lineOne, lineTwo) << std::endl;
    std::cout << "Zad 3.: " << SG::TLinearMath<double>::FindIntersection(lineThree, planeOne) << std::endl;

    return 0;
}
