//
// bmp.cpp
//
// Created by massimo on 10/8/18.
//
#include "bmp.h"

////////////////////////////////////////////////////////////////////////////////
namespace bmpTest {

[[maybe_unused]]
void
testBMP()
{
  std::uint32_t width {256};
  std::uint32_t height {1024};

  bmp::bmp image(width, height);
  rgb::RGB color {};

  for (size_t y{0}; y < image.height(); ++y)
  {
    for (size_t x{0}; x < image.width(); ++x)
    {
      image.setRGB(x, y, color.setRGB(x, y, 128));
    }
  }

  std::string fname{"../images/image.bmp"};

  if ( image.write(fname) )
  {
    std::cout << "...saved \"" << fname << "\"\n";
  }
  else
  {
    std::cout << "...failed\n";
  }
}  // testBMP

}  // namespace bmpTest
