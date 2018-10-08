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

  const std::vector<uint32_t> numColors {4, 8, 16, 32, 64, 128, 256};
  for (auto&& nc : numColors)
  {
    palette::Palette p {nc};
    pl(p);
  }
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
  p4.shufflePalette().savePalettes("p4-rgb-palette-shuffled.txt", "p4-hsb-palette-shuffled.txt");
}  // testPalette_2

[[maybe_unused]]
void testPalette_3()
{
  const std::vector<uint32_t> numColors {1, 2, 5, 10, 25, 50, 100, 200, 1024, 2048};

  for (auto &&c : numColors)
  {
    palette::Palette p {c};

    p.makePaletteImage_PPM();
    //p.shufflePalette().makePaletteImage_PPM();
  }
}  // testPalette_3

}  // namespace PaletteTest
