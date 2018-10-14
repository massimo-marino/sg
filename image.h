//
// image.h
//
// Created by massimo on 10/13/18.
//
#pragma once

#include "rgb.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
////////////////////////////////////////////////////////////////////////////////
namespace sg {

using pixels_t = rgb::pixels_t;

#pragma pack (push, 1)

class image {
protected:
  // image width in pixels
  mutable uint32_t width_ {0};
  // image height in pixels
  mutable uint32_t height_ {0};
  // total number of pixels
  mutable uint32_t size_ {0};
  // the pixel image
  mutable pixels_t data_ {};

  bool
  checkGraphicFile(const std::string &path, const std::string& magic) const noexcept(false)
  {
    if (std::ifstream ifs {path, std::ios_base::binary})
    {
      char magicFromFile[3] {};

      ifs >> magicFromFile[0];
      ifs >> magicFromFile[1];

      return (static_cast<std::string>(magicFromFile) == magic);
    }
    return false;
  }  // checkGraphicFile

public:
  // create an empty default 100x100-sized image object
  image() : width_(100), height_(100), size_(100 * 100), data_(static_cast<size_t>(100 * 100))
  {
    data_.reserve(size_);
  }

  // create an "empty" image with a given width_ and height_; data_ is filled with zeros
  image(const uint32_t _width, const uint32_t _height) :
  width_(_width),
  height_(_height),
  size_(_width * _height),
  data_(static_cast<size_t>(_width * _height))
  {
    data_.reserve(size_);
  }

  // default dtor
  virtual ~image();

  // default copy ctor
  // usage:
  // image obj{};
  // image copiedObj{obj};
  image(const image &rhs) = default;

  // default copy assignment
  // usage:
  // image obj{};
  // image copiedObj;
  // copiedObj = obj;
  image&
  operator=(const image &rhs) = default;

  // default move ctor
  // The move constructor is called whenever selected by overload resolution,
  // which typically occurs when an object is initialized (by direct-initialization
  // or copy-initialization) from rvalue (xvalue or prvalue) (until C++17)
  // xvalue (since C++17) of the same type, including:
  //
  // initialization: T a = std::move(b); or T a(std::move(b));, where b is of type T;
  // function argument passing: f(std::move(a));, where a is of type T and f is void f(T t);
  // function return: return a; inside a function such as T f(), where a is of type T which has a move constructor.
  image(image &&rhs) = default;

  // default move assignment operator
  image&
  operator=(image &&rhs) = default;

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

  image&
  setRGB(const size_t x, const size_t y, const rgb::RGB &color) noexcept
  {
    data_[y * width_ + x].setRGB(color);
    return *this;
  }

  image&
  setRGB(const size_t index, const rgb::RGB &color) noexcept
  {
    data_[index].setRGB(color);
    return *this;
  }

  image&
  setR(const size_t index, const u_char r) noexcept {
    data_[index].setR(r);
    return *this;
  }

  image&
  setR(const size_t x, size_t y, const u_char r) noexcept {
    data_[x + y * width_].setR(r);
    return *this;
  }

  image&
  setG(const size_t index, const u_char g) noexcept {
    data_[index].setG(g);
    return *this;
  }
  image&
  setG(const size_t x, size_t y, const u_char g) noexcept {
    data_[x + y * width_].setG(g);
    return *this;
  }

  image&
  setB(const size_t index, const u_char b) noexcept {
    data_[index].setB(b);
    return *this;
  }

  image&
  setB(const size_t x, size_t y, const u_char b) noexcept {
    data_[x + y * width_].setB(b);
    return *this;
  }

  image&
  setRGB(const size_t index, const u_char r, const u_char g, const u_char b) noexcept {
    data_[index].setRGB(r, g, b);
    return *this;
  }

  image&
  setRGB(const size_t x, const size_t y, const u_char r, const u_char g, const u_char b) noexcept {
    data_[x + y * width_].setRGB(r, g, b);
    return *this;
  }

  rgb::RGB&
  getRGB(const size_t x, const size_t y) const noexcept
  {
    return data_[y * width_ + x];
  }

  rgb::RGB&
  getRGB(const size_t index) const noexcept
  {
    return data_[index];
  }

};  // class image

class ppm final : public image {
private:
  mutable uint32_t max_col_val_ {255};

public:
  // create a PPM default-sized object
  ppm() : image(), max_col_val_(255) {}

  // create an "empty" PPM with a given width_ and height_; data_ is filled with zeros
  ppm(const uint32_t _width, const uint32_t _height, uint32_t _max_col_val = 255) :
  image(_width, _height),
  max_col_val_(_max_col_val)
  {}

  ~ppm();

  bool isPPM(const std::string& path) const noexcept(false)
  {
    return checkGraphicFile(path, "P6");
  }

