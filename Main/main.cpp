#include <iostream>
#include <vector>

#include "TVector4.h"
#include "TMat4.h"

int main(int argc, char *argv[]) {
    SG::TVector4<double> TestVector4(1, 0, 0, 1);
    SG::TMat4<double> TestMatrix(0);
    TestMatrix[{0, 0}] = 1;
    TestMatrix[{0,1}] = 2;
    TestMatrix[{0,2}] = 4;
    TestMatrix[{0,3}] = 4;

    TestMatrix[{1, 0}] = 8;
    TestMatrix[{1,1}] = 5;
    TestMatrix[{1,2}] = 3;
    TestMatrix[{1,3}] = 3;

    TestMatrix[{2, 0}] = 3;
    TestMatrix[{2,1}] = 1;
    TestMatrix[{2,2}] = 2;
    TestMatrix[{2,3}] = 2;

    TestMatrix[{3, 0}] = 1;
    TestMatrix[{3,1}] = 2;
    TestMatrix[{3,2}] = 3;
    TestMatrix[{3,3}] = 1;

    std::cout << "Test Matrix: " << std::endl;
    std::cout << TestMatrix << std::endl;

    std::cout << "Determinant Test Matrix: " << std::endl;
    std::cout << TestMatrix.Det() << std::endl;

    std::cout << "Inverted Test Matrix: " << std::endl;
    std::cout << TestMatrix.Inverse() << std::endl;

    SG::TMat4<double> ScaleMatrix = SG::TMat4<double>::Scale(2, 2, 2);
    std::cout << "ScaledVector: " << std::endl;
    std::cout << SG::TVector4<double>(1, 0, 1, 1) * ScaleMatrix << std::endl;
    return 0;
}
