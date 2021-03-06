//
// main.cpp
//
#include "image.h"
#include "palette.h"
#include "rgbTest.h"
#include "imageTest.h"
#include "perlinDemos.h"
#include "paletteTest.h"
////////////////////////////////////////////////////////////////////////////////

[[maybe_unused]]
static
void
fullTests()
{
  sg::rgbTest::testRGB();
  sg::rgbTest::testhsv2rgb();
  sg::rgbTest::testrgb2hsv();

  // simple palette creations; saved in image files and text files
  sg::paletteTest::testPalette_Full_RGB();
  sg::paletteTest::testPalette_00();
  sg::paletteTest::testPalette_0();
  sg::paletteTest::testPalette_1();
  sg::paletteTest::testPalette_2();
  // palette creations and saving them in files in rgb and hsb codings (text files)
  sg::paletteTest::testPalette_3();
  // palette creations and saving them in color map images in bmp and ppm formats
  sg::paletteTest::testPalette_4();
  // read a palette file in hex coding and save it in rgb, hsb text files and the
  // color map image in bmp, ppm files
  sg::paletteTest::testPalette_5();

  sg::paletteTest::testPalette_6();
  sg::paletteTest::testPalette_7();
  sg::paletteTest::testPalette_8();

  sg::imageTest::testPPM();
  sg::imageTest::testBMP();
  sg::imageTest::testPNG();
  sg::imageTest::testImageFileFormat();

  sg::perlinTest::perlinDemo00();
  sg::perlinTest::perlinDemo01();
}

int
main()
{
  fullTests();
  return 0;
}
