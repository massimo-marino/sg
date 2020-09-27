//
// rgbTest.cpp
//
// Created by massimo on 9/27/20.
//
#include "rgbTest.h"
////////////////////////////////////////////////////////////////////////////////

namespace sg::rgbTest {

[[maybe_unused]]
void
testRGB()
{
  rgb::RGB aColor1 {};
  rgb::RGB aColor2 {255, 255, 255};
  rgb::RGB aColor3 (0x123456);

  std::cout << "aColor1 (0,0,0): " << aColor1 << std::endl;
  std::cout << "aColor2(255, 255, 255): " << aColor2 << std::endl;
  std::cout << "aColor3(18, 52, 86): " << aColor3 << std::endl;
  std::cout << "aColor3(0x12, 0x34, 0x56): " << std::hex << aColor3 << std::dec << std::endl;
  aColor1 = aColor2;
  std::cout << "aColor1(255, 255, 255): " << aColor1 << std::endl;
  std::cout << "(aColor1 == aColor1) is true: " << std::boolalpha << (aColor1 == aColor1) << std::endl;
  std::cout << "(aColor1 == aColor2) is true: " << std::boolalpha << (aColor1 == aColor2) << std::endl;
  std::cout << "(aColor1 != aColor1) is false: " << std::boolalpha << (aColor1 != aColor1) << std::endl;
  std::cout << "(aColor1 != aColor2) is false: " << std::boolalpha << (aColor1 != aColor2) << std::endl;
  std::cout << "aColor2 RGB HEX 0xffffff: " <<  std::hex << "0x" << aColor2.rgb() << std::dec << std::endl;
}  // testRGB

[[maybe_unused]]
void
testhsv2rgb()
{
  const rgb::RGB BLACK {0,   0,   0};
  const rgb::RGB WHITE {255, 255, 255};
  const rgb::RGB RED   {255, 0,   0};
  const rgb::RGB GREEN {0,   255, 0};
  const rgb::RGB BLUE  {0,   0,   255};

  rgb::RGB c {};

  std::cout << std::boolalpha;

  // 87 153 124
  rgb::RGB& result = c.hsv2rgb(154.0f, 0.43f, 0.60f);
  std::cout << ((result ==  rgb::RGB(87, 153, 124)) ? "OK" : "NOT OK ") << " - result: RGB: " << result << std::endl;

  // 255 5 0
  result = c.hsv2rgb(1.18f, 1.0f, 1.0f);
  std::cout << ((result == rgb::RGB(255, 5, 0)) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 37 106 211
  result = c.hsv2rgb(216.12f, 0.8246f, 0.8275f);
  std::cout << ((result == rgb::RGB(37, 106, 211)) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 255 0 5
  result = c.hsv2rgb(358.82352f, 1.0f, 1.0f);
  std::cout << ((result == rgb::RGB(255, 0, 5)) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 26 13 13
  result = c.hsv2rgb(357.41177f, 0.5f, 0.1f);
  std::cout << ((result == rgb::RGB(26, 13, 13)) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 0 0 0 black
  result = c.hsv2rgb(338.41177f, 0.0f, 0.0f);
  std::cout << ((result == BLACK) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 255 255 255 white
  result = c.hsv2rgb(0.0f, 0.0f, 1.0f);
  std::cout << ((result == WHITE) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  // 255 0 0 red
  result = c.hsv2rgb(0.0f, 1.0f, 1.0f);
  std::cout << ((result == RED) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  /// 0 0 0 black
  result = c.hsv2rgb(0.0f, 1.0f, 0.0f);
  std::cout << ((result == BLACK) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  /// 0 0 0 black
  result = c.hsv2rgb(1.0f, 0.0f, 0.0f);
  std::cout << ((result == BLACK) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  /// 0 0 0 black
  result = c.hsv2rgb(90.0f, 0.0f, 0.0f);
  std::cout << ((result == BLACK) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  /// 0 255 0 green
  result = c.hsv2rgb(120.0f, 1.0f, 1.0f);
  std::cout << ((result == GREEN) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;

  /// 0 0 255 blue
  result = c.hsv2rgb(240.0f, 1.0f, 1.0f);
  std::cout << ((result == BLUE) ? "OK" : "NOT OK") << " - result: RGB: " << result << std::endl;
}  // testhsv2rgb

[[maybe_unused]]
void
testrgb2hsv()
{
  const rgb::RGB BLACK {0,   0,   0};
  const rgb::RGB WHITE {255, 255, 255};
  const rgb::RGB RED   {255, 0,   0};
  const rgb::RGB GREEN {0,   255, 0};
  const rgb::RGB BLUE  {0,   0,   255};

  float hue {};
  float saturation {};
  float brightness {};

  std::cout << std::endl << std::endl;

  BLACK.rgb2hsv(hue, saturation, brightness);
  std::cout << "BLACK RGB(0,0,0): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  WHITE.rgb2hsv(hue, saturation, brightness);
  std::cout << "WHITE RGB(255,255,255): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  RED.rgb2hsv(hue, saturation, brightness);
  std::cout << "RED RGB(255,0,0): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  GREEN.rgb2hsv(hue, saturation, brightness);
  std::cout << "GREEN RGB(0,255,0): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  BLUE.rgb2hsv(hue, saturation, brightness);
  std::cout << "BLUE RGB(0,0,255): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  // 60 100 49.02
  rgb::RGB(125, 125, 0).rgb2hsv(hue, saturation, brightness);
  std::cout << "RGB(125, 125, 0) -> HSV(60,100,49.02): HSV: " << hue << " " << saturation << " " << brightness << std::endl;

  // 0 50 10.2
  rgb::RGB(26, 13, 13).rgb2hsv(hue, saturation, brightness);
  std::cout << "RGB(26, 13, 13) -> HSV(0,50,10.2): HSV: " << hue << " " << saturation << " " << brightness << std::endl;
}

}  // namespace sg::rgbTest
