//
// image.cpp
//
// Created by massimo on 10/13/18.
//

#include "image.h"
////////////////////////////////////////////////////////////////////////////////
namespace sg {

image::~image() {}

ppm::~ppm() {}

bmp::~bmp() {}

png::~png() {}

namespace imageTest {

[[maybe_unused]]
void
testPPM()
{
  std::uint32_t width {256};
  std::uint32_t height {1024};

  ppm image(width, height);
  rgb::RGB color {};

  for (size_t y {0}; y < image.height(); ++y)
  {
    for (size_t x {0}; x < image.width(); ++x)
    {
      image.setRGB(x, y, color.setRGB(x, y, 128));
    }
  }

  std::string fname {"../images/4-stacked-images.ppm"};

  if ( image.write(fname) )
  {
    std::cout << "...saved '" << fname << "'\n";
  }
  else
  {
    std::cerr << "...failed\n";
  }
}  // testPPM

[[maybe_unused]]
void
testBMP()
{
  std::uint32_t width {256};
  std::uint32_t height {1024};

  bmp image(width, height);
  rgb::RGB color {};

  for (size_t y {0}; y < image.height(); ++y)
  {
    for (size_t x {0}; x < image.width(); ++x)
    {
      image.setRGB(x, y, color.setRGB(x, y, 128));
    }
  }

  std::string fname {"../images/4-stacked-images.bmp"};

  if ( image.write(fname) )
  {
    std::cout << "...saved '" << fname << "'\n";
  }
  else
  {
    std::cerr << "...failed\n";
  }
}  // testBMP

[[maybe_unused]]
void
testPNG()
{
  std::uint32_t width {256};
  std::uint32_t height {1024};

  png image(width, height);
  rgb::RGB color {};

  for (unsigned int y {0}; y < image.height(); ++y)
  {
    for (unsigned int x {0}; x < image.width(); ++x)
    {
      image.setRGB(x, y, color.setRGB(x, y, 128));
    }
  }

  std::string fname {"../images/4-stacked-images.png"};

  if ( image.write_png_file(fname) )
  {
    std::cout << "...saved '" << fname << "'\n";
  }
  else
  {
    std::cerr << "...failed\n";
  }
}  // testPNG

[[maybe_unused]]
void
testImageFileFormat()
{
  sg::ppm p {};
  bool b1 {p.isPPM("../images/4-stacked-images.ppm")};
  bool b2 {p.isPPM("../images/4-stacked-images.bmp")};
  bool b3 {p.isPPM("../images/4-stacked-images.png")};

  // must print "OK"
  std::cout << ((b1 == true)  ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b2 == false) ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b3 == false) ? "OK" : "NOT OK") << std::endl;

  sg::bmp b {};
  b1 = b.isBMP("../images/4-stacked-images.ppm");
  b2 = b.isBMP("../images/4-stacked-images.bmp");
  b3 = b.isBMP("../images/4-stacked-images.png");

  // must print "OK"
  std::cout << ((b1 == false) ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b2 == true)  ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b3 == false) ? "OK" : "NOT OK") << std::endl;

  sg::png n {};
  b1 = n.isPNG("../images/4-stacked-images.ppm");
  b2 = n.isPNG("../images/4-stacked-images.bmp");
  b3 = n.isPNG("../images/4-stacked-images.png");

  // must print "OK"
  std::cout << ((b1 == false) ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b2 == false) ? "OK" : "NOT OK") << std::endl;
  std::cout << ((b3 == true)  ? "OK" : "NOT OK") << std::endl;
}  // testImageFileFormat

}  // namespace imageTest

}  // namespace sg
