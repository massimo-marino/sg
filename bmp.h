//
// bmp.h
//
// Created by massimo on 10/8/18.
//
// this code is an adapted version from:
// https://github.com/Reputeless/PerlinNoise
//
// From the original license file:
// MIT License
//
//Copyright (c) 2013-2018 Ryo Suzuki <reputeless@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

#include "rgb.h"

#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
////////////////////////////////////////////////////////////////////////////////
namespace bmp
{
#pragma pack (push, 1)
struct BMPHeader
{
  std::uint16_t bfType;
  std::uint32_t bfSize;
  std::uint16_t bfReserved1;
  std::uint16_t bfReserved2;
  std::uint32_t bfOffBits;
  std::uint32_t biSize;
  std::uint32_t biWidth;
  std::uint32_t biHeight;
  std::uint16_t biPlanes;
  std::uint16_t biBitCount;
  std::uint32_t biCompression;
  std::uint32_t biSizeImage;
  std::int32_t biXPelsPerMeter;
  std::int32_t biYPelsPerMeter;
  std::uint32_t biClrUsed;
  std::uint32_t biClrImportant;
};

static_assert(sizeof(BMPHeader) == 54);
#pragma pack (pop)

using bmp_t = std::vector<rgb::RGB>;

class bmp final
{
private:

  mutable bmp_t data_ {};

  std::uint32_t width_ {0};
  std::uint32_t height_ {0};

//  constexpr
//  bool
//  inBounds(const std::int32_t y, const std::int32_t x) const noexcept
//  {
//    return (0 <= y) && (y < height_) && (0 <= x) && (x < width_);
//  }

public:

  bmp() = default;

  bmp(const std::uint32_t width, const std::uint32_t height) noexcept :
          data_(static_cast<size_t>(width * height)),
          width_(width),
          height_(height)
  {}

  bmp&
  setRGB(const std::uint32_t x, const std::uint32_t y, const rgb::RGB &color) noexcept
  {
//    if (!inBounds(y, x))
//    {
//      return;
//    }

    data_[y * width_ + x] = color;
    return *this;
  }

  bmp&
  setRGB(const size_t x, const size_t y, const rgb::RGB &color) noexcept
  {
//    if (!inBounds(y, x))
//    {
//      return;
//    }

    data_[y * width_ + x] = color;
    return *this;
  }

  bmp&
  setRGB(const std::uint32_t x, const std::uint32_t y, const u_char r, const u_char g, const u_char b) noexcept
  {
    data_[y * width_ + x] = rgb::RGB(r, g, b);
    return *this;
  }

  bmp&
  setRGB(const size_t index, const u_char r, const u_char g, const u_char b) noexcept
  {
    data_[index] = rgb::RGB(r, g, b);
    return *this;
  }

  constexpr
  uint32_t
  width() const noexcept
  {
    return width_;
  }

  constexpr
  uint32_t
  height() const noexcept
  {
    return height_;
  }

  bool
  write(const std::string &path) const noexcept(false)
  {
    const std::uint32_t rowSize = width_ * 3 + width_ % 4;
    const std::uint32_t bmpsize {static_cast<uint32_t>(rowSize * height_)};
    const BMPHeader header =
            {
              0x4d42,
              static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
              0,
              0,
              sizeof(BMPHeader),
              40,
              width_,
              height_,
              1,
              24,
              0,
              bmpsize,
              0,
              0,
              0,
              0
            };

    if (std::ofstream ofs {path, std::ios_base::binary})
    {
      ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

      std::vector<std::uint8_t> line(static_cast<size_t>(rowSize));
      rgb::RGB&& color {0,0,0};

      for (std::int32_t y = static_cast<std::int32_t>(height_) - 1; (-1) < y; --y)
      {
        size_t pos{0};

        for (std::uint32_t x {0}; x < width_; ++x)
        {
          color = data_[static_cast<size_t>(y) * width_ + x];
          //const rgb::RGB& color{data_[static_cast<size_t>(y) * width_ + x]};

          line[pos++] = color.Blue();
          line[pos++] = color.Green();
          line[pos++] = color.Red();
        }

        ofs.write(reinterpret_cast<const char*>(line.data()), static_cast<long>(line.size()));
      }
      return true;
    }
    else
    {
      return false;
    }
  }
};  // class bmp

}  // namespace bmp

namespace bmpTest
{
[[maybe_unused]] void testBMP();
}  // namespace bmpTest
