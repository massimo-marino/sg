//
// main.cpp
//
#include "perlinDemos.h"
#include "palette.h"
#include "image.h"
////////////////////////////////////////////////////////////////////////////////

int main()
{
  sg::rgbTest::testRGB();
  sg::rgbTest::testhsv2rgb();
  sg::rgbTest::testrgb2hsv();

  // simple palette creations
  sg::paletteTest::testPalette_1();
  // palette creations and saving them in files in rgb and hsb codings (text files)
  sg::paletteTest::testPalette_2();
  // palette creations and saving them in color map images in bmp and ppm formats
  sg::paletteTest::testPalette_3();
  // read a palette file in hex coding and save it in rgb, hsb text files and the
  // color map image in bmp, ppm files
  sg::paletteTest::testPalette_4();

  sg::paletteTest::testPalette_5();

  sg::imageTest::testPPM();
  sg::imageTest::testBMP();
  sg::imageTest::testPNG();
  sg::imageTest::testImageFileFormat();

  sg::perlinTest::perlinDemo00();
  sg::perlinTest::perlinDemo01();

  return 0;
}
