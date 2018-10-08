//
// helpers.cpp
//
// Created by massimo on 10/2/18.
//
#include "helpers.h"
////////////////////////////////////////////////////////////////////////////////
// the empty tuple
std::ostream &operator<<(std::ostream &os, const std::tuple<>&)
{
  return os << "{}";
}
