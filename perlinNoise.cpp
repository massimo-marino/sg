//
// perlinNoise.cpp
//
// This code is a fork from:
// https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
// https://github.com/sol-prog/Perlin_Noise
//
#include "perlinNoise.h"
#include "randomNumberGenerators.h"

#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
////////////////////////////////////////////////////////////////////////////////
// THIS IS A DIRECT TRANSLATION TO C++11 FROM THE REFERENCE
// JAVA IMPLEMENTATION OF THE IMPROVED PERLIN FUNCTION (see http://mrl.nyu.edu/~perlin/noise/)
// THE ORIGINAL JAVA IMPLEMENTATION IS COPYRIGHT 2002 KEN PERLIN

// I ADDED AN EXTRA METHOD THAT GENERATES A NEW PERMUTATION VECTOR (THIS IS NOT
// PRESENT IN THE ORIGINAL IMPLEMENTATION)
////////////////////////////////////////////////////////////////////////////////
namespace sg {

// Initialize with the reference values for the permutation vector
PerlinNoise::PerlinNoise() {
  permVector_.reserve(512);

  // Duplicate the permutation vector
  permVector_.insert(permVector_.end(), permVector_.begin(), permVector_.end());
}

// Generate a new permutation vector based on the value of seed_
void
PerlinNoise::generateNewPermVector() const noexcept {
  permVector_.clear();
  permVector_.shrink_to_fit();

  permVector_.reserve(512);
  permVector_.resize(256);

  seed_ = utilities::getRandomINT<unsigned int>(1, 0xFFFFFFFF);

  // Fill permVector_ with values from 0 to 255: {0, 1, 2, ..., 255}
  std::iota(permVector_.begin(), permVector_.end(), 0);

  // Initialize a random engine with seed
  std::default_random_engine engine(seed_);

  // Shuffle  using the above random engine
  std::shuffle(permVector_.begin(), permVector_.end(), engine);

  // Duplicate the permutation vector
  permVector_.insert(permVector_.end(), permVector_.begin(), permVector_.end());
}

double
PerlinNoise::fade(const double t) const noexcept {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

// linear interpolation
double
PerlinNoise::lerp(const double t, const double a, const double b) const noexcept {
  return a + t * (b - a);
}

double
PerlinNoise::grad(const int hash, const double x, const double y, const double z) const noexcept {
  int h{hash & 15};
  // Convert lower 4 bits of hash into 12 gradient directions
  double u{(h < 8) ? x : y};
  double v{(h < 4) ? y : ((h == 12) || (h == 14)) ? x : z};

  return (((h & 1) == 0) ? u : -u) + (((h & 2) == 0) ? v : -v);
}

double
PerlinNoise::noise(double x, double y, double z) const noexcept {
  // Find the unit cube that contains the point
  int X{static_cast<int>(floor(x)) & 255};
  int Y{static_cast<int>(floor(y)) & 255};
  int Z{static_cast<int>(floor(z)) & 255};

  // Find relative x, y, z of point in cube
  x = x - floor(x);
  y = y - floor(y);
  z = z - floor(z);

  // Compute fade curves for each of x, y, z
  double u{fade(x)};
  double v{fade(y)};
  double w{fade(z)};

  // Hash coordinates of the 8 cube corners
  int A{permVector_[static_cast<size_t>(X)] + Y};
  int AA{permVector_[static_cast<size_t>(A)] + Z};
  int AB{permVector_[static_cast<size_t>(A + 1)] + Z};
  int B{permVector_[static_cast<size_t>(X + 1)] + Y};
  int BA{permVector_[static_cast<size_t>(B)] + Z};
  int BB{permVector_[static_cast<size_t>(B + 1)] + Z};

  // Add blended results from 8 corners of cube
  double res{lerp(w, lerp(v, lerp(u, grad(permVector_[static_cast<size_t>(AA)], x, y, z),
                                  grad(permVector_[static_cast<size_t>(BA)], x - 1, y, z)),
                          lerp(u, grad(permVector_[static_cast<size_t>(AB)], x, y - 1, z),
                               grad(permVector_[static_cast<size_t>(BB)], x - 1, y - 1, z))),
                  lerp(v, lerp(u, grad(permVector_[static_cast<size_t>(AA + 1)], x, y, z - 1),
                               grad(permVector_[static_cast<size_t>(BA + 1)], x - 1, y, z - 1)),
                       lerp(u, grad(permVector_[static_cast<size_t>(AB + 1)], x, y - 1, z - 1),
                            grad(permVector_[static_cast<size_t>(BB + 1)], x - 1, y - 1, z - 1))))};
  return (res + 1.0) / 2.0;
}

}  // namespace sg
