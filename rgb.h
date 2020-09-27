//
// rgb.h
//
// Created by massimo on 10/1/18.
//
#pragma once

#include "helpers.h"

#include <iostream>
#include <vector>
#include <cmath>
////////////////////////////////////////////////////////////////////////////////

namespace sg::rgb {

// 0xAARRGGBB -> AA alpha, RR red, GG green, BB blue
// when alpha not used in class RGB is set to 0x00 by default
using RGB_t = uint32_t;

class RGB final
{
public:
  explicit
  RGB() = default;

  explicit
  RGB(const u_char _c) : rgbHex_(static_cast<RGB_t>(_c << 16 | _c << 8 | _c)) {}

  explicit
  RGB(const u_char _a, const u_char _r, const u_char _g, const u_char _b) : rgbHex_(static_cast<RGB_t>(_a << 24 | _r << 16 | _g << 8 | _b)) {}

  explicit
  RGB(const u_char _r, const u_char _g, const u_char _b) : rgbHex_(static_cast<RGB_t>(_r << 16 | _g << 8 | _b)) {}

  explicit
  RGB(int32_t _rgb) : rgbHex_(static_cast<RGB_t>(_rgb)) {}

  explicit
  RGB(RGB_t _rgb) : rgbHex_(_rgb) {}

  bool
  operator==(const RGB &rhs) const noexcept
  {
    return rhs.rgbHex_ == rgbHex_;
  }

  bool
  operator!=(const RGB &rhs) const noexcept
  {
    return rhs.rgbHex_ != rgbHex_;
  }

  RGB_t
  operator()() const noexcept
  {
    return rgbHex_;
  }

  operator RGB_t() const noexcept
  {
    return rgbHex_;
  }

  u_char
  Alpha() const noexcept
  {
    return static_cast<u_char>((rgbHex_ & ALPHAMASK_) >> 24);
  }

  u_char
  Red() const noexcept
  {
    return static_cast<u_char>((rgbHex_ & REDMASK_) >> 16);
  }

  u_char
  Green() const noexcept
  {
    return static_cast<u_char>((rgbHex_ & GREENMASK_) >> 8);
  }

  u_char
  Blue() const noexcept
  {
    return static_cast<u_char>(rgbHex_ & BLUEMASK_);
  }

  RGB_t
  rgb() const noexcept
  {
    return rgbHex_;
  }

  template <typename A = u_char>
  RGB&
  setA(const A _a) noexcept
  {
    rgbHex_ = rgbHex_ | static_cast<RGB_t>(static_cast<u_char>(_a) << 24);
    return *this;
  }

  template <typename R = u_char>
  RGB&
  setR(const R _r) noexcept
  {
    rgbHex_ = rgbHex_ | static_cast<RGB_t>(static_cast<u_char>(_r) << 16);
    return *this;
  }

  template <typename G = u_char>
  RGB&
  setG(const G _g) noexcept
  {
    rgbHex_ = rgbHex_ | static_cast<RGB_t>(static_cast<u_char>(_g) << 8);
    return *this;
  }

  template <typename B = u_char>
  RGB&
  setB(const B _b) noexcept
  {
    rgbHex_ = rgbHex_ | static_cast<RGB_t>(static_cast<u_char>(_b));
    return *this;
  }

  template <typename A = u_char, typename R = u_char, typename G = u_char, typename B = u_char>
  RGB&
  setRGB(const A _a, const R _r, const G _g, const B _b) noexcept
  {
    rgbHex_ = static_cast<RGB_t>(static_cast<u_char>(_a) << 24 | static_cast<u_char>(_r) << 16 | static_cast<u_char>(_g) << 8 | static_cast<u_char>(_b));
    return *this;
  }

  template <typename R = u_char, typename G = u_char, typename B = u_char>
  RGB&
  setRGB(const R _r, const G _g, const B _b) noexcept
  {
    rgbHex_ = static_cast<RGB_t>(static_cast<u_char>(_r) << 16 | static_cast<u_char>(_g) << 8 | static_cast<u_char>(_b));
    return *this;
  }

  RGB&
  setRGB(const int32_t rgb) noexcept
  {
    rgbHex_ = static_cast<RGB_t>(rgb);
    return *this;
  }

  RGB&
  setRGB(const RGB_t rgb) noexcept
  {
    rgbHex_ = rgb;
    return *this;
  }

  //
  // hue H in [0,360)
  // saturation S, brightness B in [0,1]
  // r,g,b in [0,255]
  // http://colorizer.org/
  //
  RGB&
  hsv2rgb(const float hue, const float saturation, float brightness) noexcept
  {
    if ( 0.0f == saturation )
    {
      // achromatic (grey)
      brightness = std::round(brightness * 255.0f);
      return setRGB(brightness, brightness, brightness);
    }

    int i{};
    float f{};
    float p{};
    float q{};
    float t{};

    float hhue = hue / 60.0f;  // sector 0 to 5
    i = static_cast<int>(std::floor(hhue));
    f = hhue - i;      // factorial part of hue
    p = std::round( (brightness * (1 - saturation)) * 255.0f );
    q = std::round( (brightness * (1 - saturation * f)) * 255.0f );
    t = std::round( (brightness * (1 - saturation * (1 - f))) * 255.0f );
    brightness = std::round(brightness * 255.0f);

    switch ( i )
    {
      case 0:
        return setRGB(brightness, t, p);
      case 1:
        return setRGB(q, brightness, p);
      case 2:
        return setRGB(p, brightness, t);
      case 3:
        return setRGB(p, q, brightness);
      case 4:
        return setRGB(t, p, brightness);
      case 5:
      default:
        return setRGB(brightness, p, q);
    }
  }  // hsv2rgb

  //
  // adapted from: http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
  //
  // http://colorizer.org/
  //
  void rgb2hsv(float& hue, float& saturation, float& brightness) const noexcept
  {
    float K {0.0f};
    float r {Red() / 255.0f};
    float g {Green() / 255.0f};
    float b {Blue() / 255.0f};

    if ( g < b )
    {
      std::swap(g, b);
      K = -1.0f;
    }

    if ( r < g )
    {
      std::swap(r, g);
      K = -2.0f / 6.0f - K;
    }

    const float chroma = r - std::min(g, b);

    // hue is in [0,1]
    //hue = fabs(K + (g - b) / (6.0f * chroma + 1e-20f));
    // return hue in [0,360]
    hue = 360.0f * (K + (g - b) / (6.0f * chroma + 1e-20f));
    if (hue < 0) { hue = -hue; }
    saturation = 100.0f * (chroma / (r + 1e-20f));
    brightness = 100.0f * r;
  }  // rgb2hsv

private:

  static const RGB_t ALPHAMASK_ {0xFF000000};
  static const RGB_t REDMASK_   {0x00FF0000};
  static const RGB_t GREENMASK_ {0x0000FF00};
  static const RGB_t BLUEMASK_  {0x000000FF};

  mutable RGB_t rgbHex_{};

};  // class RGB

using pixels_t = std::vector<rgb::RGB>;

} // namespace sg::rgb

std::ostream& operator<<(std::ostream &os, const sg::rgb::RGB& rgb);
