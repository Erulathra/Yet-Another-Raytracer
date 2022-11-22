#include <iostream>
#include <vector>

#include "TVector4.h"
#include "TMat4.h"

int main(int argc, char *argv[]) {
    SG::TMat4<float> MatTest1(0);
    MatTest1[{0, 0}] = 1; MatTest1[{1, 0}] = 8; MatTest1[{2, 0}] = 3; MatTest1[{3, 0}] = 1;
    MatTest1[{0, 1}] = 2; MatTest1[{1, 1}] = 5; MatTest1[{2, 1}] = 1; MatTest1[{3, 1}] = 2;
    MatTest1[{0, 2}] = 4; MatTest1[{1, 2}] = 3; MatTest1[{2, 2}] = 2; MatTest1[{3, 2}] = 3;
    MatTest1[{0, 3}] = 4; MatTest1[{1, 3}] = 3; MatTest1[{2, 3}] = 2; MatTest1[{3, 3}] = 1;

    SG::TMat4<float> MatTest2(0);
    MatTest2[{0, 0}] = 4; MatTest2[{1, 0}] = 2; MatTest2[{2, 0}] = 1; MatTest2[{3, 0}] = 4;
    MatTest2[{0, 1}] = 8; MatTest2[{1, 1}] = 7; MatTest2[{2, 1}] = 3; MatTest2[{3, 1}] = 3;
    MatTest2[{0, 2}] = 3; MatTest2[{1, 2}] = 4; MatTest2[{2, 2}] = 8; MatTest2[{3, 2}] = 2;
    MatTest2[{0, 3}] = 1; MatTest2[{1, 3}] = 7; MatTest2[{2, 3}] = 0; MatTest2[{3, 3}] = 1;


    std::cout << "Matrix 1: " << std::endl;
    std::cout << MatTest1 << std::endl;

    std::cout << "Matrix 2: " << std::endl;
    std::cout << MatTest2 << std::endl;

    std::cout << "Add Matrices: " << std::endl;
    std::cout << MatTest1 + MatTest2 << std::endl;

    std::cout << "Subtract Matrices: " << std::endl;
    std::cout << MatTest1 - MatTest2 << std::endl;

    std::cout << "Multiply Matrix 1 by scalar: " << std::endl;
    std::cout << MatTest1 * 3 << std::endl;


    {
        SG::TMat4<float> Multiply1 = MatTest1 * MatTest2;
        std::cout << "Multiply Matrix 1 by Matrix 2: " << std::endl;
        std::cout << MatTest1 * MatTest2 << std::endl;

        SG::TMat4<float> Multiply2 = MatTest2 * MatTest1;
        std::cout << "Multiply Matrix 2 by Matrix 1: " << std::endl;
        std::cout << MatTest2 * MatTest1 << std::endl;

        if (Multiply1 == Multiply2)
            std::cout << "Multiplications are equal." << std::endl << std::endl;
        else
            std::cout << "Multiplications are NOT equal." << std::endl << std::endl;
    }


    std::cout << "Determinant Matrix 1: " << std::endl;
    std::cout << MatTest1.Det() << std::endl << std::endl;

    std::cout << "Inverted Matrix 1: " << std::endl;
    std::cout << MatTest1.Inverse() << std::endl;

    std::cout << "Transposed Matrix 1: " << std::endl;
    std::cout << MatTest1.Transpose() << std::endl;


    std::cout << "Translation Matrix 1 by [1, 2, 3]: " << std::endl;
    std::cout << MatTest1 * SG::TMat4<float>::Translation(1, 2, 3) << std::endl;

    std::cout << "Scaling Matrix 1 by [1, 2, 3]: " << std::endl;
    std::cout << MatTest1 * SG::TMat4<float>::Scale(1, 2, 3) << std::endl;

    std::cout << "Rotation Matrix 1 by [1, 2, 3]: " << std::endl;
    std::cout << MatTest1 * SG::TMat4<float>::RotationY(M_PI * 0.5) << std::endl;


    SG::TMat4<double> RotationMatrix = SG::TMat4<double>::RotationY(M_PI * 0.5);
    std::cout << "Rotate : " << std::endl;
    std::cout << SG::TVector4<double>(1, 0, 0, 1) * RotationMatrix << std::endl;
    std::cout << SG::TVector4<double>(1, 0, 0, 1)<< std::endl;
    return 0;
}
