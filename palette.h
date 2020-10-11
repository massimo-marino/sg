//
// palette.h
//
// Created by massimo on 10/8/18.
//
#pragma once

#include "image.h"
#include "randomNumberGenerators.h"

#include <iomanip>
#include <fstream>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <unordered_set>
////////////////////////////////////////////////////////////////////////////////

namespace sg::palette {

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
  mutable std::string order_ {};

  // saturation, brightness in [0,1]
  // hue in [0,360]
  void
  makeHSBPalette(const uint32_t numColors = numColorsDefault_,
                 const float saturation = saturationDefault_,
                 const float brightness = brightnessDefault_) const noexcept
  {
    numColors_ = numColors;
    saturation_ = saturation;
    brightness_ = brightness;

    const float hueIncrement {360.0f / numColors_};
    float hue {0.0f};
    rgb::RGB c {};

    rgbPalette_.clear();
    rgbPalette_.reserve(numColors_);
    for (uint32_t step {1}; hue < 360.0f; ++step)
    {
      rgbPalette_.push_back(c.hsv2rgb(hue, saturation_, brightness_));
      hue = hue + hueIncrement;
      if (numColors_ == step)
      {
        break;
      }
    }
  }  // makeHSBPalette

public:
  static const std::string rgbHexPaletteFileNameExtension_;

  // default ctor
  explicit
  Palette() :
  numColors_(0)
  {}

  explicit
  Palette(const int32_t numColors)
  {
    makeHSBPalette(numColors);
  }

  explicit
  Palette(const uint32_t numColors)
  {
    makeHSBPalette(numColors);
  }

  explicit
  Palette(const uint32_t numColors, const float saturation)
  {
    makeHSBPalette(numColors, saturation);
  }

  explicit
  Palette(const uint32_t numColors, const float saturation, const float brightness)
  {
    makeHSBPalette(numColors, saturation, brightness);
  }

  explicit
  Palette(const std::string& fname)
  {
    loadHexPaletteFromFile(fname);
  }

  pixels_t
  operator()() const noexcept
  {
    return rgbPalette_;
  }

  operator
  pixels_t() const noexcept
  {
    return rgbPalette_;
  }

  pixels_t
  rgbPalette() const noexcept
  {
    return rgbPalette_;
  }

  // current actual number of colors in the palette: in general size() <= numColors()
  // when the palette is being used: size() == numColors()
  constexpr
  size_t
  size () const noexcept
  {
    return rgbPalette_.size();
  }

  // the expected number of colors in the palette: in general size() <= numColors()
  // when the palette is being used: size() == numColors()
  constexpr
  uint32_t
  numColors () const noexcept
  {
    return numColors_;
  }

  Palette&
  setSaturation (const float saturation) noexcept
  {
    saturation_ = saturation;

    return *this;
  }

  Palette&
  setBrightness (const float brightness) noexcept
  {
    brightness_ = brightness;

    return *this;
  }

  Palette&
  addRGBColor (const rgb::RGB color) noexcept
  {
    rgbPalette_.push_back(color);

    return *this;
  }

  void
  clear () const noexcept
  {
    numColors_ = 0;
    rgbPalette_.clear();
    rgbPalette_.shrink_to_fit();
  }

  void
  clearAndResize (const uint32_t numColors) const noexcept
  {
    rgbPalette_.clear();
    rgbPalette_.shrink_to_fit();
    numColors_ = numColors;
    rgbPalette_.reserve(numColors_);
  }

  Palette&
  setPalette (pixels_t& palette) noexcept
  {
    clearAndResize(static_cast<uint32_t>(palette.size()));
    rgbPalette_ = palette;
    numColors_ = static_cast<uint32_t>(rgbPalette_.size());

    return *this;
  }

  Palette&
  allRGBColors () noexcept
  {
    rgb::RGB RGBColor {};
    u_char R {};
    u_char G {};
    u_char B {};

    clearAndResize(256*256*256);

    for (int rI {0}; rI <= 255; ++rI)
    {
      for (int gI {0}; gI <= 255; ++gI)
      {
        for (int bI {0}; bI <= 255; ++bI)
        {
          R = static_cast<u_char>(rI);
          G = static_cast<u_char>(gI);
          B = static_cast<u_char>(bI);
          RGBColor.setRGB(R, G, B);
          addRGBColor(RGBColor);
        }
      }
    }

    return *this;
  }

  Palette&
  setGrayScalePalette () noexcept
  {
    rgb::RGB rgbColor {};
    u_char c {};
    for (int i {0}; i <= 255; ++i)
    {
      c = static_cast<u_char>(i);
      rgbColor.setRGB(c, c, c);
      addRGBColor(rgbColor);
    }

    return *this;
  }

