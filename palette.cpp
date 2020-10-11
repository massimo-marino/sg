//
// palette.cpp
//
// Created by massimo on 10/8/18.
//
#include "palette.h"
////////////////////////////////////////////////////////////////////////////////
namespace sg::palette {

const std::string Palette::rgbHexPaletteFileNameExtension_ {".rgbhex"};

std::string Palette::getOrder() const
{
  return order_;
}

void Palette::setOrder(const std::string& order)
{
  order_ = order;
}

}

std::ostream& operator<<(std::ostream &os, const sg::palette::Palette& p)
{
  for (auto&& c : p())
  {
    os << c << "\n";
  }
  return os;
}
