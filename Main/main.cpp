#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TQuanternion.h"
#include "TLinearMath.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TLine<double> lineOne{{3, 1, 5}, {2, -4, 0}};
    SG::TLine<double> lineTwo{{1, -5, 3}, {2, -4, 0}};

    std::cout << "Zad 1.: " << SG::TLinearMath<double>::FindIntersection(lineOne, lineTwo) << std::endl;
    std::cout << "Zad 2.: " << SG::TLinearMath<double>::FindAngle(lineOne, lineTwo) << std::endl;

    return 0;
}
