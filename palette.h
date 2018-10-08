//
// palette.h
//
// Created by massimo on 10/8/18.
//
#pragma once

#include "rgb.h"
#include "randomNumberGenerators.h"

#include <fstream>
#include <cstdint>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
namespace palette
{
using rgbPalette_t = std::vector<rgb::RGB>;

class Palette final
{
private:
  static constexpr uint32_t numColorsDefault_ {16};
  static constexpr float saturationDefault_ {1.0f};
  static constexpr float brightnessDefault_ {1.0f};

  mutable uint32_t numColors_ {numColorsDefault_};
  mutable float saturation_ {numColorsDefault_};
  mutable float brightness_ {numColorsDefault_};
  mutable rgbPalette_t rgbPalette_ {};

public:
  // default ctor
  explicit
  Palette()
  {
    makePalette();
  }

  explicit
  Palette(const uint32_t numColors)
  {
    makePalette(numColors);
  }

  explicit
  Palette(const uint32_t numColors, const float saturation)
  {
    makePalette(numColors, saturation);
  }

  explicit
  Palette(const uint32_t numColors, const float saturation, const float brightness)
  {
    makePalette(numColors, saturation, brightness);
  }

  // default dtor
  ~Palette() = default;

  // default copy ctor
  // usage:
  // rgbPalette_ obj{};
  // rgbPalette_ copiedObj{obj};
  Palette(const Palette &rhs) = default;

  // default copy assignment
  // usage:
  // rgbPalette_ obj{};
  // rgbPalette_ copiedObj;
  // copiedObj = obj;
  Palette &operator=(const Palette &rhs) = default;

  // default move ctor
  // The move constructor is called whenever selected by overload resolution,
  // which typically occurs when an object is initialized (by direct-initialization
  // or copy-initialization) from rvalue (xvalue or prvalue) (until C++17)
  // xvalue (since C++17) of the same type, including:
  //
  // initialization: T a = std::move(b); or T a(std::move(b));, where b is of type T;
  // function argument passing: f(std::move(a));, where a is of type T and f is void f(T t);
  // function return: return a; inside a function such as T f(), where a is of type T which has a move constructor.
  Palette(Palette &&rhs) = default;

  // default move assignment operator
  Palette &operator=(Palette &&rhs) = default;

  rgbPalette_t
  operator()() const noexcept
  {
    return rgbPalette_;
  }

  operator rgbPalette_t() const noexcept
  {
    return rgbPalette_;
  }

  rgbPalette_t
  rgbPalette() const noexcept
  {
    return rgbPalette_;
  }

  // saturation, brightness in [0,1]
  // hue in [0,360]
  void makePalette(const uint32_t numColors = numColorsDefault_,
                   const float saturation = saturationDefault_,
                   const float brightness = brightnessDefault_) const noexcept
  {
    numColors_ = numColors;
    saturation_ = saturation;
    brightness_ = brightness;

    float hue{0.0f};
    rgb::RGB c{};
    uint32_t step{0};
    const float increment{360.0f / numColors_};

    rgbPalette_.clear();
    rgbPalette_.reserve(numColors_);
    for (step = 0; (step < numColors_) && (hue < 360.0f); ++step)
    {
      rgbPalette_.push_back(c.hsv2rgb(hue, saturation_, brightness_));
      hue = hue + increment;
    }
  }  // makePalette

  void shufflePalette() const noexcept
  {
    auto seed = utilities::getRandomINT<unsigned int>(1, 0xFFFFFFFF);

    // Initialize a random engine with seed
    std::default_random_engine engine(seed);

    // Shuffle  using the above random engine
    std::shuffle(rgbPalette_.begin(), rgbPalette_.end(), engine);
  }

  void savePalettes(const std::string& rgbPalettefname = "", const std::string& hsbPalettefname = "") const noexcept(false)
  {
    saveRGBPalette(rgbPalettefname);
    saveHSBPalette(hsbPalettefname);
  }

  void saveHSBPalette(const std::string& fname = "") const noexcept(false)
  {
    std::string fn {fname};

    if ( "" == fn )
    {
      fn = "hsb-palette-" + std::to_string(numColors_) + ".txt";
    }

    std::ofstream outf(fn.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    uint16_t i {0};

    if ( outf.is_open() )
    {
      outf << std::to_string(360.0f) << " " << std::to_string(saturation_) << " " << std::to_string(brightness_) << "\n";

      float h {};
      float s {};
      float b {};

      for (auto&& c: rgbPalette_)
      {
        c.rgb2hsv(h, s, b);
        outf << i << " " << h << " " << s << " " << b << "\n";
        ++i;
      }
    }
    else
    {
      std::cerr << "Error: Unable to open file "
                << fname
                << std::endl;
    }
    outf.close();
  }

  void saveRGBPalette(const std::string& fname = "") const noexcept(false)
  {
    std::string fn {fname};

    if ( "" == fn )
    {
      fn = "rgb-palette-" + std::to_string(numColors_) + ".txt";
    }

    std::ofstream outf(fn.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    uint16_t i {0};

    if ( outf.is_open() )
    {
      for (auto&& c: rgbPalette_)
      {
        outf << i << " " << c << "\n";
        ++i;
      }
    }
    else
    {
      std::cerr << "Error: Unable to open file "
                << fname
                << std::endl;
    }
    outf.close();
  }  // saveRGBPalette

};  // class Palette

}  // namespace palette

namespace paletteTest
{
  [[maybe_unused]] void testPalette();
  [[maybe_unused]] void testPalette_2();
}

std::ostream& operator<<(std::ostream &os, const  palette::Palette& p);
