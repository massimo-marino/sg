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
void testPalette_0()
{
  auto pl = [] (const palette::Palette& p, const uint32_t numColors)
  {
    auto i {0};
    for (auto &&item : p())
    {
      std::cout << ++i << "/" << numColors << ": " << item << "\n";
    }
    std::cout << "\n\n";
  };

  const uint32_t numColors {256 * 256 * 256};

  palette::Palette p {numColors, 1.0f, 1.0f};

  std::cout << p.size() << std::endl;

  pl(p, numColors);
}  // testPalette_0

[[maybe_unused]]
void testPalette_1()
{
  auto pl = [] (const palette::Palette& p, const uint32_t numColors)
  {
    auto i {0};
    for (auto &&item : p())
    {
      std::cout << ++i << "/" << numColors << ": " << item << "\n";
    }
    std::cout << "\n\n";
  };

  const std::vector<uint32_t> numColors {4, 8, 16, 32, 64, 128, 512};
  for (auto&& nc : numColors)
  {
    palette::Palette p {nc};
    pl(p, nc);
  }
}  // testPalette_1

[[maybe_unused]]
void testPalette_2()
{
  palette::Palette p4 {4};
  palette::Palette p128 {128};
  palette::Palette p256 {256};

  p128.savePalettes("../palettes/generated/",
                    "../palettes/generated/",
                    "../palettes/generated/");
  p256.saveRGBHexPalette("../palettes/generated/");
  p256.saveRGBPalette("../palettes/generated/");
  p256.saveHSBPalette("../palettes/generated/");

  p4.savePalettes("../palettes/generated/",
                  "../palettes/generated/",
                  "../palettes/generated/");
  p4.shufflePalette().savePalettes("../palettes/generated/p4-shuffled-",
                                   "../palettes/generated/p4-shuffled-",
                                   "../palettes/generated/p4-shuffled-");
}  // testPalette_2

[[maybe_unused]]
void testPalette_3()
{
  const std::vector<uint32_t> numColors {1, 2, 5, 10, 25, 50, 100, 200, 1024, 2048};

  for (auto &&nc : numColors)
  {
    palette::Palette p {nc};

    // palette image saved in a png file by default
    p.makePaletteImage("../palettes/generated/");
//    p.makePaletteImage<sg::ppm>("../palettes/generated/");
//    p.makePaletteImage<sg::bmp>("../palettes/generated/");
//    p.makePaletteImage<sg::png>("../palettes/generated/");
    p.shufflePalette().makePaletteImage<sg::ppm>("../palettes/generated/p-shuffled-");
  }
}  // testPalette_3

[[maybe_unused]]
void testPalette_4()
{
  palette::Palette p {"../palettes/0330-stage-1.2-palette.txt"};

  p.sortPalette();
  p.savePalettes("../palettes/generated/0330-stage-1.2-",
                 "../palettes/generated/0330-stage-1.2-",
                 "../palettes/generated/0330-stage-1.2-");

  // palette image saved in a png file by default
  p.makePaletteImage("../palettes/generated/0330-stage-1.2-");
//  p.makePaletteImage<sg::ppm>("../palettes/generated/");
//  p.makePaletteImage<sg::bmp>("../palettes/generated/");
//  p.makePaletteImage<sg::png>("../palettes/generated/");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/0330-stage-1.2-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/0330-stage-1.2-shuffled-");

}  // testPalette_4

[[maybe_unused]]
void testPalette_5()
{
  palette::Palette p {"../palettes/c20-sorted.txt"};

  p.saveRGBHexPalette("../palettes/generated/c20-sorted-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/c20-sorted-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/c20-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/c20-shuffled-");

}  // testPalette_5

[[maybe_unused]]
void testPalette_6()
{
  palette::Palette p {"../palettes/c20-sorted-2.txt"};

  p.saveRGBHexPalette("../palettes/generated/c20-sorted-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/c20-sorted-2-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/c20-shuffled-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/c20-shuffled-2-");

}  // testPalette_6

[[maybe_unused]]
void testPalette_7()
{
  uint32_t numColors {256};
  float saturation {0.925f};
  float brightness {0.935f};
  palette::Palette p {numColors, saturation, brightness};

  p.saveRGBHexPalette("../palettes/generated/");
  p.saveRGBPalette("../palettes/generated/");
  p.saveHSBPalette("../palettes/generated/");
  // palette image saved in a png file by default
  p.makePaletteImage("../palettes/generated/");

  p.shufflePalette().savePalettes("../palettes/generated/p256-shuffled-",
                                      "../palettes/generated/p256-shuffled-",
                                      "../palettes/generated/p256-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/p256-shuffled-");
}  // testPalette_7

}  // namespace sg::PaletteTest
