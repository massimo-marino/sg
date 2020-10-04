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
#include <memory>
#include <png.h>
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
  checkGraphicFile(const std::string &path, const std::string& magic, const ulong offset = 0) const noexcept(false)
  {
    if (std::ifstream ifs {path, std::ios_base::binary})
    {
      const auto numChars {magic.length()};
      auto magicFromFile {std::make_unique<char[]>(numChars + 1)};
      size_t i {0};

      ifs.seekg(offset);
      for (i = 0; i < numChars; ++i)
      {
        ifs >> magicFromFile[i];
      }
      magicFromFile[i] = '\0';
      return (static_cast<std::string>(magicFromFile.get()) == magic);
    }
    return false;
  }  // checkGraphicFile

public:
  // create an empty default 100x100-sized image object
  image() :
  width_(100),
  height_(100),
  size_(100 * 100),
  data_(static_cast<size_t>(100 * 100))
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
  virtual ~image() = default;

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

  uint32_t
  width() const noexcept
  {
    return width_;
  }

  uint32_t
  height() const noexcept
  {
    return height_;
  }

  image&
  setRGB(const size_t x, const size_t y, const rgb::RGB& color) noexcept
  {
    data_[x + y * width_].setRGB(color);
    return *this;
  }

  image&
  setRGB(const size_t index, const rgb::RGB& color) noexcept
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

class png final : public image {
private:
  unsigned long bpp_ {3};

public:
  // create a PNG default-sized object
  png() :
  image()
  {}

  // create an "empty" PNG with a given width_ and height_; data_ is filled with zeros
  png(const uint32_t _width, const uint32_t _height, const unsigned long _bpp = 3) :
  image(_width, _height),
  bpp_(_bpp)
  {}

  ~png() = default;

  // png signature: 0x?? 0x50 0x4E 0x47
  bool
  isPNG(const std::string& fname) const noexcept(false)
  {
    return checkGraphicFile(fname, "PNG", 1);
  }

  bool
  isPNGlib(const std::string& fname) const noexcept(false)
  {
    std::ifstream inf(fname, std::ios::in | std::ofstream::binary);
    if ( !inf.is_open() )
    {
      return false;
    }

    const png_size_t numToCheck {64};
    char header[numToCheck] {};

    inf.read(header, numToCheck);

    int is_png {!png_sig_cmp(reinterpret_cast<png_bytep>(header), static_cast<png_size_t>(0), numToCheck)};
    if ( !is_png )
    {
      return false;
    }
    return true;
  }  // isPNG

  std::vector<unsigned char>
  write() const noexcept(false)
  {
    struct pngimage_t
    {
      std::vector <unsigned char> pngData_ {};
    };

    pngimage_t pngImage;
    png_infop info_ptr;
    png_structp png_ptr;

    u_char r {};
    u_char g {};
    u_char b {};
    u_char a {};

    pngImage.pngData_.reserve(data_.size() * bpp_);

    for (const auto& c : data_)
    {
      r = c.Red();
      g = c.Green();
      b = c.Blue();
      pngImage.pngData_.emplace_back(r);
      pngImage.pngData_.emplace_back(g);
      pngImage.pngData_.emplace_back(b);
      if ( 4 == bpp_ )
      {
        a = c.Alpha();
        pngImage.pngData_.emplace_back(a);
      }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if ( !png_ptr ) {throw std::runtime_error( "png_create_write_struct" ); }

    info_ptr = png_create_info_struct(png_ptr);

    if ( !info_ptr ) {throw std::runtime_error( "png_create_info_struct" ); }

    if ( 3 == bpp_ ) png_set_IHDR(png_ptr, info_ptr, width_, height_,
                                  8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                                  PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    if ( 4 == bpp_ ) png_set_IHDR(png_ptr, info_ptr, width_, height_,
                                  8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                                  PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // set the zlib compression level
    png_set_compression_level(png_ptr, Z_BEST_SPEED);

    std::vector<unsigned char> file_content;

    png_set_write_fn(png_ptr, &file_content,
                     [] (const png_structp _png_ptr, const png_bytep _data, const png_size_t _length)
                     {
                       std::vector<unsigned char> &fileContent = *(reinterpret_cast<std::vector<unsigned char>*>(png_get_io_ptr(_png_ptr)));
                       fileContent.reserve(_length);
                       for (uint32_t i {0}; i < _length; ++i)
                       {
                         fileContent.emplace_back(_data[i]);
                       }
                     }, nullptr);

    png_write_info(png_ptr, info_ptr);

    std::vector<png_bytep> row_pointers(height_);

    for (uint32_t y {0}; y < height_; ++y)
    {
      row_pointers[y] = &pngImage.pngData_[y * png_get_rowbytes(png_ptr, info_ptr)];
    }
    png_write_image(png_ptr, &row_pointers[0]);
    png_write_end(png_ptr, nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return file_content;
  }  // write

  bool
  write(const std::string &fname)
  {
    std::vector<unsigned char> data_to_write {write()};

    std::ofstream outf(fname, std::ios::out | std::ofstream::binary);
    std::copy(data_to_write.begin(), data_to_write.end(), std::ostreambuf_iterator<char>(outf));

    return true;
  }  // write_png_file
};  // class png

class ppm final : public image {
private:
  mutable uint32_t max_col_val_ {255};

public:
  // create a PPM default-sized object
  ppm() :
  image(),
  max_col_val_(255)
  {}

  // create an "empty" PPM with a given width_ and height_; data_ is filled with zeros
  ppm(const uint32_t _width, const uint32_t _height, uint32_t _max_col_val = 255) :
  image(_width, _height),
  max_col_val_(_max_col_val)
  {}

  ~ppm() = default;

  // ppm signature: 0x50 0x36
  bool
  isPPM(const std::string& fname) const noexcept(false)
  {
    return checkGraphicFile(fname, "P6");
  }

  // read a PPM image from fname
  bool
  read(const std::string& fname) const noexcept(false) {
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

      char r {};
      char g {};
      char b {};
      for (size_t i{0}; i < size_; ++i) {
        ifs.get(r);
        ifs.get(g);
        ifs.get(b);
        data_[i].setRGB(r, g, b);
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
  write(const std::string& fname) const noexcept(false) {
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
  static_assert(sizeof(BMPHeader) == 54, "BMPHeader must be 54 bytes");

//  constexpr
//  bool
//  inBounds(const std::int32_t y, const std::int32_t x) const noexcept
//  {
//    return (0 <= y) && (y < height_) && (0 <= x) && (x < width_);
//  }

public:
  // create a BMP default-sized object
  bmp() :
  image()
  {}

  // create an "empty" BMP with a given width_ and height_; data_ is filled with zeros
  bmp(const uint32_t _width, const uint32_t _height) :
  image(_width, _height)
  {}

  ~bmp() = default;

  // bmp signature: 0x42 0x4D
  bool
  isBMP(const std::string& fname) const noexcept(false)
  {
    return checkGraphicFile(fname, "BM");
  }

  bool
  write(const std::string& fname) const noexcept(false)
  {
    const std::uint32_t rowSize {width_ * 3 + width_ % 4};
    const std::uint32_t bmpsize {static_cast<uint32_t>(rowSize * height_)};
    const BMPHeader header(static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
                           width_,
                           height_,
                           bmpsize);

    if (std::ofstream ofs {fname, std::ios_base::binary})
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
    // error trying to open the file
    return false;
  }
};  // class bmp

#pragma pack (pop)

}  // namespace sg
