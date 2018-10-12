//
// main.cpp
//
#include "perlinDemos.h"
#include "palette.h"
#include "bmp.h"
////////////////////////////////////////////////////////////////////////////////
int main()
{
  rgbTest::testRGB();
  rgbTest::testhsv2rgb();
  rgbTest::testrgb2hsv();

  // simple palette creations
  paletteTest::testPalette_1();
  // palette creations and saving them in files in rgb and hsb codings (text files)
  paletteTest::testPalette_2();
  // palette creations and saving them in color map images in bmp and ppm formats
  paletteTest::testPalette_3();
  // read a palette file in hex coding and save it in rgb, hsb text files and the
  // color map image in bmp, ppm files
  paletteTest::testPalette_4();

  bmpTest::testBMP();

  perlinDemo00();
  perlinDemo01();

  return 0;
}
