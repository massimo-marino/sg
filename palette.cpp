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

////////////////////////////////////////////////////////////////////////////////
namespace sg::paletteTest {

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

  p128.savePalettes("../palettes/", "../palettes/", "../palettes/");
  p256.saveRGBHexPalette("../palettes/");
  p256.saveRGBPalette("../palettes/");
  p256.saveHSBPalette("../palettes/");

  p4.savePalettes("../palettes/", "../palettes/", "../palettes/");
  p4.shufflePalette().savePalettes("../palettes/p4-shuffled-",
                                   "../palettes/p4-shuffled-",
                                   "../palettes/p4-shuffled-");
}  // testPalette_2

[[maybe_unused]]
void testPalette_3()
{
  const std::vector<uint32_t> numColors {1, 2, 5, 10, 25, 50, 100, 200, 1024, 2048};

  for (auto &&nc : numColors)
  {
    palette::Palette p {nc};

    // palette image saved in a png file by default
    p.makePaletteImage("../palettes/");
//    p.makePaletteImage<sg::ppm>("../palettes/");
//    p.makePaletteImage<sg::bmp>("../palettes/");
//    p.makePaletteImage<sg::png>("../palettes/");
    //p.shufflePalette().makePaletteImage<ppm::ppm>("../palettes/p-shuffled-");
  }
}  // testPalette_3

[[maybe_unused]]
void testPalette_4()
{
  palette::Palette p {"../palettes/0330-stage-1.2-palette.txt"};

  p.sortPalette();
  p.savePalettes("../palettes/0330-stage-1.2-",
                 "../palettes/0330-stage-1.2-",
                 "../palettes/0330-stage-1.2-");

  // palette image saved in a png file by default
  p.makePaletteImage("../palettes/");
//  p.makePaletteImage<sg::ppm>("../palettes/");
//  p.makePaletteImage<sg::bmp>("../palettes/");
//  p.makePaletteImage<sg::png>("../palettes/");

}  // testPalette_4

[[maybe_unused]]
void testPalette_5()
{
  palette::Palette p {"../palettes/c20-sorted.txt"};

  p.saveRGBHexPalette("../palettes/c20-sorted-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/c20-sorted-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/c20-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/c20-shuffled-");

}  // testPalette_5

[[maybe_unused]]
void testPalette_6()
{
  palette::Palette p {"../palettes/c20-sorted-2.txt"};

  p.saveRGBHexPalette("../palettes/c20-sorted-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/c20-sorted-2-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/c20-shuffled-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/c20-shuffled-2-");

}  // testPalette_6

}  // namespace sg::PaletteTest
