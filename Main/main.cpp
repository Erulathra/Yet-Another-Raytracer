#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TQuanternion.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TQuanternion<double> test = SG::TQuanternion<double>::GetRotationQuanternion((3./2. * M_PI), SG::TVector3<double>(1., 0., 0.));
    std::cout << std::endl << "Rotation of vector {-1, -1, -1} by 270 degrees around X axis:" << std::endl << test.Rotate(SG::TVector3<double>(-1., -1., -1.)) << std::endl << std::endl;

    SG::TQuanternion<double> quanternion_1 = SG::TQuanternion<double>(1, 0, 3, 5);
    SG::TQuanternion<double> quanternion_2 = SG::TQuanternion<double>(1, 1, 0, 2);

    std::cout << "Quanternion 1: " << quanternion_1 << std::endl;
    std::cout << "Quanternion 2: " << quanternion_2 << std::endl << std::endl;
//    std::cout << "Minus Quanternion 2: " << -quanternion_2 << std::endl;

    std::cout << "Sum: " << quanternion_1 + quanternion_2 << std::endl << std::endl;
    std::cout << "Difference: " << quanternion_1 - quanternion_2 << std::endl << std::endl;

    SG::TQuanternion<double> result_1 = quanternion_1 * quanternion_2;
    SG::TQuanternion<double> result_2 = quanternion_2 * quanternion_1;
    std::cout << "Product Q1 * Q2: " << result_1 << std::endl;
    std::cout << "Product Q2 * Q1: " << result_2 << std::endl << std::endl;

    if(result_1 == result_2)
        std::cout << "Multiplication is commutative" << std::endl << std::endl;
    else
        std::cout << "Multiplication is not commutative" << std::endl << std::endl;


    std::cout << "Division Q1 / Q2: " << quanternion_1 / quanternion_2 << std::endl;
    std::cout << "Division Q2 / Q1: " << quanternion_2 / quanternion_1 << std::endl << std::endl;
    return 0;
}
