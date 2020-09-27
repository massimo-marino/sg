//
// paletteTest.cpp
//
// Created by massimo on 9/27/20.
//
#include "palette.h"
#include "paletteTest.h"

#include <unordered_set>
////////////////////////////////////////////////////////////////////////////////

namespace sg::paletteTest {

[[maybe_unused]]
void testPalette_Full_RGB()
{
  palette::Palette p {};
  p.allRGBColors();
  std::cout << "palette size: " << p.size() << std::endl;
  std::cout << "numColors: " << p.numColors();
  p.saveRGBHexPalette("../palettes/generated/rgb/");
}

[[maybe_unused]]
void testPalette_00()
{
  const uint32_t numColors {256 * 256 * 256};
  float saturation {1.0f};
  float brightness {1.0f};
  palette::Palette p {};

  while (saturation >= 0.0f)
  {
    p.makeCustomPalette(numColors, saturation, brightness);

    std::cout << "\nnumColors, saturation, brightness: "
              << numColors << ", "
              << saturation << ", "
              << brightness
              << " -> palette size: " << p.size();
    std::cout << "\n";

    const std::string fileName {"../palettes/generated/tp00/s-" +
                                std::to_string(saturation) +
                                "-b-" + std::to_string(brightness) +"-"};
    p.makePaletteImage(fileName);
    p.saveRGBHexPalette(fileName);

//    brightness = brightness - 0.1f;
    saturation = saturation - 0.1f;
  }
}

[[maybe_unused]]
void testPalette_0()
{
  const uint32_t numColors {256 * 256 * 256};
  const float saturation {1.0f};
  const float brightness {1.0f};
  palette::Palette p {numColors, saturation, brightness};
  std::unordered_set<sg::rgb::RGB_t> colorSet(numColors);

  for (const rgb::RGB& RGBColor : p())
  {
    // insert unique color elements (no copies)
    colorSet.insert(RGBColor);
  }
  // create the palette
  pixels_t colorV(colorSet.begin(), colorSet.end());

  std::cout << "\nnumColors: " << numColors;
  std::cout << "\npalette p size before replacement: " << p.size();
  std::cout << "\ncolorSet size: " << colorSet.size();
  std::cout << "\ncolorV size: " << colorV.size();

  // replace the palette
  p.setPalette(colorV);
  std::cout << "\npalette p size after palette replacement: " << p.size();
  std::cout << "\n";

  p.makePaletteImage("../palettes/generated/tp0/");
  p.saveRGBHexPalette("../palettes/generated/tp0/");
}  // testPalette_0

[[maybe_unused]]
void testPalette_1()
{
  auto pl = [] (const palette::Palette& p,
                palette::Palette& q,
                const uint32_t numColors)
  {
    auto i {0};
    auto counter {0};
    rgb::RGB previousRGBColor {};
    for (const rgb::RGB& RGBColor : p())
    {
      if (RGBColor != previousRGBColor) {
        std::cout << i << "/" << numColors << ": " << RGBColor << "\n";
        q.addRGBColor(RGBColor);
        previousRGBColor = RGBColor;
        ++counter;
      }
      ++i;
    }

    std::cout << "\nnumColors: " << numColors;
    std::cout << "\ncounter: " << counter;
    std::cout << "\n";
  };

  const uint32_t numColors {256 * 256 * 256};
  const float saturation {0.9f};
  const float brightness {0.9f};
  const palette::Palette p {numColors, saturation, brightness};
  palette::Palette q {};

  pl(p, q, numColors);
  std::cout << "palette p size: " << p.size() << std::endl;
  std::cout << "palette q size: " << q.size() << std::endl;

  // palette image saved in a png file by default
  q.makePaletteImage("../palettes/generated/tp1/");
  q.saveRGBHexPalette("../palettes/generated/tp1/");

  // grayscale palette
  palette::Palette grayScale {};
  grayScale.setGrayScalePalette();
  // palette image saved in a png file by default
  grayScale.makePaletteImage("../palettes/generated/tp1/");
}  // testPalette_1

[[maybe_unused]]
void testPalette_2()
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

  const std::vector<uint32_t> numColors {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4196};
  for (auto&& nc : numColors)
  {
    palette::Palette p {nc};
    // palette image saved in a png file by default
    p.makePaletteImage("../palettes/generated/tp2/");
    p.saveRGBHexPalette("../palettes/generated/tp2/");
    pl(p, nc);
  }
}  // testPalette_2

