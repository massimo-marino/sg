// Process a binary PPM file
//
// ppm.h
//
#pragma once

#include "rgb.h"

#include <vector>
#include <string>
////////////////////////////////////////////////////////////////////////////////
namespace ppm {

#pragma pack (push, 1)

using ppm_t = std::vector<rgb::RGB>;

class ppm final {
private:
  mutable unsigned int width_ {0};
  mutable unsigned int height_ {0};
  mutable unsigned int max_col_val_ {255};
  mutable ppm_t data_ {};
  // total number of elements (pixels)
  mutable unsigned int size_ {};

public:
  ppm();

  // create an "epmty" PPM image with a given width_ and height_;
  // data_ is filled with zeros
  ppm(unsigned int _width, unsigned int _height, unsigned int _max_col_val = 255);

  // create a PPM object and fill it with data stored in fname
  ppm(const std::string &fname);

  void setR(size_t index, u_char r) const noexcept;
  void setR(size_t x, size_t y, u_char r) const noexcept;

  void setG(size_t index, u_char g) const noexcept;
  void setG(size_t x, size_t y, u_char g) const noexcept;

  void setB(size_t index, u_char b) const noexcept;
  void setB(size_t x, size_t y, u_char b) const noexcept;

  void setRGB(size_t index,
              u_char r,
              u_char g,
              u_char b) const noexcept;
  void setRGB(size_t x,
              size_t y,
              u_char r,
              u_char g,
              u_char b) const noexcept;

  // read a PPM image from fname
  void read(const std::string &fname) const noexcept(false);

  // write a PPM image in fname
  void write(const std::string &fname) const noexcept(false);
};  // class ppm

#pragma pack (pop)

}  // namespace ppm
