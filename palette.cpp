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

////////////////////////////////////////////////////////////////////////////////
namespace paletteTest {

[[maybe_unused]]
void testPalette_1()
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

  const std::vector<uint32_t> numColors {4, 8, 16, 32, 64, 128, 512};
  for (auto&& nc : numColors)
  {
    palette::Palette p {nc};
    pl(p);
  }
}  // testPalette_1

[[maybe_unused]]
void testPalette_2()
{
  palette::Palette p4 {4};
  palette::Palette p128 {128};
  palette::Palette p256 {256};

  p128.savePalettes("../palettes/", "../palettes/");
  p256.saveRGBPalette("../palettes/");
  p256.saveHSBPalette("../palettes/");

  p4.savePalettes("../palettes/", "../palettes/");
  p4.shufflePalette().savePalettes("../palettes/p4-shuffled-", "../palettes/p4-shuffled-");
}  // testPalette_2

[[maybe_unused]]
void testPalette_3()
{
  const std::vector<uint32_t> numColors {1, 2, 5, 10, 25, 50, 100, 200, 1024, 2048};

  for (auto &&nc : numColors)
  {
    palette::Palette p {nc};

    p.makePaletteImage<ppm::ppm>("../palettes/");
    p.makePaletteImage<bmp::bmp>("../palettes/");
    //p.shufflePalette().makePaletteImage<ppm::ppm>("../palettes/p-shuffled-");
  }
}  // testPalette_3

[[maybe_unused]]
void testPalette_4()
{
  palette::Palette p {"../palettes/0330-stage-1.2-palette.txt"};

  p.savePalettes("../palettes/", "../palettes/");
  p.makePaletteImage<ppm::ppm>("../palettes/");
  p.makePaletteImage<bmp::bmp>("../palettes/");

}  // testPalette_4

}  // namespace PaletteTest