  Palette&
  makeCustomPalette (const uint32_t numColors,
                     const float saturation,
                     const float brightness) noexcept
  {
    std::unordered_set<sg::rgb::RGB_t> colorSet(numColors);

    makeHSBPalette(numColors, saturation, brightness);
    for (const rgb::RGB& RGBColor : rgbPalette_)
    {
      // insert unique color elements (no copies)
      colorSet.insert(RGBColor);
    }
    // create the final palette with unique colors
    pixels_t colorV(colorSet.begin(), colorSet.end());
    // replace the palette
    setPalette(colorV);

    return *this;
  }

  Palette&
  sortPalette() noexcept
  {
    std::sort(rgbPalette_.begin(), rgbPalette_.end());
    setOrder("sorted-");

    return *this;
  }

  Palette&
  shufflePalette() noexcept
  {
    auto seed = utilities::getRandomINT<unsigned int>(1, 0xFFFFFFFF);

    // Initialize a random engine with seed
    std::default_random_engine engine(seed);

    // Shuffle using the above random engine
    std::shuffle(rgbPalette_.begin(), rgbPalette_.end(), engine);

    setOrder("shuffled-");

    return *this;
  }  // shufflePalette

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
      return false;
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
    numColors_ = numColors;

    return true;
  }  // loadHexPaletteFromFile

  bool
  savePalettes(const std::string& rgbPalettefname = "",
               const std::string& rgbHexPalettefname = "",
               const std::string& hsbPalettefname = "") const noexcept(false)
  {
    return saveRGBPalette(rgbPalettefname) | saveRGBHexPalette(rgbHexPalettefname) | saveHSBPalette(hsbPalettefname);
  }

  bool
  saveHSBPalette(const std::string& fname = "") const noexcept(false)
  {
    const uint32_t numColors {static_cast<uint32_t>(size())};
    const std::string mode {"hsb-"};
    const std::string fn {fname + mode + getOrder() + "palette-" + std::to_string(numColors) + ".txt"};
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
    const uint32_t numColors {static_cast<uint32_t>(size())};
    const std::string mode {"rgb-"};
    const std::string fn {fname + mode + getOrder() + "palette-" + std::to_string(numColors) + ".txt"};
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

  bool
  saveRGBHexPalette(const std::string& fname = "") const noexcept(false)
  {
    const uint32_t numColors {static_cast<uint32_t>(size())};
    const std::string mode {"rgbhex-"};
    const std::string fn {fname + mode + getOrder() + "palette-" + std::to_string(numColors) + ".txt"};
    std::ofstream outf(fn.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    uint16_t i {0};

    if ( outf.is_open() )
    {
      for (auto&& c: rgbPalette_)
      {
        outf << "#" << std::hex
             // << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c.Alpha())
             << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c.Red())
             << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c.Green())
             << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c.Blue())
             << std::dec << "\n";
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
  }  // saveRGBHexPalette

  // make a color map image in a .bmp/.ppm/.png file
  // T ::= sg::bmp | sg::ppm | sg::png
  template <typename T = sg::png>
  bool
  makePaletteImage(const std::string& fname = "") const noexcept(false)
  {
    const uint32_t numColors {static_cast<uint32_t>(size())};

    // Define the size_ of the image in pixels
    // bwidth: the width of a single color band in the color map
    unsigned int bwidth {1};
    // bwidth is chosen depending on the number of colors
    if (numColors > 100 )
    {
      bwidth = 2;
    }
    else if (numColors > 50 )
    {
      bwidth = 8;
    }
    else if (numColors > 25 )
    {
      bwidth = 10;
    }
    else
    {
      bwidth = 25;
    }
    // bheight: the height of a single color band in the color map,
    // same value of the full image height
    const unsigned int bheight {100};
    const unsigned int width {bwidth * numColors};
    const unsigned int height {bheight};

    // Create an empty BMP/PPM/PNG image
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
    const std::string pngExtension {".png"};
    const std::string fileExtension { ((std::is_same<T, sg::ppm>::value) ? ppmExtension :
                                       ((std::is_same<T, sg::bmp>::value) ? bmpExtension :
                                        ((std::is_same<T, sg::png>::value) ? pngExtension : ".img"))) };
    const std::string paletteFileName {fname + getOrder() + "palette-" + std::to_string(numColors) + fileExtension};

    // Save the image in a binary BMP/PPM/PNG file
    return image.write(paletteFileName);
  }  // makePaletteImage

  static
  std::string
  getRgbHexPaletteFileNameExtension()
  {
    return rgbHexPaletteFileNameExtension_;
  }

  std::string getOrder() const;
  void setOrder(const std::string& order);
};  // class Palette

#pragma pack (pop)

} // namespace sg::palette

std::ostream& operator<<(std::ostream &os, const  sg::palette::Palette& p);
