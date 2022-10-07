#include <iostream>

#include "TVector3.h"

int main(int argc, char *argv[]) {
    SG::TVector3<double> VectorOne(0., 3., 0.);
    SG::TVector3<double> VectorTwo(5., 5., 0.);

    SG::TVector3<double> VectorTree(4., 5., 1.);
    SG::TVector3<double> VectorFour(4., 1., 3.);

    std::cout << VectorOne << " + " << VectorTwo << " = " << VectorOne + VectorTwo << std::endl;
    std::cout << VectorTwo << " + " << VectorOne << " = " << VectorTwo + VectorOne << std::endl;


    std::cout << "Angle between " << VectorOne << ", and " << VectorTwo << "is: "
              << VectorOne.Angle(VectorTwo) << " rad" << std::endl;

    SG::TVector3<double> VectorFive = VectorTree.Cross(VectorFour);
    std::cout << "Normal vector to " << VectorTree << " and " << VectorFour
              << " is: " << VectorFive << std::endl;
    std::cout << "Normalized " << VectorFive << " is: " << VectorFive.Normal() << std::endl;
    return 0;
}
