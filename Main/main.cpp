#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TMat4.h"
#include "TQuanternion.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TQuanternion<double> test = SG::TQuanternion<double>::GetRotationQuanternion((3./2. * M_PI), SG::TVector3<double>(1., 0., 0.));
    std::cout << test.Rotate(SG::TVector3<double>(-1., -1., -1.)) << std::endl;

    SG::TQuanternion<double> quanternion_1 = SG::TQuanternion<double>(1, 0, 3, 5);
    SG::TQuanternion<double> quanternion_2 = SG::TQuanternion<double>(1, 1, 0, 2);

    std::cout << "Quanternion 1: " << quanternion_1 << std::endl;
    std::cout << "Quanternion 2: " << quanternion_2 << std::endl;
    std::cout << "Minus Quanternion 2: " << -quanternion_2 << std::endl;

    std::cout << "Sum: " << quanternion_1 + quanternion_2 << std::endl;
    std::cout << "Difference: " << quanternion_1 - quanternion_2 << std::endl;

    std::cout << "Product: " << quanternion_1 * quanternion_2 << std::endl;
    std::cout << "Division: " << quanternion_1 / quanternion_2 << std::endl;
    return 0;
}
