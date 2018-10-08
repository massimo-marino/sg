//
// palette.cpp
//
// Created by massimo on 10/8/18.
//
#include "palette.h"
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const palette::Palette& p)
{
  for (auto&& c : p())
  {
    os << c << "\n";
  }
  return os;
}

namespace paletteTest
{

[[maybe_unused]]
void testPalette()
{
  auto pl = [] (const palette::Palette& p)
  {
    auto i {0};
    for (auto &&item : p())
    {
      std::cout << ++i << ": " << item << "\n";
    }
    std::cout << "\n\n";
  };

  palette::Palette p4 {4};
  palette::Palette p8 {8};
  palette::Palette p16 {};
  palette::Palette p32 {32};
  palette::Palette p64 {64};
  palette::Palette p128 {128};
  palette::Palette p256 {256};

  pl(p4);
  pl(p8);
  pl(p16);
  pl(p32);
  pl(p64);
  pl(p128);
  pl(p256);
}  // testPalette

[[maybe_unused]]
void testPalette_2()
{
  palette::Palette p4 {4};
  palette::Palette p128 {128};
  palette::Palette p256 {256};

  p128.savePalettes();
  p256.saveRGBPalette();
  p256.saveHSBPalette();

  p4.savePalettes();
  p4.shufflePalette();
  p4.savePalettes("p4-rgb-palette-shuffled.txt", "p4-hsb-palette-shuffled.txt");
}  // testPalette_2

}  // namespace PaletteTest
