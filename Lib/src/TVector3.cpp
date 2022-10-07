#include "TVector3.h"

#include <iostream>

const char *SG::DivisionByZeroException::what() const noexcept {
    return "ERROR: Division by zero";
}
