//
// perlinDemos.cpp
//
#include "image.h"
#include "perlinNoise.h"
#include "perlinDemos.h"

#include <cmath>
////////////////////////////////////////////////////////////////////////////////

namespace sg::perlinTest {

int
perlinDemo00() {
  // Define the size_ of the image
  unsigned int width = 1000; //600;
  unsigned int height = 1000; //450;

  // Create an empty PPM image
  sg::ppm image(width, height);

  // Create a PerlinNoise object with the reference permutation vector
  PerlinNoise pn;

  size_t kk{0};
  unsigned int i{};
  unsigned int j{};
  double n{};
  double x{};
  double y{};
  // Visit every pixel of the image and assign a color generated with Perlin noise
  // y
  for (i = 0; i < height; ++i) {
    // x
    for (j = 0; j < width; ++j) {
      x = static_cast<double>(j) / static_cast<double>(width);
      y = static_cast<double>(i) / static_cast<double>(height);

      // Wood like structure
      n = 20.0 * pn.noise(x, y, 0.8);
      n = n - floor(n);

      // Map the values to the [0, 255] interval, for simplicity we use
      // tones of grey
      image.setRGB(kk,
                   static_cast<u_char>(floor(255 * n)),
                   static_cast<u_char>(floor(255 * n)),
                   static_cast<u_char>(floor(255 * n)));
      ++kk;
    }
  }

  // Save the image in a binary PPM file
  image.write("../images/figure_8_R.ppm");

  // Create an empty PPM image
  sg::ppm image2(width, height);

  // read back the just saved binary PPM file
  image2.read("../images/figure_8_R.ppm");

  // save it again with another name
  image2.write("../images/figure_8_R-COPY.ppm");

  return 0;
}

int
perlinDemo01() {
  // Define the size_ of the image
  unsigned int width = 1000; //600;
  unsigned int height = 1000; //450;

  // Create an empty PPM image
  sg::ppm image(width, height);

  // Create a PerlinNoise object with a random permutation vector generated with seed
  PerlinNoise pn;
  pn.generateNewPermVector();

  size_t kk{0};
  unsigned int i{};
  unsigned int j{};
  double n{};
  double x{};
  double y{};
  // Visit every pixel of the image and assign a color generated with Perlin noise
  // y
  for (i = 0; i < height; ++i) {
    // x
    for (j = 0; j < width; ++j) {
      x = static_cast<double>(j) / static_cast<double>(width);
      y = static_cast<double>(i) / static_cast<double>(height);

      // Typical Perlin noise
      n = pn.noise(10.0 * x, 10.0 * y, 0.8);

      // Map the values to the [0, 255] interval, for simplicity we use
      // tones of grey
      image.setRGB(kk,
                   static_cast<u_char>(floor(255 * n)),
                   static_cast<u_char>(floor(255 * n)),
                   static_cast<u_char>(floor(255 * n)));
      ++kk;
    }
  }

  // Save the image in a binary PPM file
  image.write("../images/figure_7_P.ppm");

  // Create an empty PPM image
  sg::ppm image2(width, height);

  // read back the just saved binary PPM file
  image2.read("../images/figure_7_P.ppm");

  // save it again with another name
  image2.write("../images/figure_7_P-COPY.ppm");

  return 0;
}

}  // namespace sg::perlinTest
