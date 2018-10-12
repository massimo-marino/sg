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
ppm::ppm(const std::string &fname) : width_(0), height_(0), max_col_val_(255), data_(0) {
  read(fname);
}

// create an "empty" PPM image with a given width_ and height_; data_ is filled with zeros
ppm::ppm(const unsigned int _width, const unsigned int _height, unsigned int _max_col_val) :
        width_(_width),
        height_(_height),
        max_col_val_(_max_col_val),
        data_(static_cast<size_t>(_width * _height)),
        size_(_width * _height)
{
  data_.reserve(size_);
}

void
ppm::setR(const size_t index, const u_char r) const noexcept {
  data_[index].setR(r);
}
void
ppm::setR(const size_t x, size_t y, const u_char r) const noexcept {
  data_[x + y * width_].setR(r);
}

void
ppm::setG(const size_t index, const u_char g) const noexcept {
  data_[index].setG(g);
}
void
ppm::setG(const size_t x, size_t y, const u_char g) const noexcept {
  data_[x + y * width_].setG(g);
}

void
ppm::setB(const size_t index, const u_char b) const noexcept {
  data_[index].setB(b);
}
void
ppm::setB(const size_t x, size_t y, const u_char b) const noexcept {
  data_[x + y * width_].setB(b);
}

void
ppm::setRGB(const size_t index, const u_char r, const u_char g, const u_char b) const noexcept {
  data_[index].setRGB(r, g, b);
}
void
ppm::setRGB(const size_t x, const size_t y, const u_char r, const u_char g, const u_char b) const noexcept {
  data_[x + y * width_].setRGB(r, g, b);
}

// read a PPM image from fname
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
    data_.clear();
    data_.resize(size_);
    data_.reserve(size_);

    for (unsigned int i{0}; i < size_; ++i) {
      data_[i].setRGB(static_cast<u_char>(inf.get()),
                      static_cast<u_char>(inf.get()),
                      static_cast<u_char>(inf.get()));
    }
  } else {
    std::cerr << "Error: Unable to open file "
              << fname
              << std::endl;
  }
  inf.close();
}  // read

// write a PPM image in fname
void
ppm::write(const std::string &fname) const noexcept(false) {
  std::ofstream outf(fname.c_str(), std::ios::out | std::ios::binary);

  if (outf.is_open()) {
    outf << "P6\n" << width_ << " " << height_ << "\n" << max_col_val_ << "\n";

    for (unsigned int i{0}; i < size_; ++i) {
      outf << data_[i].Red() << data_[i].Green() << data_[i].Blue();
    }
  } else {
    std::cerr << "Error: Unable to open file "
              << fname
              << std::endl;
  }
  outf.close();
}  // write

} // namespace ppm