[[maybe_unused]]
void testPalette_3()
{
  palette::Palette p40 {40};
  palette::Palette p1280 {1280};
  palette::Palette p2560 {2560};

  p1280.savePalettes("../palettes/generated/tp3/",
                     "../palettes/generated/tp3/",
                     "../palettes/generated/tp3/");
  p2560.saveRGBHexPalette("../palettes/generated/tp3/");
  p2560.saveRGBPalette("../palettes/generated/tp3/");
  p2560.saveHSBPalette("../palettes/generated/tp3/");

  p40.savePalettes("../palettes/generated/tp3/",
                   "../palettes/generated/tp3/",
                   "../palettes/generated/tp3/");
  p40.shufflePalette().savePalettes("../palettes/generated/tp3/p40-shuffled-",
                                    "../palettes/generated/tp3/p40-shuffled-",
                                    "../palettes/generated/tp3/p40-shuffled-");
}  // testPalette_3

[[maybe_unused]]
void testPalette_4()
{
  const std::vector<uint32_t> numColors {5, 10, 25, 50, 100, 500, 1000, 2000};

  for (auto &&nc : numColors)
  {
    palette::Palette p {nc};

    // palette image saved in a png file by default
    p.makePaletteImage("../palettes/generated/tp4/");
//    p.makePaletteImage<sg::ppm>("../palettes/generated/");
//    p.makePaletteImage<sg::bmp>("../palettes/generated/");
//    p.makePaletteImage<sg::png>("../palettes/generated/");
    p.shufflePalette().makePaletteImage<sg::ppm>("../palettes/generated/tp4/p-shuffled-");
  }
}  // testPalette_4

[[maybe_unused]]
void testPalette_5()
{
  palette::Palette p {"../palettes/0330-stage-1.2-palette.txt"};

  p.sortPalette();
  p.savePalettes("../palettes/generated/tp5/0330-stage-1.2-",
                 "../palettes/generated/tp5/0330-stage-1.2-",
                 "../palettes/generated/tp5/0330-stage-1.2-");

  // palette image saved in a png file by default
  p.makePaletteImage("../palettes/generated/tp5/0330-stage-1.2-");
//  p.makePaletteImage<sg::ppm>("../palettes/generated/tp5/");
//  p.makePaletteImage<sg::bmp>("../palettes/generated/tp5/");
//  p.makePaletteImage<sg::png>("../palettes/generated/tp5/");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/tp5/0330-stage-1.2-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp5/0330-stage-1.2-shuffled-");

}  // testPalette_5

[[maybe_unused]]
void testPalette_6()
{
  palette::Palette p {"../palettes/c20-sorted.txt"};

  p.saveRGBHexPalette("../palettes/generated/tp6/c20-sorted-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp6/c20-sorted-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/tp6/c20-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp6/c20-shuffled-");

}  // testPalette_6

[[maybe_unused]]
void testPalette_7()
{
  palette::Palette p {"../palettes/c20-sorted-2.txt"};

  p.saveRGBHexPalette("../palettes/generated/tp7/c20-sorted-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp7/c20-sorted-2-");

  p.shufflePalette();
  p.saveRGBHexPalette("../palettes/generated/tp7/c20-shuffled-2-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp7/c20-shuffled-2-");

}  // testPalette_7

[[maybe_unused]]
void testPalette_8()
{
  uint32_t numColors {256};
  float saturation {0.925f};
  float brightness {0.935f};
  palette::Palette p {numColors, saturation, brightness};

  p.saveRGBHexPalette("../palettes/generated/tp8/");
  p.saveRGBPalette("../palettes/generated/tp8/");
  p.saveHSBPalette("../palettes/generated/tp8/");
  // palette image saved in a png file by default
  p.makePaletteImage("../palettes/generated/tp8/");

  p.shufflePalette().savePalettes("../palettes/generated/tp8/p256-shuffled-",
                                  "../palettes/generated/tp8/p256-shuffled-",
                                  "../palettes/generated/tp8/p256-shuffled-");
  // palette image saved in a png file
  p.makePaletteImage<sg::png>("../palettes/generated/tp8/p256-shuffled-");
}  // testPalette_8

}  // namespace sg::PaletteTest
