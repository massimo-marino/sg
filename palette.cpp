//
// palette.cpp
//
// Created by massimo on 10/8/18.
//
#include "palette.h"
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const sg::palette::Palette& p)
{
  for (auto&& c : p())
  {
    os << c << "\n";
  }
  return os;
}
