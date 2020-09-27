//
// rgb.cpp
//
// Created by massimo on 10/2/18.
//
#include "rgb.h"
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const sg::rgb::RGB& rgb)
{
  return os << "RGB("
            << static_cast<uint16_t>(rgb.Red()) << ","
            << static_cast<uint16_t>(rgb.Green()) << ","
            << static_cast<uint16_t>(rgb.Blue())
            << ")";
}
