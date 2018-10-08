//
// rgb.cpp
//
// Created by massimo on 10/2/18.
//
#include "rgb.h"
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const rgb::RGB& rgb)
{
  return os << static_cast<uint16_t>(rgb.Red()) << " "
            << static_cast<uint16_t>(rgb.Green()) << " "
            << static_cast<uint16_t>(rgb.Blue());
}

namespace rgbTest
{

[[maybe_unused]]
void
testRGB()
{
  rgb::RGB aColor1 {};
  rgb::RGB aColor2 {255, 255, 255};
  rgb::RGB aColor3 (0x123456);

  std::cout << aColor1 << std::endl;
  std::cout << aColor2 << std::endl;
  std::cout << aColor3 << std::endl;
  std::cout << std::hex << aColor3 << std::dec << std::endl;
  aColor1 = aColor2;
  std::cout << aColor1 << std::endl;
  std::cout << std::boolalpha << (aColor1 == aColor1) << std::endl;
  std::cout << std::boolalpha << (aColor1 == aColor2) << std::endl;
  std::cout << std::boolalpha << (aColor1 != aColor1) << std::endl;
  std::cout << std::boolalpha << (aColor1 != aColor2) << std::endl;
  std::cout << std::hex << "0x" << aColor2.rgb() << std::endl;
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

  // 255 0 0 red
  std::cout << ((c.hsv2rgb(0.0f, 1.0f, 1.0f) == RED) ? "OK" : "NOT OK ") << std::endl;
  // 255 5 0
  std::cout << ((c.hsv2rgb(1.1764705f, 1.0f, 1.0f) == rgb::RGB(255, 5, 0)) ? "OK" : "NOT OK ") << std::endl;
  // 255 0 11
  std::cout << ((c.hsv2rgb(357.41177f, 1.0f, 1.0f) == rgb::RGB(255, 0, 11)) ? "OK" : "NOT OK ") << std::endl;
  // 255 0 5
  std::cout << ((c.hsv2rgb(358.82352f, 1.0f, 1.0f) == rgb::RGB(255, 0, 5)) ? "OK" : "NOT OK ") << std::endl;
  // 26 13 13
  std::cout << ((c.hsv2rgb(357.41177f, 0.5f, 0.1f) == rgb::RGB(26, 13, 13)) ? "OK" : "NOT OK ") << std::endl;
  // 0 0 0 black
  std::cout << ((c.hsv2rgb(357.41177f, 0.0f, 0.0f) == BLACK) ? "OK" : "NOT OK ") << std::endl;
  // 255 255 255 white
  std::cout << ((c.hsv2rgb(0.0f, 0.0f, 1.0f) == WHITE) ? "OK" : "NOT OK ") << std::endl;
  // 255 0 0 red
  std::cout << ((c.hsv2rgb(0.0f, 1.0f, 1.0f) == RED) ? "OK" : "NOT OK ") << std::endl;
  /// 0 0 0 black
  std::cout << ((c.hsv2rgb(0.0f, 1.0f, 0.0f) == BLACK) ? "OK" : "NOT OK ") << std::endl;
  /// 0 0 0 black
  std::cout << ((c.hsv2rgb(1.0f, 0.0f, 0.0f) == BLACK) ? "OK" : "NOT OK ") << std::endl;
  /// 0 0 0 black
  std::cout << ((c.hsv2rgb(90.0f, 0.0f, 0.0f) == BLACK) ? "OK" : "NOT OK ") << std::endl;
  /// 0 255 0 green
  std::cout << ((c.hsv2rgb(120.0f, 1.0f, 1.0f) == GREEN) ? "OK" : "NOT OK ") << std::endl;
  /// 0 0 255 blu
  std::cout << ((c.hsv2rgb(240.0f, 1.0f, 1.0f) == BLUE) ? "OK" : "NOT OK ") << std::endl;
}  // testhsv2rgb

[[maybe_unused]]
void
testrgb2hsv()
{
  const rgb::RGB BLACK{0, 0, 0};
  const rgb::RGB WHITE{255, 255, 255};
  const rgb::RGB RED{255, 0, 0};
  const rgb::RGB GREEN{0, 255, 0};
  const rgb::RGB BLUE{0, 0, 255};

  float hue {};
  float saturation {};
  float brightness {};

  std::cout << std::endl << std::endl;

  BLACK.rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  WHITE.rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  RED.rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  GREEN.rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  BLUE.rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  // 60 100 49.02
  rgb::RGB(125, 125, 0).rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;

  // 0 50 10.2
  rgb::RGB(26, 13, 13).rgb2hsv(hue, saturation, brightness);
  std::cout << hue << " " << saturation << " " << brightness << std::endl;
}

}  // namespace rgbTest
