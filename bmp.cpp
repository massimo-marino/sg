//
// bmp.cpp
//
// Created by massimo on 10/8/18.
//
#include "bmp.h"

////////////////////////////////////////////////////////////////////////////////
namespace bmpTest
{

[[maybe_unused]]
void
testBMP()
{
  bmp::bmp image(500, 500);

  const rgb::RGB color(255, 0, 255);

  for (int32_t y{0}; y < image.height(); ++y)
  {
    for (int32_t x{0}; x < image.width(); ++x)
    {
      image.set(x, y, color);
    }
  }

  std::string fname{"image.bmp"};

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
