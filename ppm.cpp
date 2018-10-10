//
// ppm.cpp
//
#include "ppm.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
////////////////////////////////////////////////////////////////////////////////
namespace ppm {

// create a PPM object
ppm::ppm() : width_(0), height_(0), max_col_val_(255) {}

// create a PPM object and fill it with data stored in fname
ppm::ppm(const std::string &fname) : width_(0), height_(0), max_col_val_(255) {
  read(fname);
}

// create an "empty" PPM image with a given width_ and height_;the r_, g_, b_ arrays are filled with zeros
ppm::ppm(const unsigned int _width, const unsigned int _height) {
  init(_width, _height);
  nr_lines_ = height_;
  nr_columns_ = width_;
  size_ = width_ * height_;

  // fill r_, g_ and b_ with 0
  r_.resize(size_);
  g_.resize(size_);
  b_.resize(size_);
}

// init with default values
void
ppm::init(const unsigned int width, unsigned int height, unsigned int max_col_val) const noexcept {
  width_ = width;
  height_ = height;
  max_col_val_ = max_col_val;
}

void
ppm::setR(const size_t index, const u_char r) const noexcept {
  r_[index] = r;
}

void
ppm::setR(const size_t x, size_t y, const u_char r) const noexcept {
  r_[x + y * width_] = r;
}

void
ppm::setG(const size_t index, const u_char g) const noexcept {
  g_[index] = g;
}

void
ppm::setG(const size_t x, size_t y, const u_char g) const noexcept {
  g_[x + y * width_] = g;
}

void
ppm::setB(const size_t index, const u_char b) const noexcept {
  b_[index] = b;
}

void
ppm::setB(const size_t x, size_t y, const u_char b) const noexcept {
  b_[x + y * width_] = b;
}

void
ppm::setRGB(const size_t index, const u_char r, const u_char g, const u_char b) const noexcept {
  r_[index] = r;
  g_[index] = g;
  b_[index] = b;
}

void
ppm::setRGB(const size_t x, const size_t y, const u_char r, const u_char g, const u_char b) const noexcept {
  auto index{x + y * width_};

  r_[index] = r;
  g_[index] = g;
  b_[index] = b;
}

// read the PPM image from fname
void
ppm::read(const std::string &fname) const noexcept(false) {
  std::ifstream inf(fname.c_str(), std::ios::in | std::ios::binary);

  if (inf.is_open()) {
    std::string line;
    std::getline(inf, line);
    if (line != "P6") {
      std::cerr << "Error: Unrecognized file format."
                << std::endl;
      return;
    }

    std::getline(inf, line);
    while (line[0] == '#') {
      std::getline(inf, line);
    }
    std::stringstream dimensions(line);

    try {
      dimensions >> width_;
      dimensions >> height_;
      nr_lines_ = height_;
      nr_columns_ = width_;
    }
    catch (std::exception &e) {
      std::cerr << "Header file format error. "
                << e.what()
                << std::endl;
      return;
    }

    std::getline(inf, line);
    std::stringstream max_val(line);
    try {
      max_val >> max_col_val_;
    }
    catch (std::exception &e) {
      std::cout << "Header file format error. " << e.what() << std::endl;
      return;
    }

    size_ = width_ * height_;

    r_.reserve(size_);
    g_.reserve(size_);
    b_.reserve(size_);

    for (unsigned int i{0}; i < size_; ++i) {
      r_[i] = static_cast<u_char>(inf.get());
      g_[i] = static_cast<u_char>(inf.get());
      b_[i] = static_cast<u_char>(inf.get());
    }
  } else {
    std::cerr << "Error: Unable to open file "
              << fname
              << std::endl;
  }
  inf.close();
}

// write the PPM image in fname
void
ppm::write(const std::string &fname) const noexcept(false) {
  std::ofstream outf(fname.c_str(), std::ios::out | std::ios::binary);

  if (outf.is_open()) {
    outf << "P6\n" << width_ << " " << height_ << "\n" << max_col_val_ << "\n";

    for (unsigned int i{0}; i < size_; ++i) {
      outf << r_[i] << g_[i] << b_[i];
    }
  } else {
    std::cerr << "Error: Unable to open file "
              << fname
              << std::endl;
  }
  outf.close();
}

} // namespace ppm
