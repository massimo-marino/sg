// Process a binary PPM file
//
// ppm.cpp
//
#pragma once

#include <vector>
#include <string>
////////////////////////////////////////////////////////////////////////////////
namespace ppm {

using ppm_t = std::vector<u_char>;

class ppm final {
private:
  void init(unsigned int width = 0,
            unsigned int height = 0,
            unsigned int max_col_val = 255) const noexcept;

  // arrays for storing the R,G,B values
  mutable ppm_t r_;
  mutable ppm_t g_;
  mutable ppm_t b_;

  mutable unsigned int width_{0};
  mutable unsigned int height_{0};
  mutable unsigned int max_col_val_{255};
  // total number of elements (pixels)
  mutable unsigned int size_;

  // info about the PPM file (height_ and width_)
  mutable unsigned int nr_lines_{0};
  mutable unsigned int nr_columns_{0};

public:
  ppm();

  // create an "epmty" PPM image with a given width_ and height_;
  // the r_, g_, b_ arrays are filled with zeros
  ppm(unsigned int _width, unsigned int _height);

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

  // read the PPM image from fname
  void read(const std::string &fname) const noexcept(false);

  // write the PPM image in fname
  void write(const std::string &fname) const noexcept(false);
};

}  // namespace ppm
