//
// palette.h
//
// Created by massimo on 10/8/18.
//
#pragma once

#include "rgb.h"
#include "randomNumberGenerators.h"
#include "ppm.h"
#include "bmp.h"

#include <fstream>
#include <cstdint>
#include <vector>
#include <type_traits>
////////////////////////////////////////////////////////////////////////////////
namespace palette {

using pixels_t = rgb::pixels_t;

#pragma pack (push, 1)
class Palette final
{
private:
  static constexpr uint32_t numColorsDefault_ {16};
  static constexpr float saturationDefault_ {1.0f};
  static constexpr float brightnessDefault_ {1.0f};

  mutable uint32_t numColors_ {numColorsDefault_};
  mutable float saturation_ {numColorsDefault_};
  mutable float brightness_ {numColorsDefault_};
  mutable pixels_t rgbPalette_ {};

  // saturation, brightness in [0,1]
  // hue in [0,360]
  void
  makePalette(const uint32_t numColors = numColorsDefault_,
              const float saturation = saturationDefault_,
              const float brightness = brightnessDefault_) const noexcept
  {
    numColors_ = numColors;
    saturation_ = saturation;
    brightness_ = brightness;

    float hue{0.0f};
    rgb::RGB c{};
    uint32_t step{0};
    const float hueIncrement{360.0f / numColors_};

    rgbPalette_.clear();
    rgbPalette_.reserve(numColors_);
    for (step = 0; (step < numColors_) && (hue < 360.0f); ++step)
    {
      rgbPalette_.push_back(c.hsv2rgb(hue, saturation_, brightness_));
      hue = hue + hueIncrement;
    }
  }  // makePalette

  // load a palette from a text file where each line is of this format:
  // #rrggbb\n
  // where r, g, b characters are hex digits
  // a palette file is generated for instance from GIMP 2.8 in: ~/.gimp-2.8/palettes/
  bool
  loadHexPaletteFromFile(const std::string &fname) const noexcept(false)
  {
    std::ifstream inf(fname, std::ios::in | std::ios::binary);
    if ( !inf.is_open() )
    {
      return true;
    }

    uint32_t numColors {0};
    rgb::RGB rgb {};
    std::string line {};

    rgbPalette_.clear();
    while ( std::getline(inf, line) )
    {
      // remove heading '#'
      line.erase(0, 1);
      rgbPalette_.push_back(rgb.setRGB(std::stoi(line, nullptr, 16)));
      ++numColors;

      if ( inf.eof() )
      {
        break;
      }
    }
    std::sort(rgbPalette_.begin(), rgbPalette_.end());
    numColors_ = numColors;

    return false;
  }  // loadHexPaletteFromFile

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

  explicit
  Palette(const std::string& fname)
  {
    loadHexPaletteFromFile(fname);
  }

  // default dtor
  ~Palette() = default;

  // default copy ctor
  // usage:
  // Palette obj{};
  // Palette copiedObj{obj};
  Palette(const Palette &rhs) = default;

  // default copy assignment
  // usage:
  // Palette obj{};
  // Palette copiedObj;
  // copiedObj = obj;
  Palette&
  operator=(const Palette &rhs) = default;

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
  Palette&
  operator=(Palette &&rhs) = default;

  pixels_t
  operator()() const noexcept
  {
    return rgbPalette_;
  }

  operator pixels_t() const noexcept
  {
    return rgbPalette_;
  }

  pixels_t
  rgbPalette() const noexcept
  {
    return rgbPalette_;
  }

  Palette&
  shufflePalette() noexcept
  {
    auto seed = utilities::getRandomINT<unsigned int>(1, 0xFFFFFFFF);

    // Initialize a random engine with seed
    std::default_random_engine engine(seed);

    // Shuffle  using the above random engine
    std::shuffle(rgbPalette_.begin(), rgbPalette_.end(), engine);

    return *this;
  }  // shufflePalette

  bool
  savePalettes(const std::string& rgbPalettefname = "", const std::string& hsbPalettefname = "") const noexcept(false)
  {
    return saveRGBPalette(rgbPalettefname) | saveHSBPalette(hsbPalettefname);
  }

  bool
  saveHSBPalette(const std::string& fname = "") const noexcept(false)
  {
    const std::string mode {"hsb"};
    const std::string fn {fname + mode + "-palette-" + std::to_string(numColors_) + ".txt"};
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
                << "\n";
      return false;
    }
    return true;
  }  // saveHSBPalette

  bool
  saveRGBPalette(const std::string& fname = "") const noexcept(false)
  {
    const std::string mode {"rgb"};
    const std::string fn {fname + mode + "-palette-" + std::to_string(numColors_) + ".txt"};
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
                << "\n";
      return false;
    }
    return true;
  }  // saveRGBPalette

  // make a color map image in a .bmp/.ppm file
  // T ::= bmp::bmp | ppm::ppm
  template <typename T>
  bool
  makePaletteImage(const std::string& fname = "") const noexcept(false)
  {
    // Define the size_ of the image in pixels
    // bwidth: the width of a single color band in the color map
    unsigned int bwidth {1};
    // bwidth is chosen depending on the number of colors
    if ( numColors_ > 100 )
    {
      bwidth = 2;
    }
    else if ( numColors_ > 50 )
    {
      bwidth = 8;
    }
    else if ( numColors_ > 25 )
    {
      bwidth = 10;
    }
    else
    {
      bwidth = 50;
    }
    // bheight: the height of a single color band in the color map
    // the same of the full image height
    const unsigned int bheight {100};
    const unsigned int width {bwidth * numColors_};
    const unsigned int height {bheight};

    // Create an empty BMP/PPM image
    T image(width, height);

    size_t x {};
    size_t y {};
    size_t xb {0};
    size_t colorIndex {0};
    rgb::RGB color {};

    // Visit every pixel of the image and assign a color from the palette
    for (x = 0; x < width; x = x + bwidth)
    {
      color = rgbPalette_[colorIndex];

      for (xb = 0; xb < bwidth; ++xb)
      {
        for (y = 0; y < height; ++y)
        {
          image.setRGB(x + xb + y * width, color.Red(), color.Green(), color.Blue());
        }
      }
      ++colorIndex;
    }

    const std::string bmpExtension {".bmp"};
    const std::string ppmExtension {".ppm"};
    const std::string fileExtension { ((std::is_same<T, ppm::ppm>::value) ? ppmExtension :
                                       ((std::is_same<T, bmp::bmp>::value) ? bmpExtension : ".img")) };
    const std::string paletteFileName {fname + "palette-" + std::to_string(numColors_) + fileExtension};

    // Save the image in a binary BMP/PPM file
    return image.write(paletteFileName);
  }  // makePaletteImage

};  // class Palette
#pragma pack (pop)

}  // namespace palette

namespace paletteTest {

[[maybe_unused]] void testPalette_1();
[[maybe_unused]] void testPalette_2();
[[maybe_unused]] void testPalette_3();
[[maybe_unused]] void testPalette_4();

}  // namespace paletteTest

std::ostream& operator<<(std::ostream &os, const  palette::Palette& p);