  // read a PPM image from fname
  bool
  read(const std::string &fname) const noexcept(false) {
    std::ifstream ifs(fname.c_str(), std::ios::in | std::ios::binary);

    if (ifs.is_open()) {
      std::string line;
      std::getline(ifs, line);
      if (line != "P6") {
        std::cerr << "Error: Unrecognized file format:"
                  << fname
                  << " is not a PPM file.\n";
        return false;
      }

      std::getline(ifs, line);
      while (line[0] == '#') {
        std::getline(ifs, line);
      }
      std::stringstream dimensions(line);

      try {
        dimensions >> width_;
        dimensions >> height_;
      }
      catch (std::exception &e) {
        std::cerr << "Header file format error. "
                  << e.what()
                  << "\n";
        return false;
      }

      std::getline(ifs, line);
      std::stringstream max_val(line);
      try {
        max_val >> max_col_val_;
      }
      catch (std::exception &e) {
        std::cerr << "Header file format error. "
                  << e.what()
                  << "\n";
        return false;
      }

      size_ = width_ * height_;
      data_.clear();
      data_.resize(size_);
      data_.reserve(size_);

      for (size_t i{0}; i < size_; ++i) {
        data_[i].setRGB(static_cast<u_char>(ifs.get()),
                        static_cast<u_char>(ifs.get()),
                        static_cast<u_char>(ifs.get()));
      }
    } else {
      std::cerr << "Error: Unable to open file "
                << fname
                << "\n";
      return false;
    }
    return true;
  }  // read

  // write a PPM image in fname
  bool
  write(const std::string &fname) const noexcept(false) {
    std::ofstream ofs(fname.c_str(), std::ios::out | std::ios::binary);

    if (ofs.is_open()) {
      ofs << "P6\n" << width_ << " " << height_ << "\n" << max_col_val_ << "\n";

      for (size_t i{0}; i < size_; ++i) {
        ofs << data_[i].Red() << data_[i].Green() << data_[i].Blue();
      }
    } else {
      std::cerr << "Error: Unable to open file "
                << fname
                << "\n";
      return false;
    }
    return true;
  }  // write

};  // class ppm

class bmp final : public image {
private:
  struct BMPHeader
  {
    BMPHeader(const std::uint32_t _bfSize,
              const std::uint32_t _biWidth,
              const std::uint32_t _biHeight,
              const std::uint32_t _biSizeImage) :
            bfSize(_bfSize),
            biWidth(_biWidth),
            biHeight(_biHeight),
            biSizeImage(_biSizeImage)
    {}

    std::uint16_t bfType {0x4d42};  // "BM"
    std::uint32_t bfSize {};
    std::uint16_t bfReserved1 {0};
    std::uint16_t bfReserved2 {0};
    std::uint32_t bfOffBits {sizeof(BMPHeader)};
    std::uint32_t biSize {40};
    std::uint32_t biWidth {};
    std::uint32_t biHeight {};
    std::uint16_t biPlanes {1};
    std::uint16_t biBitCount {24};
    std::uint32_t biCompression {0};
    std::uint32_t biSizeImage {};
    std::int32_t  biXPelsPerMeter {0};
    std::int32_t  biYPelsPerMeter {0};
    std::uint32_t biClrUsed {0};
    std::uint32_t biClrImportant {0};
  };  // struct BMPHeader
  static_assert(sizeof(BMPHeader) == 54);

//  constexpr
//  bool
//  inBounds(const std::int32_t y, const std::int32_t x) const noexcept
//  {
//    return (0 <= y) && (y < height_) && (0 <= x) && (x < width_);
//  }

public:
  // create a BMP default-sized object
  bmp() : image() {}

  // create an "empty" BMP with a given width_ and height_; data_ is filled with zeros
  bmp(const uint32_t _width, const uint32_t _height) :
  image(_width, _height)
  {}

  ~bmp();

  bool isBMP(const std::string& path) const noexcept(false)
  {
    return checkGraphicFile(path, "BM");
  }

  bool
  write(const std::string &path) const noexcept(false)
  {
    const std::uint32_t rowSize {width_ * 3 + width_ % 4};
    const std::uint32_t bmpsize {static_cast<uint32_t>(rowSize * height_)};
    const BMPHeader header(static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
                           width_,
                           height_,
                           bmpsize);

    if (std::ofstream ofs {path, std::ios_base::binary})
    {
      ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

      std::vector<std::uint8_t> line(static_cast<size_t>(rowSize));
      rgb::RGB&& color {0,0,0};

      for (std::int32_t y {static_cast<std::int32_t>(height_) - 1}; (-1) < y; --y)
      {
        size_t pos {0};

        for (std::uint32_t x {0}; x < width_; ++x)
        {
          color = getRGB(x, static_cast<size_t>(y));

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
      // error trying to open the file
      return false;
    }
  }
};  // class bmp

#pragma pack (pop)

namespace imageTest {

[[maybe_unused]] void testPPM();
[[maybe_unused]] void testBMP();
[[maybe_unused]] void testImageFileFormat();

}  // namespace imageTest

}  // namespace sg
