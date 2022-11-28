#include <iostream>
#include <vector>

#include "TVector3.h"
#include "TMat4.h"
#include "TQuanternion.h"
#include <cmath>

int main(int argc, char *argv[]) {
    SG::TQuanternion<double> test = SG::TQuanternion<double>::GetRotationQuanternion((3./2. * M_PI), SG::TVector3<double>(1., 0., 0.));
    std::cout << test.Rotate(SG::TVector3<double>(-1., -1., -1.)) << std::endl;
    
    return 0;
}
